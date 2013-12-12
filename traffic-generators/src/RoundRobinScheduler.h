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

#ifndef ROUNDROBINSCHEDULER_H_
#define ROUNDROBINSCHEDULER_H_

#include <stdlib.h>
#include <list>
#include <omnetpp.h>
#include "Packet_m.h"

class RoundRobinScheduler : public cSimpleModule
{
	public:
		RoundRobinScheduler();
		virtual ~RoundRobinScheduler();

	protected:
		virtual void initialize();
		virtual void handleMessage(cMessage* msg);
		virtual void finish();
		void addPacketToQueue(Packet* packet);
		bool isQueueForAddressExistent(int address);
		bool isQueueSizeExceeded(int address);


		//std::list< std::list<Packet*>* > packetList;

		std::map<int, std::list<Packet*>*>*  packetQueueMap;

		//Parameters
		unsigned int queueSizeLimit;


		//Infrastructure
		cGate* out;

};

#endif /* ROUNDROBINSCHEDULER_H_ */
