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

#include "BlockDeniedSourceAdmissionControl.h"

Define_Module(BlockDeniedSourceAdmissionControl)

BlockDeniedSourceAdmissionControl::BlockDeniedSourceAdmissionControl()
{
	blackList = new std::list<int>;

	//histogram = new cDoubleHistogram("Histogram", 1000);

	EV<< "list size " << blackList->size() << "\n";
}

BlockDeniedSourceAdmissionControl::~BlockDeniedSourceAdmissionControl()
{
	rejected = 0;
	accepted = 0;
}

void BlockDeniedSourceAdmissionControl::initialize()
{
	blockedPar = par("blackList").stdstringValue();
	delay = par("delay");
	out = gate("out");

	parseSources(blockedPar, blackList);

	//Statistics
	signalAccepted = registerSignal("accepted");
	signalRejected = registerSignal("rejected");

    histogram.setRange(0, 1700);
    histogram.setNumCells(1000);

}

bool BlockDeniedSourceAdmissionControl::accept(Packet* packet)
{
	return !isInTheList(packet->getSrcAddr(), blackList);
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
			EV<< "BlockDeniedSourceAdmissionControl accepted packet " << pck->getName() << " from source address " << pck->getSrcAddr() << " \n";
			cChannel* channel = out->getChannel();
			if (channel)
			{
				simtime_t channelTransmissionFinishTime = channel->getTransmissionFinishTime();

				//Calculate time when channel will be available
				simtime_t sendPostponeTime = std::max(channelTransmissionFinishTime - simTime(), SIMTIME_ZERO);

				sendDelayed(pck, sendPostponeTime, out);
			}
			else
			{
				send(pck, out);
			}

			accepted++;
			packetsSentOut++;
			emit(signalAccepted, accepted);

			histogram.collect(simTime());
		}
		else
		{
			EV<< "BlockDeniedSourceAdmissionControl rejected and removed packet " << pck->getName() << " from source address " << pck->getSrcAddr() << "\n";
			delete pck;
			rejected++;
			emit(signalRejected, rejected);
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
    recordScalar("Rejected count", rejected);
    recordScalar("Accepted count", accepted);
    histogram.recordAs("Histogram");
}

void BlockDeniedSourceAdmissionControl::parseSources(std::string blockedSources, std::list<int>* blockedList) throw ()
{
	cStringTokenizer moduleTokenizer(blockedSources.c_str());

	while (moduleTokenizer.hasMoreTokens())
	{

		printList(blockedList);
		std::string blockedSource(moduleTokenizer.nextToken());

		int srcAddr = atoi(blockedSource.c_str());

		EV<< "BlockDeniedSourceAdmissionControl::parseSources() adding source " << blockedSource << " \n";
		blockedList->push_back(srcAddr);

	}
}

bool BlockDeniedSourceAdmissionControl::isInTheList(int item, std::list<int>* list)
{
	EV<< "BlockDeniedSourceAdmissionControl::isInTheList() called for " << item << " \n";

	bool found = false;
	int i = 0;
	for (std::list<int>::const_iterator iterator = list->begin(), end = list->end(); iterator != end && !found; ++iterator)
	{
		int currentBlockedListElement = *iterator;
		if (currentBlockedListElement == item)
		{
			EV<< "BlockDeniedSourceAdmissionControl::isInTheList() found " << item << " on list position " << i++ << ", item "<< currentBlockedListElement << "\n";
			found = true;
		}
	}

	return found;
}

void BlockDeniedSourceAdmissionControl::printList(std::list<int>* list)
{
	EV<< "BlockDeniedSourceAdmissionControl::printList() called \n";

	int i=0;
	if(list->begin()!=list->end())
	{
		for (std::list<int>::const_iterator iterator = list->begin(), end = list->end(); iterator != end; ++iterator)
		{
			int currentBlockedListElement = *iterator;
			EV<< "Item " << i++ << " is " << currentBlockedListElement << "\n";

		}
	}

}

