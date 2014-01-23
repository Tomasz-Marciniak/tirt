package traffic_generators.simulations.profiler;

import traffic_generators.Receiver;
import traffic_generators.Source;

network TokenBucketProfiler
{
    submodules:
        tokenBucketProfiler: traffic_generators.profiler.TokenBucketProfiler {
            @display("p=242,92");
        }
        receiver: Receiver {
            @display("p=379,92");
        }
        source: Source {
            @display("p=74,25");
        }
        exponential: traffic_generators.Exponential {
            @display("p=74,89");
        }
        poisson: traffic_generators.Poisson {
            @display("p=74,158");
        }
        randomSize: traffic_generators.RandomSizePacketGenerator {
            @display("p=160,197");
        }
    connections:
        tokenBucketProfiler.out --> receiver.in;
        source.out --> tokenBucketProfiler.in++;
        exponential.out --> tokenBucketProfiler.in++;
        poisson.out --> tokenBucketProfiler.in++;
        randomSize.out --> tokenBucketProfiler.in++;
}
