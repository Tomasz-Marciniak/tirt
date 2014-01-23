package traffic_generators.scheduler;

simple RoundRobinScheduler
{
    parameters:

        @class(RoundRobinScheduler);
        @display("i=block/join");

        double delay @unit("s") = default(0s);
        int queueSizeLimit = default(5);

    gates:
        input in[];
        output out;
}
