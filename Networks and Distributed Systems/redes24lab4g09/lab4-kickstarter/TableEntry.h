#ifndef TABLEENTRY_H
#define TABLEENTRY_H

#include <string>

class TableEntry {
private:
    int routerID;
    double delay;
    unsigned int hops;
    int gate;
public:
    // Constructor
    TableEntry();

    // Getters
    int getRouterID() const;
    double getDelay() const;
    unsigned int getHops() const;
    int getGate() const;

    // Setters
    void setRouterID(int newRouterID);
    void setDelay(double newDelay);
    void setHops(unsigned int newHops);
    void setGate(int newGate);
    void setEntry(int routerID, double delay, unsigned int hops, bool side);
};

#endif // TABLEENTRY_H
