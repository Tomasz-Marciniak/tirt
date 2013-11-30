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

#include "Source.h"
#include "Packet_m.h"

Define_Module(Source)
;

Source::Source()
{
	timerMessage = NULL;
}

Source::~Source()
{
	cancelAndDelete(timerMessage);
}

cMessage* Source::generateMessage()
{
	return new cMessage("timer");
}

void Source::initialize()
{
	timerMessage = generateMessage();
	scheduleAt(simTime(), timerMessage);
}

Packet* Source::generatePacket()
{
	return new Packet();
}

void Source::handleMessage(cMessage *msg)
{
	ASSERT(msg == timerMessage);

	Packet *pk = generatePacket();

	pk->setSrcAddr(1);
	pk->setDstAddr(1);
	send(pk, "out");
	scheduleAt(simTime() + par("sendInterval").doubleValue(), timerMessage);
}
