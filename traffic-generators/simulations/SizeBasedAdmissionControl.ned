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

package traffic_generators.simulations;

import traffic_generators.Receiver;
import traffic_generators.Source;


//
// TODO auto-generated type
//
network SizeBasedAdmissionControl
{
    submodules:
        source: Source {
            @display("p=73,132");
        }
        sizeBasedAdmissionControl: traffic_generators.SizeBasedAdmissionControl {
            @display("p=211,132");
        }
        receiver: Receiver {
            @display("p=346,132");
        }
    connections:
        source.out --> sizeBasedAdmissionControl.in++;
        sizeBasedAdmissionControl.out --> receiver.in;
}
