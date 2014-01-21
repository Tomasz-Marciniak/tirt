#ifndef TOKENBUCKETPROFILER_H_
#define TOKENBUCKETPROFILER_H_

#include <stdlib.h>
#include <list>
#include <omnetpp.h>
#include "Packet_m.h"

/**
 * Token Bucket
 * @author Tomasz Marciniak
 * @date 2013
 * @copyright GNU Public License.
 */
class TokenBucketProfiler : public cSimpleModule
{

	public:
		TokenBucketProfiler();
		virtual ~TokenBucketProfiler();

	protected:
		virtual void initialize();
		virtual void handleMessage(cMessage* msg);
		virtual void finish();
		void addPacketToQueue(Packet* packet);
		Packet* pickupPacketFromQueue(std::list<Packet*>* list);
		bool isQueueSizeExceeded(std::list<Packet*>* list);

		std::list<Packet*>* packetList;
		cMessage* internalDispatchingMessage;

		Packet* lastDelayedPacket;


		int32_t tokensMax;
		int32_t tokensCount;
		int32_t tokensToAdd;
		simtime_t lastTokenAddedTime;

		//Parameters
		unsigned int queueSizeLimit;
		simtime_t delay;

		//Infrastructure
		cGate* out;
};

#endif /* TOKENBUCKETPROFILER_H_ */
