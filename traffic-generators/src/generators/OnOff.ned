package traffic_generators.generators;

//
// Generates messages with a configurable limit.
//
simple OnOff
{
    parameters:
        int limit = default(10);
        int srcAddr = default(1);
    gates:
        output out;
        output self;
        input in;
}
