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

package traffic_generators;

//
// TODO auto-generated type
//
simple SizeBasedAdmissionControl
{
    parameters:
        volatile int min @unit("B") = default(0B);
        volatile int max @unit("B") = default(1KiB);

        @class(SizeBasedAdmissionControl);
        @display("i=block/control");
        
        volatile double delay @unit("s") = default(0s);
        
    gates:
        input  in[];
        output out;        
}
