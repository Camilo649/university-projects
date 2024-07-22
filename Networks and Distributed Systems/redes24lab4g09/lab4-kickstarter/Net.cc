#ifndef NET
#define NET

#include <string.h>
#include <omnetpp.h>
#include <packet_m.h>
#include <POLL_m.h>
#include <TableEntry.h>
#include <NotEntryFound.h>

using namespace omnetpp;

class Net: public cSimpleModule {
private:
    int id;
    unsigned int routersInNetwork;
    TableEntry* tbl;
    cMessage *resendPOLLEvent;
    unsigned int pollSent;
    POLL** pollArray;
    bool* pollArrived;
    void sendPolls();
    void updateTable();
    int selectGate(int destination);
    bool isPollsArrived();
public:
    Net();
    virtual ~Net();
protected:
    virtual void initialize();
    virtual void finish();
    virtual void handleMessage(cMessage *msg);
};

Define_Module(Net);

#endif /* NET */

Net::Net() {
}

Net::~Net() {
}

void Net::sendPolls() {
    std::string pollLName = "Polling in counterclockwise from router " + std::to_string(this->id);
    std::string pollRName = "Polling in clockwise from router " + std::to_string(this->id);
    POLL *pollL = new POLL(pollLName.c_str()); POLL *pollR = new POLL(pollRName.c_str());
    pollL->setSource(this->id); pollR->setSource(this->id);
    pollL->setHopCount(0); pollR->setHopCount(0);
    Info info(this->id, 0, 0.0);
    pollL->appendInformation(info); pollR->appendInformation(info); 
    pollL->setSide(false); pollR->setSide(true);
    int pollByteSize = static_cast<int>(par("POLLByteSize").doubleValue());
    pollL->setByteLength(pollByteSize); pollR->setByteLength(pollByteSize);

    // send polls along all lines
    send(pollL , "toLnk$o", 1); send(pollR , "toLnk$o", 0);
}

void Net::updateTable() {
    // If the table is empty, it is initialized
    // The number of routers is also initialized
    if (this->tbl == nullptr) {
        // Valid because I have information from each router;
        this->routersInNetwork = pollArray[0]->getInformationArraySize();
        this->tbl = new TableEntry[this->routersInNetwork];
        for (unsigned int i = 0; i < this->routersInNetwork; i++) {
            this->tbl[i] = TableEntry();
        }  
    }
    // First, set de table with the information from the first POLL
    for (unsigned int  i = 0; i < this->routersInNetwork; i++) {
        this->tbl[i].setRouterID(this->pollArray[0]->getInformation(i).id);
        this->tbl[i].setDelay(this->pollArray[0]->getInformation(i).receptionTime - this->pollArray[0]->getCreationTime().dbl());
        unsigned int gate = this->pollArray[0]->getSide() ? 0 : 1; 
        this->tbl[i].setGate(gate);
    }
    // Then, compare data with the others POLLs and keep the best according to the algorithm specification
    for (unsigned int i = 1; i < par("interfaces").intValue(); i++) {
        for (unsigned int  j = 0; j < this->routersInNetwork; j++) { 
            unsigned int routerID = this->pollArray[i]->getInformation(j).id;
            double delay = this->pollArray[i]->getInformation(j).receptionTime - this->pollArray[i]->getCreationTime().dbl();
            unsigned int hops = this->pollArray[i]->getInformation(j).hops;
            bool side = this->pollArray[i]->getSide();

            unsigned int k = 0;
            bool comparison = false;
            while (!comparison && k < this->routersInNetwork) {
                if (routerID == this->tbl[k].getRouterID()) {
                    if (delay < this->tbl[k].getDelay()) {
                        this->tbl[k].setEntry(routerID, delay, hops, side);
                    }
                    else if (delay == this->tbl[k].getDelay() && hops < this->tbl[k].getHops()) {
                        this->tbl[k].setEntry(routerID, delay, hops, side);
                    }
                    else if (delay == this->tbl[k].getDelay() && hops == this->tbl[k].getHops()) {
                        this->tbl[k].setGate(par("defaultGate"));
                    }
                    comparison = true;
                }
                k++;
            }           
        }
    }
}

