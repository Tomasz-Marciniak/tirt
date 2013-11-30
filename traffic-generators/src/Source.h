#ifndef __TRAFFIC_GENERATORS_SOURCE_H
#define __TRAFFIC_GENERATORS_SOURCE_H

#include <omnetpp.h>
#include "Packet_m.h"


/**
 * Generates messages; see NED file for more info.
 */
class Source : public cSimpleModule
{
    public:
        cMessage *timerMessage;
        Source();
        virtual ~Source();

    protected:
        virtual void initialize();
        virtual void handleMessage(cMessage *msg);
        Packet* generatePacket();

};

#endif
