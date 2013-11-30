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

#include "SizeBasedAdmissionControl.h"

Define_Module(SizeBasedAdmissionControl)

SizeBasedAdmissionControl::SizeBasedAdmissionControl()
{

}

SizeBasedAdmissionControl::~SizeBasedAdmissionControl()
{

}

void SizeBasedAdmissionControl::initialize()
{
    minPacketSize = par("minPacketSize");
    maxPacketSize = par("maxPacketSize");
    delay = par("delay");
    out = gate("out");
}

bool SizeBasedAdmissionControl::accept(Packet* packet)
{
    int64 packetSize = packet->getByteLength();
    return packetSize >= minPacketSize && packetSize <= maxPacketSize;
}

void SizeBasedAdmissionControl::handleMessage(cMessage* msg)
{
    if (msg->isSelfMessage())
    {
        Packet* pck = check_and_cast<Packet*>(msg);

        if (accept(pck))
        {
            EV<< "SizeBasedAdmissionControl accepted packet " << pck->getName() << " with size " << pck->getByteLength() << " \n";
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
            EV<< "SizeBasedAdmissionControl rejected and removed packet " << pck->getName() << " \n";
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

void SizeBasedAdmissionControl::finish()
{

}
