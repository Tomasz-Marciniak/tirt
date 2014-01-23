package traffic_generators.profiler;

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
