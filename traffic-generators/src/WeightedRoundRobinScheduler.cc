//
// This program is free software: you can redistribute it and/or modify
// it under the terms of the GNU Lesser General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
// 
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU Lesser General Public License for more details.
// 
// You should have received a copy of the GNU Lesser General Public License
// along with this program.  If not, see http://www.gnu.org/licenses/.
// 

#include "WeightedRoundRobinScheduler.h"
#include "SchedulerType.h"

Define_Module(WeightedRoundRobinScheduler)

WeightedRoundRobinScheduler::WeightedRoundRobinScheduler()
{
	internalDispatchingMessage = new cMessage("WRRSched", SchedulerType(WRR));
}

WeightedRoundRobinScheduler::~WeightedRoundRobinScheduler()
{
	//TODO: Cleanup leaks
	//packetQueueMap->begin()
}

void WeightedRoundRobinScheduler::initialize()
{
	queueSizeLimit = par("queueSizeLimit");
	delay = par("delay");
	queueRotatorIndex = 0;
	out = gate("out");

	for (int i = 0; i < gateSize("in"); i++)
	{
		in[i] = gate("in", i);
	}

	weightsTokens = par("weights").stdstringValue();

	channelCount = this->gateSize("in");

//	weights = new int[channelCount];
	weights = new std::map<int, int>();
	weightRanges = new int[channelCount];

	parseWeights(weightsTokens, weights, channelCount);

	packetQueueMap = new std::map<int, std::list<Packet*>*>();
	inputChannelIds = getInputChannelIds();

	weightRotation = 0;

//	std::vector<int> vestor;
//	vestor.at()
}

void WeightedRoundRobinScheduler::handleMessage(cMessage* msg)
{
	EV<< "WeightedRoundRobinScheduler::handleMessage: called for message " << msg << "\n";
	if (msg == internalDispatchingMessage)
	{
		// Sending the messages takes place here

		Packet* packet = pickupNextPacketFromQueues();
		EV<< "WeightedRoundRobinScheduler::handleMessage: packet = [" << msg << "] \n";
		if (packet)
		{
			send(packet, out);
			EV<< "WeightedRoundRobinScheduler::handleMessage: packet sent to out gate \n";
			scheduleAt(simTime() + delay, internalDispatchingMessage);
		}
		else
		{
			EV<< "WeightedRoundRobinScheduler::handleMessage: packet was NULL \n";
		}

	}
	else
	{
		// Picking the messages up and putting them to queues takes place here
		Packet* packet = check_and_cast<Packet*>(msg);
		addPacketToQueue(packet);

		if(!internalDispatchingMessage->isScheduled())
		{
			EV<< "WeightedRoundRobinScheduler::handleMessage: scheduling next self invocation \n";
			scheduleAt(simTime() + delay, internalDispatchingMessage);
		}
		else
		{
			EV<< "WeightedRoundRobinScheduler::handleMessage: next self invocation already scheduled \n";
		}

	}

	//int srcAddress = packet->getSrcAddr();
}

void WeightedRoundRobinScheduler::finish()
{

}

void WeightedRoundRobinScheduler::addPacketToQueue(Packet* packet)
{
	int srcGateId = packet->getArrivalGateId();

	if (!isQueueSizeExceeded(srcGateId))
	{
		EV<< "WeightedRoundRobinScheduler::addPacketToQueue: queue for gate= [" << srcGateId << "] size is in bounds \n";

		if (!isQueueForGateExistent(srcGateId))
		{
			EV << "WeightedRoundRobinScheduler::addPacketToQueue: queue for gate " << srcGateId << " does not exist, creating one\n";
			std::list<Packet*>* queueList = new std::list<Packet*>();
			packetQueueMap->insert(std::pair<int, std::list<Packet*>*>(srcGateId, queueList));
		}
		else
		{
			EV << "WeightedRoundRobinScheduler::addPacketToQueue: queue for gate " << srcGateId << " exists\n";
		}

		std::list<Packet*>* list = getPacketListForGate(srcGateId);
		list->push_back(packet);
		EV << "WeightedRoundRobinScheduler::addPacketToQueue: packet " << packet << " added\n";
	}
	else
	{
		EV << "WeightedRoundRobinScheduler::addPacketToQueue: queue for gate= [" << srcGateId << "] size is exceeded \n";
		EV << "WeightedRoundRobinScheduler::addPacketToQueue: removing packet = [" << packet << "] \n";
		delete packet;
	}

}

Packet* WeightedRoundRobinScheduler::pickupNextPacketFromQueues()
{
	EV<< "WeightedRoundRobinScheduler::pickupNextPacketFromQueues: called \n";

	int chanelId = getChannelIdByIndex(queueRotatorIndex);
	Packet* packet = pickupPacketFromQueue(chanelId);
	rotateIndex();
	EV<< "WeightedRoundRobinScheduler::pickupNextPacketFromQueues: returning packet= [" << packet << "] \n";
	return packet;
}

