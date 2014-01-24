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

package traffic_generators.simulations.schedulers;

import traffic_generators.receivers.Receiver;
import traffic_generators.generators.Source;


//
// TODO auto-generated type
//
network RoundRobinScheduler
{
    submodules:
        roundRobinScheduler: traffic_generators.scheduler.RoundRobinScheduler {
            @display("p=242,92");
        }
        receiver: Receiver {
            @display("p=379,92");
        }
        source: Source {
            @display("p=74,25");
        }
        exponential: traffic_generators.generators.Exponential {
            @display("p=74,89");
        }
        poisson: traffic_generators.generators.Poisson {
            @display("p=74,158");
        }
    connections:
        roundRobinScheduler.out --> receiver.in;
        source.out --> roundRobinScheduler.in++;
        exponential.out --> roundRobinScheduler.in++;
        poisson.out --> roundRobinScheduler.in++;
}
