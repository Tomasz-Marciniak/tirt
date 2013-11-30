#ifndef __TRAFFIC_GENERATORS_SINK_H
#define __TRAFFIC_GENERATORS_SINK_H

#include <omnetpp.h>
#include "Packet_m.h"

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
		cOutVector sizeVector;
	protected:
		virtual void initialize();
		virtual void handleMessage(cMessage *msg);
		virtual void finish();
};

#endif
