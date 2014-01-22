#include "DualLeakyBucketProfiler.h"
#include "ProfilerType.h"

Define_Module(DualLeakyBucketProfiler)

DualLeakyBucketProfiler::DualLeakyBucketProfiler()
{
	internalDispatchingMessage = new cMessage("LBProfiler", ProfilerType(LB));
}

DualLeakyBucketProfiler::~DualLeakyBucketProfiler()
{
}

void DualLeakyBucketProfiler::initialize()
{
	queueSizeLimit = par("queueSizeLimit");
	delay = par("delay");
	out = gate("out");
	packetList = new std::list<Packet*>();
}

void DualLeakyBucketProfiler::handleMessage(cMessage* msg)
{
	EV<< "DualLeakyBucketProfiler::handleMessage: called for message " << msg << "\n";
	if (msg == internalDispatchingMessage)
	{
		EV<< "DualLeakyBucketProfiler::handleMessage: packet = [" << msg << "] \n";
		Packet* packet = pickupPacketFromQueue(packetList);
		if (packet)
		{
			send(packet, out);
			EV<< "DualLeakyBucketProfiler::handleMessage: packet sent to out gate \n";
			scheduleAt(simTime() + delay, internalDispatchingMessage);
		}
		else
		{
			EV<< "DualLeakyBucketProfiler::handleMessage: packet was NULL \n";
		}
	}
	else
	{
		// Picking the messages up and putting them to queues takes place here
		Packet* packet = check_and_cast<Packet*>(msg);
		addPacketToQueue(packet);

		if(!internalDispatchingMessage->isScheduled())
		{
			scheduleAt(simTime() + delay, internalDispatchingMessage);
		}

	}
}

void DualLeakyBucketProfiler::finish()
{
}

void DualLeakyBucketProfiler::addPacketToQueue(Packet* packet)
{
	EV<< "DualLeakyBucketProfiler::addPacketToQueue: is exceeded: "<<isQueueSizeExceeded(packetList)<< "\n";
	if (!isQueueSizeExceeded(packetList))
	{
		packetList->push_back(packet);
		EV<< "DualLeakyBucketProfiler::addPacketToQueue: packet " << packet << " added\n";
	}
	else
	{
		EV << "DualLeakyBucketProfiler::addPacketToQueue: removing packet = [" << packet << "] \n";
		delete packet;
	}

}

Packet* DualLeakyBucketProfiler::pickupPacketFromQueue(std::list<Packet*>* list)
{
	EV<< "DualLeakyBucketProfiler::pickupPacketFromQueue: called \n";

	Packet* packet = NULL;
	if (list && !list->empty())
	{
		packet = list->front();
		list->pop_front();
	}

	return packet;
}

bool DualLeakyBucketProfiler::isQueueSizeExceeded(std::list<Packet*>* list)
{
	unsigned int size = list->size();
	if (queueSizeLimit <= size)
	{
		EV<< "DualLeakyBucketProfiler::isQueueSizeExceeded(list): exceeded, limit = [" << queueSizeLimit << "], current size = ["<< size <<"] \n";
		return true;
	}
	else
	{
		EV << "DualLeakyBucketProfiler::isQueueSizeExceeded(list): not exceeded, limit = [" << queueSizeLimit << "], current size = ["<< size <<"] \n";
		return false;
	}
}
