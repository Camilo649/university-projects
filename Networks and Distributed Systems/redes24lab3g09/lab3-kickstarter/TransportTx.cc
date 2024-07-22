#ifndef TRANSPORTTX
#define TRANSPORTTX

#include "Queue.h"
#include <omnetpp.h>
#include "ConnectionRequest_m.h"
#include "FeedbackPacket_m.h"

class TransportTx : public Queue {
    private:
        bool Connected; // True if the connection to the receiver is established. False otherwise
        int UpperThreshold;
        int LowerThreshold;
        double TimeModifier; // Indicates at what speed send packtes
    public:
        TransportTx();
        virtual ~TransportTx();
    protected:
        virtual void initialize();
        virtual void finish();
        virtual void handleMessage(cMessage *msg);
};

Define_Module(TransportTx);

TransportTx::TransportTx() {
    Queue();
}

TransportTx::~TransportTx() {
}

void TransportTx::initialize() {
    buffer.setName("buffer");
    bufferSizeQueue.setName("BufferSizeQueue");
    packetDropQueue.setName("PacketDropQueue");
    packetDropQueue.record(0);
    endServiceEvent = new cMessage("endService");
    Connected = false;
    TimeModifier = 1.0;
}

void TransportTx::finish() {
}

void TransportTx::handleMessage(cMessage *msg) {
    // if msg is signaling an endServiceEvent
    if (msg == endServiceEvent) {
        // if packet in buffer, send next one
        if (Connected && !buffer.isEmpty()) {
            // dequeue packet
            cPacket *pkt = (cPacket*) buffer.pop();
            // send packet
            send(pkt, "toOut$o");
            // start new service
            serviceTime = pkt->getDuration() + (TimeModifier * par("serviceTime").doubleValue());
            scheduleAt(simTime() + serviceTime, endServiceEvent);
        }
    }
    // if msg is signaling a ConnectionRequest
    else if (auto *request = dynamic_cast<ConnectionRequest *>(msg)) {
        request->setConnectionEnabled(true);
        Connected = true;
        UpperThreshold = (80 * request->getWindowSize()) / 100; // 80% of the receiver window
        LowerThreshold = (20 * request->getWindowSize()) / 100; // 20% of the receiver window
        send(request, "toOut$o");
    }
    // if msg is a feedback packet
    else if (auto *information = dynamic_cast<FeedbackPacket *>(msg)) {
        if (information->getRemainingCapacity() >= UpperThreshold) {
            TimeModifier = TimeModifier / 1.1;
        }
        else if (information->getRemainingCapacity() <= LowerThreshold) {
            TimeModifier = TimeModifier * 1.1;
        }
        delete(msg);
    }
    // if msg is a data packet 
    else {     
        if (buffer.getLength() >= par("bufferSize").intValue()) {
            // drop the packet
            delete(msg);
            this->bubble("packet-dropped");
            packetDropped++;
            packetDropQueue.record(packetDropped);
        }
        else {
            // Enqueue the packet
            buffer.insert(msg);
            bufferSizeQueue.record(buffer.getLength());
            // if the server is idle
            if (!endServiceEvent->isScheduled()) {
                // start the service
                scheduleAt(simTime() + 0, endServiceEvent);
            }
        }
    }
}

#endif /* TRANSPORTTX */