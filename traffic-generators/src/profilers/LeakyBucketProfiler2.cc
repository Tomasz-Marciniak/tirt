#include "LeakyBucketProfiler2.h"
#include "ProfilerType.h"

Define_Module(LeakyBucketProfiler2)
;

LeakyBucketProfiler2::LeakyBucketProfiler2()
{
}

LeakyBucketProfiler2::~LeakyBucketProfiler2()
{
}

void LeakyBucketProfiler2::initialize()
{
	queueSizeLimit = par("queueSizeLimit");
	delay = par("delay");
	out = gate("out");
	byteFlow = par("byteFlow");
	currentByteFlow = byteFlow;
	lastFlowIncrement = SIMTIME_ZERO;
	lastDelayedPacket = NULL;
	packetList = new std::list<Packet*>();
}

void LeakyBucketProfiler2::handleMessage(cMessage* msg)
{
	Packet* packet = check_and_cast<Packet*>(msg);

	simtime_t processDelay = par("processDelay");
	if (msg->isSelfMessage())
	{
		if (sendPacket(packet))
		{
			send(packet, out);

			Packet* packetFromQueue = pickupPacketFromQueue(packetList);
			if (packetFromQueue && !packetFromQueue->isScheduled())
			{
				scheduleAt(simTime() + processDelay, packetFromQueue);
			}
		}
		else
		{
			scheduleAt(simTime() + delay + processDelay, packet);
		}
	}
	else
	{

		// Picking the messages up and putting them to queues takes place here
		addPacketToQueue(packet);

		simtime_t processDelay = par("processDelay");
		scheduleAt(simTime() + processDelay, packet);
	}
}

void LeakyBucketProfiler2::finish()
{
}

bool LeakyBucketProfiler2::sendPacket(Packet* packet)
{
	simtime_t time = simTime();
	simtime_t timeDiff = time - lastFlowIncrement;

	if (timeDiff > 0)
		currentByteFlow = std::min((int32_t) (currentByteFlow + byteFlow * timeDiff.dbl()), byteFlow);

	lastFlowIncrement = time;

	if (packet == lastDelayedPacket)
	{
		return true;
	}
	else if (packet->getByteLength() <= currentByteFlow)
	{
		// Send forward because packet size less than current byte flow
		currentByteFlow -= packet->getByteLength();
		return true;
	}
	else
	{
		lastDelayedPacket = packet;
		delay = (double) (packet->getByteLength() - currentByteFlow) / byteFlow;
		currentByteFlow -= packet->getByteLength();

		return false;
	}
}

void LeakyBucketProfiler2::addPacketToQueue(Packet* packet)
{
	if (!isQueueSizeExceeded(packetList))
	{
		packetList->push_back(packet);
	}
	else
	{
		delete packet;
	}
}

Packet* LeakyBucketProfiler2::pickupPacketFromQueue(std::list<Packet*>* list)
{
	Packet* packet = NULL;
	if (list && !list->empty())
	{
		packet = list->front();
		list->pop_front();
	}

	return packet;
}

bool LeakyBucketProfiler2::isQueueSizeExceeded(std::list<Packet*>* list)
{
	return queueSizeLimit <= list->size();
}
