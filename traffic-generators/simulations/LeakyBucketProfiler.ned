package traffic_generators.simulations;

import traffic_generators.Receiver;
import traffic_generators.Source;

network LeakyBucketProfiler
{
    submodules:
        leakyBucketProfiler: traffic_generators.LeakyBucketProfiler {
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
    connections:
        leakyBucketProfiler.out --> receiver.in;
        source.out --> leakyBucketProfiler.in++;
        exponential.out --> leakyBucketProfiler.in++;
        poisson.out --> leakyBucketProfiler.in++;
}
