struct Info {
    unsigned int id;
    unsigned int hops;
    double receptionTime;
}

class POLL extends cPacket {
    unsigned int source;
    unsigned int hopCount;
    Info information[];
    bool side;
}

