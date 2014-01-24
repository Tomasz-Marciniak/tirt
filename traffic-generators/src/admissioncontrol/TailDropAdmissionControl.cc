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

#include "TailDropAdmissionControl.h"

Define_Module(TailDropAdmissionControl)

TailDropAdmissionControl::TailDropAdmissionControl()
{
	//Statistics
	signalReceived = registerSignal("accepted");
	signalDropped = registerSignal("dropped");
	signalSent = registerSignal("sent");

    histogram.setRange(0, 1700);
    histogram.setNumCells(1000);

    packetsDropped = 0;
    packetsReceived = 0;
    packetsSent = 0;
}

TailDropAdmissionControl::~TailDropAdmissionControl()
{

}

void TailDropAdmissionControl::initialize()
{
	//Parameters
	delay = par("delay");
	capacity = par("capacity");

	//gates
	out = gate("out");

	//accumulators
	limitedQueueList = new std::list<Packet*>();

	internalDispatchingMessage = new cMessage("TailDropAdmissionControl");

}

void TailDropAdmissionControl::handleMessage(cMessage* msg)
{

	EV<< "TailDropAdmissionControl::handleMessage called for SenderModuleId " << msg->getSenderModuleId() << "\n";
	if (msg == internalDispatchingMessage)
	{

		Packet* pck = getFromQueue();

		if(pck)
		{

			cChannel* channel = out->getChannel();

			simtime_t sendPostponeTime;
			if(channel)
			{
				simtime_t channelTransmissionFinishTime = channel->getTransmissionFinishTime();

				//Calculate time when channel will be available
				sendPostponeTime = channelTransmissionFinishTime - simTime();

				simtime_t simtimePlusDelay = simTime() + delay;

				if (sendPostponeTime < simtimePlusDelay)
				{
					sendPostponeTime = simtimePlusDelay;
				}

			}
			else
			{
				sendPostponeTime = simTime() + delay;
			}

			sendDelayed(pck, sendPostponeTime, out);
			emit(signalSent, sendPostponeTime);

			packetsSent++;
		}

	}
	else
	{
		Packet* pck = check_and_cast<Packet*>(msg);

		put2queue(pck);

		packetsReceived++;
		emit(signalReceived, simTime());

		if(!internalDispatchingMessage->isScheduled())
		{
			scheduleAt(simTime() + delay, internalDispatchingMessage);
		}

	}
}

void TailDropAdmissionControl::put2queue(Packet* packet)
{
	int currentCapacity = limitedQueueList->size();
	if (currentCapacity < capacity)
	{
		EV<< "TailDropAdmissionControl::put2queue: Packet accepted by queue. Used capacity = "<< currentCapacity << " of " << capacity << endl;
		limitedQueueList->push_back(packet);
	}
	else
	{
		EV<< "TailDropAdmissionControl::put2queue: All capacity used = "<< currentCapacity << endl;
		Packet* packetDrop = limitedQueueList->back();
		EV<< "TailDropAdmissionControl::put2queue: Packet " << *packetDrop << " will be deleted" << endl;
		delete(packetDrop);
		packetsDropped++;
		emit(signalDropped, simTime());
		histogram.collect(simTime());
		limitedQueueList->push_back(packet);
		EV<< "TailDropAdmissionControl::put2queue: Packet " << *packet << " added to tail" << endl;
	}

}

Packet* TailDropAdmissionControl::getFromQueue()
{
	if (limitedQueueList->size() > 0)
	{
		Packet* packet = limitedQueueList->front();
		limitedQueueList->pop_front();
		return packet;
	}
	else
	{
		return NULL;
	}
}

void TailDropAdmissionControl::finish()
{
    recordScalar("Received count", packetsReceived);
    recordScalar("Sent count", packetsSent);
    recordScalar("Dropped count", packetsDropped);
    histogram.recordAs("Histogram");
}

