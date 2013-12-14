#ifndef LEAKYBUCKETPROFILER_H_
#define LEAKYBUCKETPROFILER_H_

#include <stdlib.h>
#include <list>
#include <omnetpp.h>
#include "Packet_m.h"

/**
 * Leaky Bucket
 * @author Tomasz Marciniak
 * @date 2013
 * @copyright GNU Public License.
 */
class LeakyBucketProfiler : public cSimpleModule
{
	public:
		LeakyBucketProfiler();
		virtual ~LeakyBucketProfiler();

	protected:
		virtual void initialize();
		virtual void handleMessage(cMessage* msg);
		virtual void finish();
		void addPacketToQueue(Packet* packet);
		Packet* pickupPacketFromQueue(std::list<Packet*>* list);
		bool isQueueSizeExceeded(std::list<Packet*>* list);

		std::list<Packet*>* packetList;
		cMessage* internalDispatchingMessage;
		int inputChannelId[];

		//Parameters
		unsigned int queueSizeLimit;
		simtime_t delay;

		//Infrastructure
		cGate* out;
};

#endif /* LEAKYBUCKETPROFILER_H_ */
