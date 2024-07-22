#include "TableEntry.h"
#include <omnetpp.h>

using namespace omnetpp;

TableEntry::TableEntry() 
    : routerID(-1), delay(0.0), hops(0), gate(-1) {}

int TableEntry::getRouterID() const {
    return routerID;
}

double TableEntry::getDelay() const {
    return delay;
}

unsigned int TableEntry::getHops() const {
    return hops;
}

int TableEntry::getGate() const {
    return gate;
}

void TableEntry::setRouterID(int newRouterID) {
    routerID = newRouterID;
}

void TableEntry::setDelay(double newDelay) {
    delay = newDelay;
}

void TableEntry::setHops(unsigned int newHops) {
    hops = newHops;
}

void TableEntry::setGate(int newGate) {
    gate = newGate;
}

void TableEntry::setEntry(int routerID, double delay, unsigned int hops, bool side) {
    this->routerID = routerID;
    this->delay = delay;
    this->hops = hops;
    gate = (side ? 0 : 1);
}