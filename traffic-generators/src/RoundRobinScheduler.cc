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

#include "RoundRobinScheduler.h"
#include "SchedulerType.h"

Define_Module(RoundRobinScheduler)

RoundRobinScheduler::RoundRobinScheduler()
{
	internalDispatchingMessage = new cMessage("RRSched", SchedulerType(RR));
}

RoundRobinScheduler::~RoundRobinScheduler()
{
	//TODO: Cleanup leaks
	//packetQueueMap->begin()
}

void RoundRobinScheduler::initialize()
{
	queueSizeLimit = par("queueSizeLimit");
	delay = par("delay");
	queueRotatorIndex = 0;
	out = gate("out");
	packetQueueMap = new std::map<int, std::list<Packet*>*>();

	inputChannelIds = getInputChannelIds();
}

void RoundRobinScheduler::handleMessage(cMessage* msg)
{
	EV<< "RoundRobinScheduler::handleMessage: called for message " << msg << "\n";
	if (msg == internalDispatchingMessage)
	{
		// Sending the messages takes place here

		Packet* packet = pickupNextPacketFromQueues();
		EV<< "RoundRobinScheduler::handleMessage: packet = [" << msg << "] \n";
		if (packet)
		{
			send(packet, out);
			EV<< "RoundRobinScheduler::handleMessage: packet sent to out gate \n";
			scheduleAt(simTime() + delay, internalDispatchingMessage);
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

	//int srcAddress = packet->getSrcAddr();
}

void RoundRobinScheduler::finish()
{

}

void RoundRobinScheduler::addPacketToQueue(Packet* packet)
{
	int srcGateId = packet->getArrivalGateId();

	if (!isQueueSizeExceeded(srcGateId))
	{
		EV<< "RoundRobinScheduler::addPacketToQueue: queue for gate= [" << srcGateId << "] size is in bounds \n";

		if (!isQueueForGateExistent(srcGateId))
		{
			EV << "RoundRobinScheduler::addPacketToQueue: queue for gate " << srcGateId << " does not exist, creating one\n";
			std::list<Packet*>* queueList = new std::list<Packet*>();
			packetQueueMap->insert(std::pair<int, std::list<Packet*>*>(srcGateId, queueList));
		}
		else
		{
			EV << "RoundRobinScheduler::addPacketToQueue: queue for gate " << srcGateId << " exists\n";
		}

		std::list<Packet*>* list = getPacketListForGate(srcGateId);
		list->push_back(packet);
		EV << "RoundRobinScheduler::addPacketToQueue: packet " << packet << " added\n";
	}
	else
	{
		EV << "RoundRobinScheduler::addPacketToQueue: queue for gate= [" << srcGateId << "] size is exceeded \n";
		EV << "RoundRobinScheduler::addPacketToQueue: removing packet = [" << packet << "] \n";
		delete packet;
	}

}

Packet* RoundRobinScheduler::pickupNextPacketFromQueues()
{
	EV<< "RoundRobinScheduler::pickupNextPacketFromQueues: called \n";

	int chanelId = getChannelIdByIndex(queueRotatorIndex);
	Packet* packet = pickupPacketFromQueue(chanelId);
	rotateIndex();
	EV<< "RoundRobinScheduler::pickupNextPacketFromQueues: returning packet= [" << packet << "] \n";
	return packet;
}

Packet* RoundRobinScheduler::pickupPacketFromQueue(int gateId)
{
	EV<< "RoundRobinScheduler::pickupPacketFromQueue: called for gateId=[" << gateId <<"] \n";
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
			EV<< "RoundRobinScheduler::pickupPacketFromQueue: list was empty\n";
		}
	}

	EV<< "RoundRobinScheduler::pickupPacketFromQueue: returning packet= [" << packet << "] \n";

	return packet;
}

bool RoundRobinScheduler::isQueueForGateExistent(int gateId)
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

bool RoundRobinScheduler::isQueueSizeExceeded(int gateId)
{

	if (isQueueForGateExistent(gateId))
	{
		std::list<Packet*>* list = getPacketListForGate(gateId);

		return isQueueSizeExceeded(list);
	}
	else
	{
		return false;
	}
}

bool RoundRobinScheduler::isQueueSizeExceeded(std::list<Packet*>* list)
{
	if (queueSizeLimit > (list->size()))
	{
		return true;
	}
	else
	{
		return false;
	}
}

bool RoundRobinScheduler::isOutAttachedWithChannel()
{
	return out->getChannel() != NULL;
}

std::list<Packet*>* RoundRobinScheduler::getPacketListForGate(int gateId)
{
	EV<< "RoundRobinScheduler::getPacketListForGate: called for gateId=[" << gateId <<"] \n";
	std::map<int, std::list<Packet*>*>::iterator queueIter = packetQueueMap->find(gateId);

	if (queueIter == packetQueueMap->end())
	{
		EV << "RoundRobinScheduler::getPacketListForGate: list for gateId=[" << gateId <<"] does not exist, returning NULL \n";
		return NULL;
	}

	EV << "RoundRobinScheduler::getPacketListForGate: list for gateId=[" << gateId <<"] exists, returning list\n";
	return queueIter->second; // first==key, second==value ;)
}

void RoundRobinScheduler::rotateIndex()
{
	unsigned int prevqueueRotatorIndex = queueRotatorIndex;
	queueRotatorIndex = (queueRotatorIndex + 1) % packetQueueMap->size();
	EV<< "RoundRobinScheduler::rotateIndex: rotated index from " << prevqueueRotatorIndex << " to " << queueRotatorIndex << "\n";
}

int* RoundRobinScheduler::getInputChannelIds()
{
	int channelCount = this->gateSize("in");
	EV<< "RoundRobinScheduler::getInputChannelIds: channelCount= " << channelCount << "\n";
	int *inputChannelIds = new int[channelCount];
	for (int i = 0; i < channelCount; i++)
	{
		*(inputChannelIds + i) = gate("in", i)->getId();
		EV<< "RoundRobinScheduler::getInputChannelIds: Stored gateId "<< gate("in",i)->getId() << " \n";
	}
	return inputChannelIds;
}

int RoundRobinScheduler::getChannelIdByIndex(int index)
{
	int id = *(inputChannelIds + index);
	EV<< "RoundRobinScheduler::getChannelIdByIndex: returned id= [" << id << "] for index= [" << index << "] \n";
	return id;
}
