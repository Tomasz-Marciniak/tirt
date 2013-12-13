#ifndef __TRAFFIC_GENERATORS_ONOFF_H
#define __TRAFFIC_GENERATORS_ONOFF_H

#include <omnetpp.h>

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
		virtual void initialize();
		virtual void handleMessage(cMessage *msg);
};

#endif