/* Iterate the table until find the gate corresponding to the destination */
int Net::selectGate(int destination) {
    try {
        int gate;
        unsigned int i = 0;
        bool find = false;
        while (!find && i < this->routersInNetwork) {
            if (this->tbl[i].getRouterID() == destination) {
                gate = this->tbl[i].getGate();
                find = true;
            }
            else {
                i++;
            }
        }
        // If the entry was not found, the error is reported and chooses the deafult gate to forward 
        if (i == this->routersInNetwork) {
            std::string message = "ERROR: Routing table does not contain an entry for destination " + 
                                  std::to_string(destination) + ". Sendign packet by the default gate(" 
                                  + par("defaultGate").str() + ").";
            throw NotEntryFound(message);
        } 
        return gate;
    } catch (const NotEntryFound& e) {
        EV << e.what() << endl;
        return par("defaultGate");
    }
}

bool Net::isPollsArrived() {
    int i = 0;
    bool arrived = true;
    while (arrived && i < par("interfaces").intValue()) {
        arrived = arrived && this->pollArrived[i];
        i++;
    }
    return arrived;
}

void Net::initialize() {
    // Stores the router identifier
    this->id = this->getParentModule()->getIndex();
    // Set the table to null
    this->tbl = nullptr;
    // Initializes the polls and arrival arrays
    this->pollArray = new POLL*[par("interfaces")];
    for (int i = 0; i < par("interfaces").intValue(); i++) {
        this->pollArray[i] = nullptr;
    }
    this->pollArrived = new bool[par("interfaces")];
    // Initialize statistics
    this->pollSent = 0;
    // Schedule the first resendPOLLEvent
    resendPOLLEvent = new cMessage("resendPOLLEvent");
    scheduleAt(simTime(), resendPOLLEvent);
}

void Net::finish() {
    delete[] tbl;
    delete[] pollArray;
    delete[] pollArrived;
    recordScalar("Number of POLL packets sent", pollSent);
}

void Net::handleMessage(cMessage *msg) {

    // If the message is a POLL packet
    if (strcmp(msg->getClassName(), "POLL") == 0) {
        POLL *poll = (POLL *) msg;

        // If the packet comes back, updates routing tables and delete the packet.
        if (poll->getSource() == this->id) {
            //Mark the arrival
            unsigned int index = poll->getSide() ? 0 : 1;
            this->pollArrived[index] = true;

            // Update table when all POLLs arrived
            bool isAllPollsArrived = isPollsArrived();
            this->pollArray[index] = poll;
            if (isAllPollsArrived) {
                updateTable();
                // Delete POLL packets
                for (int i = 0; i < par("interfaces").intValue(); i++) {
                    delete(this->pollArray[i]);
                }
            }

            // Schedule a POLL packet resend if is not scheduled and if all POLLs arrived
            if (!resendPOLLEvent->isScheduled() && isAllPollsArrived) {
                double timeForNextPOLL = par("interfaces").intValue() * (par("POLLByteSize").doubleValue() / 100);
                scheduleAt(simTime() + timeForNextPOLL, resendPOLLEvent);
            }
        }
        // If not, it registers information and forwards
        else{
            poll->setHopCount(poll->getHopCount() + 1);
            Info info(this->id, poll->getHopCount(), simTime().dbl());
            poll->appendInformation(info);

            // Forward the packet through the correct gate
            poll->getSide() ? send(msg, "toLnk$o", 0) : send(msg, "toLnk$o", 1);
        }
    }

    // If the message is a sendPOLLEvent
    else if (msg == resendPOLLEvent) {
        sendPolls();
        // Update data related to polls
        this->pollSent += 2;
        for (int i = 0; i < par("interfaces").intValue(); i++) {
            this->pollArrived[i] = false;
        }
    }    

    // If the message is a data packet
    else {
        // All msg (events) on net are packets
        Packet *pkt = (Packet *) msg;

        // If this node is the final destination, send to App
        if (pkt->getDestination() == this->id) {
            send(msg, "toApp$o");
        }
        // If not, forward the packet as indicated in the table
        else {
            // Increment hop count
            pkt->setHopCount(pkt->getHopCount() + 1); 
            if (this->tbl != nullptr) {
                send(msg, "toLnk$o", selectGate(pkt->getDestination()));
            }
        }
    }
}
