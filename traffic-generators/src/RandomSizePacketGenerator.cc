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

#include <stdlib.h>
#include <time.h>
#include "RandomSizePacketGenerator.h"
#include "Source.h"

namespace traffic_generators {

Define_Module(RandomSizePacketGenerator)

RandomSizePacketGenerator::RandomSizePacketGenerator()
{
    srand(time(NULL));
}

RandomSizePacketGenerator::~RandomSizePacketGenerator()
{
    minPacketSize = par("minPacketSize");
    maxPacketSize = par("maxPacketSize");
}

void RandomSizePacketGenerator::initialize()
{


}

Packet* RandomSizePacketGenerator::generatePacket()
{
    Packet* packet = Source::generatePacket();

    // Precaution if someone decided to put max < min

    int spread = abs(maxPacketSize - minPacketSize);
    int sizeInBytes = minPacketSize + rand() % spread;

    packet->setByteLength(sizeInBytes);
    return packet;
}

} /* namespace traffic_generators */
