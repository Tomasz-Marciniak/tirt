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

#ifndef SIZEBASEDADMISSIONCONTROL_H_
#define SIZEBASEDADMISSIONCONTROL_H_

#include "Packet_m.h"

namespace traffic_generators {

class SizeBasedAdmissionControl: public cSimpleModule {
public:
    SizeBasedAdmissionControl();
    virtual ~SizeBasedAdmissionControl();

protected:

    //Parameters
    int min;
    int max;
    double delay;

    //Infrastructure
    cGate* out;

    //Accumulators
    simtime_t lastPacketProcessTime;

    int32 packetsReceivedIn;
    int32 packetsSentOut;

    virtual void initialize();
    virtual bool accept(Packet* packet);
    virtual void handleMessage(cMessage* msg);
    virtual void finish();
};

} /* namespace traffic_generators */
#endif /* SIZEBASEDADMISSIONCONTROL_H_ */
