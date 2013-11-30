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

#include "OnOff.h"

Define_Module(OnOff)
;

OnOff::OnOff()
{
	timerMessage = NULL;
}

OnOff::~OnOff()
{
	cancelAndDelete(timerMessage);
}

void OnOff::initialize()
{
	counter = 0;
	limit = par("limit");
	timerMessage = new cMessage("timer");
	scheduleAt(simTime(), timerMessage);
}

void OnOff::handleMessage(cMessage *msg)
{
	counter++;

	EV<< "Counter:" << counter << ", limit:" << limit;

	ASSERT(msg == timerMessage);
	cMessage *job = new cMessage("job");
	send(job, "out");
	scheduleAt(simTime(), timerMessage);
}

void OnOff::activity()
{

	EV<< "CZEKAJ!";

	if(counter>limit)
	{
		if(counter==limit*2)
		{
			counter = 0;
		}
		wait(4000);
	}
}
