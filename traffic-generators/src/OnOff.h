#ifndef __TRAFFIC_GENERATORS_ONOFF_H
#define __TRAFFIC_GENERATORS_ONOFF_H

#include <omnetpp.h>

namespace traffic_generators {

/**
 * Generates messages; see NED file for more info.
 */
class OnOff : public cSimpleModule
{

  public:
     cMessage *timerMessage;
     OnOff();
     virtual ~OnOff();

  protected:
     int limit;
     int counter;
    virtual void activity();
    virtual void initialize();
    virtual void handleMessage(cMessage *msg);
};

}; // namespace

#endif