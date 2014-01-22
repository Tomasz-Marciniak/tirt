package traffic_generators;

simple DualLeakyBucketProfiler
{
    parameters:

        @class(DualLeakyBucketProfiler);
        @display("i=block/join");

        double delay @unit("s") = default(0s);
        int queueSizeLimit = default(5);

    gates:
        input in[];
        output out;
}
