#include "LeakyBucketProfiler.h"
#include "ProfilerType.h"

Define_Module(LeakyBucketProfiler);

LeakyBucketProfiler::LeakyBucketProfiler()
{
	internalDispatchingMessage = new cMessage("LBProfiler", ProfilerType(LB));
}

LeakyBucketProfiler::~LeakyBucketProfiler()
{
}

void LeakyBucketProfiler::initialize()
{
	queueSizeLimit = par("queueSizeLimit");
	delay = par("delay");
	out = gate("out");
	packetList = new std::list<Packet*>();
}

void LeakyBucketProfiler::handleMessage(cMessage* msg)
{
	EV<< "LeakyBucketProfiler::handleMessage: called for message " << msg << "\n";
	if (msg == internalDispatchingMessage)
	{
		EV<< "LeakyBucketProfiler::handleMessage: packet = [" << msg << "] \n";
		Packet* packet = pickupPacketFromQueue(packetList);
		if (packet)
		{
			send(packet, out);
			EV<< "LeakyBucketProfiler::handleMessage: packet sent to out gate \n";
			scheduleAt(simTime() + delay, internalDispatchingMessage);
		}
		else
		{
			EV<< "LeakyBucketProfiler::handleMessage: packet was NULL \n";
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

void LeakyBucketProfiler::finish()
{
}

void LeakyBucketProfiler::addPacketToQueue(Packet* packet)
{
	EV<< "LeakyBucketProfiler::addPacketToQueue: is exceeded: "<<isQueueSizeExceeded(packetList)<< "\n";
	if (!isQueueSizeExceeded(packetList))
	{
		packetList->push_back(packet);
		EV<< "LeakyBucketProfiler::addPacketToQueue: packet " << packet << " added\n";
	}
	else
	{
		EV << "LeakyBucketProfiler::addPacketToQueue: removing packet = [" << packet << "] \n";
		delete packet;
	}

}

Packet* LeakyBucketProfiler::pickupPacketFromQueue(std::list<Packet*>* list)
{
	EV<< "LeakyBucketProfiler::pickupPacketFromQueue: called \n";

	Packet* packet = NULL;
	if (list && !list->empty())
	{
		packet = list->front();
		list->pop_front();
	}

	return packet;
}

bool LeakyBucketProfiler::isQueueSizeExceeded(std::list<Packet*>* list)
{
	unsigned int size = list->size();
	if (queueSizeLimit <= size)
	{
		EV<< "LeakyBucketProfiler::isQueueSizeExceeded(list): exceeded, limit = [" << queueSizeLimit << "], current size = ["<< size <<"] \n";
		return true;
	}
	else
	{
		EV << "LeakyBucketProfiler::isQueueSizeExceeded(list): not exceeded, limit = [" << queueSizeLimit << "], current size = ["<< size <<"] \n";
		return false;
	}
}
