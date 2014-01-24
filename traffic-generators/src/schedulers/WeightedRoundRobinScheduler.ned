package traffic_generators.schedulers;

simple WeightedRoundRobinScheduler
{
    parameters:

        @class(WeightedRoundRobinScheduler);
        @display("i=block/join");

        double delay @unit("s") = default(0s);
        int queueSizeLimit = default(5);
        string weights = default("");

    gates:
        input in[];
        output out;
}
