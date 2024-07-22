#ifndef QUEUE_H
#define QUEUE_H

#include <omnetpp.h>

using namespace omnetpp;

class Queue: public cSimpleModule {
public:
    Queue();
    virtual ~Queue();
protected:
    cOutVector bufferSizeQueue;
    cOutVector packetDropQueue;
    int packetDropped;
    cQueue buffer;
    cMessage *endServiceEvent;
    simtime_t serviceTime;
    virtual void initialize();
    virtual void finish();
    virtual void handleMessage(cMessage *msg);
};

#endif // QUEUE_H
