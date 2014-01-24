#ifndef LEAKYBUCKETPROFILER2_H_
#define LEAKYBUCKETPROFILER2_H_

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
class LeakyBucketProfiler2 : public cSimpleModule
{
	public:
		LeakyBucketProfiler2();
		virtual ~LeakyBucketProfiler2();

	protected:
		virtual void initialize();
		virtual void handleMessage(cMessage* msg);
		virtual void finish();

		void addPacketToQueue(Packet* packet);
		bool sendPacket(Packet* packet);
		bool isQueueSizeExceeded(std::list<Packet*>* list);

		Packet* pickupPacketFromQueue(std::list<Packet*>* list);

		std::list<Packet*>* packetList;


		cMessage* internalDispatchingMessage;

		// rozmiar kolejki
		uint32_t queueSizeLimit;

		// przeplyw na sekundê
		int32_t byteFlow;

		// obecny przeplyw
		int32_t currentByteFlow;

		// Czas w ktorym ostatnio zwiekszono przeplywnosc
		simtime_t lastFlowIncrement;

		// Ostatni zakolejkowany pakiet
		Packet* lastDelayedPacket;

		// OpóŸnienie
		simtime_t delay;

		// Wyjscie
		cGate* out;
};

#endif /* LEAKYBUCKETPROFILER2_H_ */
