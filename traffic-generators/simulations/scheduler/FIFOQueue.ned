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

package traffic_generators.simulations.scheduler;

import traffic_generators.scheduler.FIFOQueue;
import traffic_generators.RandomPriorityPacketGenerator;
import traffic_generators.RandomSizePacketGenerator;
import traffic_generators.Receiver;
import traffic_generators.Source;


//
// TODO auto-generated type
//
network FIFOQueue
{
        submodules:
        FIFOQueue: traffic_generators.scheduler.FIFOQueue {
            @display("p=242,92");
        }
        receiver: Receiver {
            @display("p=379,92");
        }
        source: Source {
            @display("p=74,25");
        }
        exponential: traffic_generators.Exponential {
            @display("p=74,89");
        }
        poisson: traffic_generators.Poisson {
            @display("p=74,158");
        }
        randomSize: traffic_generators.RandomSizePacketGenerator {
            @display("p=160,197");
        }
    connections:
        FIFOQueue.out --> receiver.in;
        source.out --> FIFOQueue.in++;
        exponential.out --> FIFOQueue.in++;
        poisson.out --> FIFOQueue.in++;
        randomSize.out --> FIFOQueue.in++;
}
