package traffic_generators;

//
// Generates messages with a configurable limit.
//
simple OnOff
{
    parameters:
        int limit = default(10);
    gates:
        output out;
}
