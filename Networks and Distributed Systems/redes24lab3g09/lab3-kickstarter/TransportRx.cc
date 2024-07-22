#ifndef TRANSPORTRX
#define TRANSPORTRX

#include "Queue.h"
#include <omnetpp.h>
#include "ConnectionRequest_m.h"
#include "FeedbackPacket_m.h"

class TransportRx: public Queue {
    private:
        ConnectionRequest *CR;
        FeedbackPacket *fdb;
        cOutVector packetReceivedVector;
        cOutVector feedbackPacketGenVector;
        int packetReceived;
        int minNetworkCapacity;
    public:
        TransportRx();
        virtual ~TransportRx();
    protected:
        virtual void initialize();
        virtual void finish();
        virtual void handleMessage(cMessage *msg);

};

Define_Module(TransportRx);

TransportRx::TransportRx() {
    Queue();
    CR = NULL;
    fdb = NULL;
}

TransportRx::~TransportRx() {
}

void TransportRx::initialize() {
    buffer.setName("buffer");
    bufferSizeQueue.setName("BufferSizeQueue");
    packetDropQueue.setName("PacketDropQueue");
    feedbackPacketGenVector.setName("FeedbackPacketGen");
    packetDropQueue.record(0);
    endServiceEvent = new cMessage("endService");
    CR = new ConnectionRequest("ConnectionRequest");
    CR->setConnectionEnabled(false);
    CR->setWindowSize(par("bufferSize").intValue());
    CR->setByteLength(par("connectionRequestByteSize"));
    CR->setKind(1);
    send(CR, "toOut$o");
    packetReceived = 0;
    minNetworkCapacity = par("bufferSize").intValue();
}

void TransportRx::finish() {
}

void TransportRx::handleMessage(cMessage *msg) {
    // if msg is signaling an endServiceEvent
    if (msg == endServiceEvent) {
        // if packet in buffer, send next one
        if (!buffer.isEmpty()) {
            // dequeue packet
            cPacket *pkt = (cPacket*) buffer.pop();
            // send packet
            send(pkt, "toApp");
            // start new service
            serviceTime = pkt->getDuration() + par("serviceTime");
            scheduleAt(simTime() + serviceTime, endServiceEvent);
        }
    }
    // if msg is signaling a ConnectionRequest
    else if (auto *response = dynamic_cast<ConnectionRequest *>(msg)) {
        if (response->getConnectionEnabled()) {
            delete CR;
        }
        else { // resend ConnectionRequest
            CR->setConnectionEnabled(false);
            CR->setWindowSize(par("bufferSize").intValue());
            CR->setByteLength(par("connectionRequestByteSize"));
            CR->setKind(1);
            send(CR, "toOut$o");
        }
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
            FeedbackPacket *fdbpkt = (FeedbackPacket*) (msg);
            ((par("bufferSize").intValue() - buffer.getLength()) < fdbpkt->getRemainingCapacity()) ?
                                                        minNetworkCapacity = (par("bufferSize").intValue() - buffer.getLength()) :
                                                        minNetworkCapacity = fdbpkt->getRemainingCapacity();
            // Enqueue the packet
            packetReceived++;
            packetReceivedVector.record(packetReceived);
            buffer.insert(fdbpkt);
            bufferSizeQueue.record(buffer.getLength());
            // if the server is idle
            if (!endServiceEvent->isScheduled()) {
                // start the service
                scheduleAt(simTime() + 0, endServiceEvent);
            }
            // create new feedback packet
            fdb = new FeedbackPacket("FeedbackPacket");
            feedbackPacketGenVector.record(1);
            if (minNetworkCapacity - 1 != 0) {
                fdb->setRemainingCapacity(minNetworkCapacity - 1);
            }
            else {
                fdb->setRemainingCapacity(0);
            }
            fdb->setByteLength(par("feedbackPacketByteSize"));
            fdb->setKind(2);
            send(fdb, "toOut$o");
        }
    }
}

#endif /* TRANSPORTRX */
