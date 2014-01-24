package traffic_generators.simulations.profilers;

import traffic_generators.receivers.Receiver;
import traffic_generators.generators.Source;

network LeakyBucketProfiler
{
    submodules:
        leakyBucketProfiler: traffic_generators.profilers.LeakyBucketProfiler {
            @display("p=242,92");
        }
        receiver: Receiver {
            @display("p=379,92");
        }
        source: Source {
            @display("p=74,25");
        }
        exponential: traffic_generators.generators.Exponential {
            @display("p=74,89");
        }
        poisson: traffic_generators.generators.Poisson {
            @display("p=74,158");
        }
    connections:
        leakyBucketProfiler.out --> receiver.in;
        source.out --> leakyBucketProfiler.in++;
        exponential.out --> leakyBucketProfiler.in++;
        poisson.out --> leakyBucketProfiler.in++;
}