Packet* WeightedRoundRobinScheduler::pickupPacketFromQueue(int gateId)
{
	EV<< "WeightedRoundRobinScheduler::pickupPacketFromQueue: called for gateId=[" << gateId <<"] \n";
	std::list<Packet*>* list = getPacketListForGate(gateId);
	//std::list<Packet*>::iterator queueIter = list->begin();

	Packet* packet = NULL;

	if (list)
	{

		if (!list->empty())
		{
			packet = list->front();
			list->pop_front();
		}
		else
		{
			EV<< "WeightedRoundRobinScheduler::pickupPacketFromQueue: list was empty\n";
		}
	}

	EV<< "WeightedRoundRobinScheduler::pickupPacketFromQueue: returning packet= [" << packet << "] \n";

	return packet;
}

bool WeightedRoundRobinScheduler::isQueueForGateExistent(int gateId)
{
	int keysFound = packetQueueMap->count(gateId);
	if (keysFound == 1)
	{
		return true;
	}
	else
	{
		return false;
	}
}

bool WeightedRoundRobinScheduler::isQueueSizeExceeded(int gateId)
{

	if (isQueueForGateExistent(gateId))
	{
		std::list<Packet*>* list = getPacketListForGate(gateId);
		bool exceeded = isQueueSizeExceeded(list);
		EV<< "WeightedRoundRobinScheduler::isQueueSizeExceeded(int): queue size " << (exceeded?"is":"isn't") << " exceeded, current size = ["<< list->size() <<"] \n";
		return exceeded;
	}
	else
	{
		EV<< "WeightedRoundRobinScheduler::isQueueSizeExceeded(int): queue does not exist yet thus not exceeded \n";
		return false;
	}
}

bool WeightedRoundRobinScheduler::isQueueSizeExceeded(std::list<Packet*>* list)
{
	unsigned int size = list->size();
	if (queueSizeLimit <= size)
	{
		EV<< "WeightedRoundRobinScheduler::isQueueSizeExceeded(list): exceeded, limit = [" << queueSizeLimit << "], current size = ["<< size <<"] \n";
		return true;
	}
	else
	{
		EV << "WeightedRoundRobinScheduler::isQueueSizeExceeded(list): not exceeded, limit = [" << queueSizeLimit << "], current size = ["<< size <<"] \n";
		return false;
	}
}

bool WeightedRoundRobinScheduler::isOutAttachedWithChannel()
{
	return out->getChannel() != NULL;
}

std::list<Packet*>* WeightedRoundRobinScheduler::getPacketListForGate(int gateId)
{
	EV<< "WeightedRoundRobinScheduler::getPacketListForGate: called for gateId=[" << gateId <<"] \n";
	std::map<int, std::list<Packet*>*>::iterator queueIter = packetQueueMap->find(gateId);

	if (queueIter == packetQueueMap->end())
	{
		EV << "WeightedRoundRobinScheduler::getPacketListForGate: list for gateId=[" << gateId <<"] does not exist, returning NULL \n";
		return NULL;
	}

	EV << "WeightedRoundRobinScheduler::getPacketListForGate: list for gateId=[" << gateId <<"] exists, returning list\n";
	return queueIter->second; // first==key, second==value ;)
}

void WeightedRoundRobinScheduler::rotateIndex()
{
	int i = 0;
	while (i < channelCount && weightRotation > weightRanges[i])
	{
		i++;
	}

	weightRotation = (weightRotation + 1) % weightRanges[channelCount - 1];

	unsigned int prevQueueRotatorIndex = queueRotatorIndex;
	queueRotatorIndex = i;
	EV<< "WeightedRoundRobinScheduler::rotateIndex: rotated index from " << prevQueueRotatorIndex << " to " << queueRotatorIndex << "\n";
}

int* WeightedRoundRobinScheduler::getInputChannelIds()
{
	int channelCount = this->gateSize("in");
	EV<< "WeightedRoundRobinScheduler::getInputChannelIds: channelCount= " << channelCount << "\n";
	int *inputChannelIds = new int[channelCount];
	for (int i = 0; i < channelCount; i++)
	{
		*(inputChannelIds + i) = gate("in", i)->getId();
		EV<< "WeightedRoundRobinScheduler::getInputChannelIds: Stored gateId "<< gate("in",i)->getId() << " \n";
	}
	return inputChannelIds;
}

int WeightedRoundRobinScheduler::getChannelIdByIndex(int index)
{
	int id = *(inputChannelIds + index);
	EV<< "WeightedRoundRobinScheduler::getChannelIdByIndex: returned id= [" << id << "] for index= [" << index << "] \n";
	return id;
}

void WeightedRoundRobinScheduler::parseWeights(std::string weightsTokens, std::map<int, int>* weights, int channelCount) throw ()
{
	cStringTokenizer moduleTokenizer(weightsTokens.c_str());

	int weight_index = 0;
	int sum = 0;
	while (moduleTokenizer.hasMoreTokens())
	{

		if (weight_index >= channelCount)
		{
			throw cRuntimeError("Number of provided weights is greater, than the number of connected channels='%s'", channelCount);
		}
		int gateId = findGate("in", weight_index);
		std::string str_weight(moduleTokenizer.nextToken());
		int weight = atoi(str_weight.c_str());
		sum += weight;
		*(weightRanges + weight_index) = sum;
		weights->insert(std::pair<int, int>(gateId, weight));
//		*(weights + weight_index) = weight;
		weight_index++;
	}

}

