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
simple TokenBucketProfiler
{
    parameters:

        @class(TokenBucketProfiler);
        @display("i=block/join");

        double delay @unit("s") = default(0s);
        int queueSizeLimit = default(5);
        int tokensMax @unit("B") = default(1MiB);
        int tokensToAdd @unit("B") = default(64KiB);
    gates:
        input in[];
        output out;
}
