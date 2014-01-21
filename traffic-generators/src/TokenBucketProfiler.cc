#include "TokenBucketProfiler.h"
#include "ProfilerType.h"

Define_Module(TokenBucketProfiler)

TokenBucketProfiler::TokenBucketProfiler()
{
	internalDispatchingMessage = new cMessage("LBProfiler", ProfilerType(LB));
}

TokenBucketProfiler::~TokenBucketProfiler()
{
}

void TokenBucketProfiler::initialize()
{
	queueSizeLimit = par("queueSizeLimit");
	delay = par("delay");
	out = gate("out");
	packetList = new std::list<Packet*>();

	tokensCount = 0;
	tokensMax = par("tokensMax");
	tokensToAdd = par("tokensToAdd");
	lastTokenAddedTime = SIMTIME_ZERO;
	lastDelayedPacket = NULL;

	WATCH(tokensCount);
}

void TokenBucketProfiler::handleMessage(cMessage* msg)
{
	EV<< "TokenBucketProfiler::handleMessage: called for message " << msg << "\n";
	if (msg == internalDispatchingMessage)
	{
		EV<< "TokenBucketProfiler::handleMessage: packet = [" << msg << "] \n";
		Packet* packet = pickupPacketFromQueue(packetList);
		if (packet)
		{
			send(packet, out);
			EV<< "TokenBucketProfiler::handleMessage: packet sent to out gate \n";
			scheduleAt(simTime() + delay, internalDispatchingMessage);
		}
		else
		{
			EV<< "TokenBucketProfiler::handleMessage: packet was NULL \n";
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

void TokenBucketProfiler::finish()
{
}

void TokenBucketProfiler::addPacketToQueue(Packet* packet)
{
	simtime_t currentTime = simTime();
	simtime_t timeDiff = currentTime - lastTokenAddedTime;

	if (timeDiff > 0)
		tokensCount = std::min((int32_t) (tokensCount + tokensToAdd * timeDiff.dbl()), tokensMax);
	lastTokenAddedTime = currentTime;

	if (packet == lastDelayedPacket)
	{

	}
	else if (packet->getByteLength() <= tokensCount)
	{
		// Jesli dlugosc pakietu jest niewieksza od liczby tokenow to mozna go
		// przeslac dalej.
		tokensCount -= packet->getByteLength();
		packetList->push_back(packet);
		EV<< "TokenBucketProfiler::addPacketToQueue: packet " << packet << " added\n";
	}
	else
	{
		lastDelayedPacket = packet;
		delay = (double)(packet->getByteLength() - tokensCount) / tokensToAdd;
		tokensCount -= packet->getByteLength();
	}

}

Packet* TokenBucketProfiler::pickupPacketFromQueue(std::list<Packet*>* list)
{
	EV<< "TokenBucketProfiler::pickupPacketFromQueue: called \n";

	Packet* packet = NULL;
	if (list && !list->empty())
	{
		packet = list->front();
		list->pop_front();
	}

	return packet;
}

bool TokenBucketProfiler::isQueueSizeExceeded(std::list<Packet*>* list)
{
	unsigned int size = list->size();
	if (queueSizeLimit <= size)
	{
		EV<< "TokenBucketProfiler::isQueueSizeExceeded(list): exceeded, limit = [" << queueSizeLimit << "], current size = ["<< size <<"] \n";
		return true;
	}
	else
	{
		EV << "TokenBucketProfiler::isQueueSizeExceeded(list): not exceeded, limit = [" << queueSizeLimit << "], current size = ["<< size <<"] \n";
		return false;
	}
}
