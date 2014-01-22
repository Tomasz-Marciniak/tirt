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

#include <algorithm>
#include "BlockDeniedSourceAdmissionControl.h"

Define_Module(BlockDeniedSourceAdmissionControl)

BlockDeniedSourceAdmissionControl::BlockDeniedSourceAdmissionControl()
{
	blockedList = new std::list<std::string*>();
}

BlockDeniedSourceAdmissionControl::~BlockDeniedSourceAdmissionControl()
{

}

void BlockDeniedSourceAdmissionControl::initialize()
{
	blockedPar = par("blocked").stdstringValue();
	delay = par("delay");
	out = gate("out");

	parseSources(blockedPar, blockedList);

}

bool BlockDeniedSourceAdmissionControl::accept(Packet* packet)
{
	int packetPriority = packet->getPriority();
//	return packetPriority >= priority;
	return false;
}

void BlockDeniedSourceAdmissionControl::handleMessage(cMessage* msg)
{

	EV<< "BlockDeniedSourceAdmissionControl::handleMessage called for SenderModuleId " << msg->getSenderModuleId() << "\n";
	if (msg->isSelfMessage())
	{
		Packet* pck = check_and_cast<Packet*>(msg);

		EV << "Address of the package " <<pck->getSrcAddr() << "\n";

		if (accept(pck))
		{
			EV<< "BlockDeniedSourceAdmissionControl accepted packet " << pck->getName() << " with priority " << pck->getPriority() << " \n";
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
//			EV<< "BlockDeniedSourceAdmissionControl rejected and removed packet " << pck->getName() << " with priority " << pck->getPriority() << "\n\t\t below limit " << priority << " \n";
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

void BlockDeniedSourceAdmissionControl::finish()
{

}

void BlockDeniedSourceAdmissionControl::parseSources(std::string blockedSources, std::list<std::string*>* blockedList) throw ()
{
	cStringTokenizer moduleTokenizer(blockedSources.c_str());

	while (moduleTokenizer.hasMoreTokens())
	{

		std::string blockedSource(moduleTokenizer.nextToken());

//		for (std::list<std::string*>::const_iterator iterator = blockedList->begin(), end = blockedList->end(); iterator != end && !found; ++iterator)
//		{
//			std::string *currentBlockedListElement = *iterator;
//			if (blockedSource == *currentBlockedListElement)
//			{
//				found = true;
//				break;
//			}
//		}

		if (!isInTheList(blockedSource, blockedList))
		{
			EV<< "BlockDeniedSourceAdmissionControl::parseSources() adding source " << blockedSource << " \n";
			blockedList->push_back(&blockedSource);
		}
	}
}

bool BlockDeniedSourceAdmissionControl::isInTheList(std::string item, std::list<std::string*>* list)
{
	EV<< "BlockDeniedSourceAdmissionControl::isInTheList() called" << " \n";
	std::list<std::string*>::const_iterator end = list->end();
	std::list<std::string*>::const_iterator fetchedItem = std::find(list->begin(), list->end(), &item);

	return (fetchedItem != list->end());
}

