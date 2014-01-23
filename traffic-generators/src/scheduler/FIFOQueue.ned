package traffic_generators.scheduler;

simple FIFOQueue
{
    parameters:
        volatile int priority = default(3);

        @class(PriorityQueue);
        @display("i=block/control");

        double delay @unit("s") = default(0s);
        int capacity = default(5);

    gates:
        input in[];
        output out;
}
