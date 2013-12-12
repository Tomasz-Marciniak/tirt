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

RoundRobinScheduler::RoundRobinScheduler()
{

}

RoundRobinScheduler::~RoundRobinScheduler()
{

}

void RoundRobinScheduler::initialize()
{
	out = gate("out");
}

void RoundRobinScheduler::handleMessage(cMessage* msg)
{
	Packet* packet = check_and_cast<Packet*>(msg);

	//int srcAddress = packet->getSrcAddr();
}

void RoundRobinScheduler::finish()
{

}

void RoundRobinScheduler::addPacketToQueue(Packet* packet)
{
	int srcAddress = packet->getSrcAddr();

	if (!isQueueSizeExceeded(srcAddress))
	{

		if (!isQueueForAddressExistent(srcAddress))
		{
			std::list<Packet*>* queueList;
			packetQueueMap->insert(std::pair<int, std::list<Packet*>*>(srcAddress, queueList));
		}

		std::map<int, std::list<Packet*>*>::iterator queueIter = packetQueueMap->find(srcAddress);
		std::list<Packet*>* list = queueIter->second; // first key second value ;)
		list->push_back(packet);

	}
	else
	{
		packet->
	}

}

bool RoundRobinScheduler::isQueueForAddressExistent(int address)
{
	int keysFound = packetQueueMap->count(address);
	if (keysFound == 1)
	{
		return true;
	}
	else
	{
		return false;
	}
}

bool RoundRobinScheduler::isQueueSizeExceeded(int address)
{
	std::map<int, std::list<Packet*>*>::iterator queueIter = packetQueueMap->find(address);
	std::list<Packet*>* list = queueIter->second;

	return isQueueSizeExceeded(list);
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

