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

#include "Receiver.h"

namespace traffic_generators {

Define_Module(Receiver);

void Receiver::initialize()
{
    lastArrival = simTime();
    iaTimeHistogram.setName("interarrival times");
    arrivalsVector.setName("arrivals");
    arrivalsVector.setInterpolationMode(cOutVector::NONE);
}

void Receiver::handleMessage(cMessage *msg)
{
    simtime_t d = simTime() - lastArrival;
    EV << 'Received ' << msg->getName() << ' at ' << d << endl;
    delete msg;

    iaTimeHistogram.collect(d);
    arrivalsVector.record(1);

    lastArrival = simTime();
}

void Receiver::finish()
{
    recordStatistic(&iaTimeHistogram);
}

}; // namespace
