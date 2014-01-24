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

#ifndef PRIORITYQUEUE_H_
#define PRIORITYQUEUE_H_

#include <algorithm>
#include "Packet_m.h"

/**
 * Priority Queue Scheduler
 * @author Tomasz Obszarny
 * @date 2013
 * @copyright GNU Public License.
 */
class PriorityQueue : public cSimpleModule
{
	public:
		PriorityQueue();
		virtual ~PriorityQueue();

	protected:

		//Parameters
		int priority;
		double delay;
		int capacity;

		//Infrastructure
		cGate* out;

		//Accumulators
		simtime_t lastPacketProcessTime;
		cMessage* internalDispatchingMessage;

		int32 packetsReceivedIn;
		int32 packetsSentOut;
		std::list<Packet*>* limitedQueueList;

		virtual void initialize();
		virtual void handleMessage(cMessage* msg);
		virtual void finish();
		virtual void put2queue(Packet* packet);
		virtual Packet* getFromQueue();
};

#endif /* SIZEBASEDADMISSIONCONTROL_H_ */
