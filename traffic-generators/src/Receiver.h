#ifndef __TRAFFIC_GENERATORS_SINK_H
#define __TRAFFIC_GENERATORS_SINK_H

#include <omnetpp.h>

namespace traffic_generators {

/**
 * Message sink; see NED file for more info.
 */
class Receiver : public cSimpleModule
{
  private:
    // state
    simtime_t lastArrival;

    // statistics
    cDoubleHistogram iaTimeHistogram;
    cOutVector arrivalsVector;

  protected:
    virtual void initialize();
    virtual void handleMessage(cMessage *msg);
    virtual void finish();
};

}; // namespace

#endif
