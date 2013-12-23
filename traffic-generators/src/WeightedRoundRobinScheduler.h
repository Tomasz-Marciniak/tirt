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
#include <omnetpp.h>
#include "Packet_m.h"

/**
 * Round Robin Scheduler
 * @author Tomasz Obszarny
 * @date 2013
 * @copyright GNU Public License.
 */
class WeightedRoundRobinScheduler : public cSimpleModule
{
	public:
		WeightedRoundRobinScheduler();
		virtual ~WeightedRoundRobinScheduler();

	protected:
		virtual void initialize();
		virtual void handleMessage(cMessage* msg);
		virtual void finish();
		void addPacketToQueue(Packet* packet);
		Packet* pickupNextPacketFromQueues();
		Packet* pickupPacketFromQueue(int gateId);
		bool isQueueForGateExistent(int gateId);
		bool isQueueSizeExceeded(int gateId);
		bool isQueueSizeExceeded(std::list<Packet*>* list);
		bool isOutAttachedWithChannel();
		std::list<Packet*>* getPacketListForGate(int gateId);
		void rotateIndex();
		int* getInputChannelIds();
		int getChannelIdByIndex(int index);
		void parseWeights(std::string weightsTokens, std::map<int, int>* weights, int channelCount) throw ();

		std::map<int, std::list<Packet*>*>*  packetQueueMap;
		unsigned int queueRotatorIndex;
		unsigned int weightRotation;
		cMessage* internalDispatchingMessage;
		int* inputChannelIds;

		//Parameters
		unsigned int queueSizeLimit;
		simtime_t delay;
		std::string weightsTokens;

		std::map<int, int>* weights;
		int* weightRanges;
		int channelCount;


		//Infrastructure
		cGate* out;
		cGate* in[];



};

#endif /* ROUNDROBINSCHEDULER_H_ */
