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

#include "PriorityBasedAdmissionControl.h"

Define_Module(PriorityBasedAdmissionControl)

PriorityBasedAdmissionControl::PriorityBasedAdmissionControl()
{

}

PriorityBasedAdmissionControl::~PriorityBasedAdmissionControl()
{

}

void PriorityBasedAdmissionControl::initialize()
{
	priority = par("priority");
	delay = par("delay");
	out = gate("out");
}

bool PriorityBasedAdmissionControl::accept(Packet* packet)
{
	int packetPriority = packet->getPriority();
	return packetPriority >= priority ;
}

void PriorityBasedAdmissionControl::handleMessage(cMessage* msg)
{

	EV<< "PriorityBasedAdmissionControl::handleMessage called for SenderModuleId " << msg->getSenderModuleId() << "\n";
	if (msg->isSelfMessage())
	{
		Packet* pck = check_and_cast<Packet*>(msg);

		if (accept(pck))
		{
			EV<< "PriorityBasedAdmissionControl accepted packet " << pck->getName() << " with priority " << pck->getPriority() << " \n";
			cChannel* channel = out->getChannel();
			if (channel)
			{
				simtime_t channelTransmissionFinishTime = channel->getTransmissionFinishTime();

				//Calculate time when channel will be available
				simtime_t sendPostponeTime = std::max(channelTransmissionFinishTime - simTime(), SIMTIME_ZERO);

				sendDelayed(pck, sendPostponeTime, out);
			}
			else
			send(pck, out);

			packetsSentOut++;
		}
		else
		{
			EV<< "PriorityBasedAdmissionControl rejected and removed packet " << pck->getName() << " with priority " << pck->getPriority() << "\n\t\t below limit " << priority << " \n";
			delete pck;
		}
	}
	else
	{
		lastPacketProcessTime = std::max(lastPacketProcessTime + delay, simTime() + delay);
		scheduleAt(lastPacketProcessTime, msg);

		packetsReceivedIn++;
	}
}

void PriorityBasedAdmissionControl::finish()
{

}
