package traffic_generators.simulations;

import traffic_generators.admissioncontrol.PriorityBasedAdmissionControl;
import traffic_generators.generators.Poisson;
import traffic_generators.generators.RandomPriorityPacketGenerator;
import traffic_generators.profilers.LeakyBucketProfiler;
import traffic_generators.receivers.Receiver;
import traffic_generators.generators.Source;
import traffic_generators.schedulers.RoundRobinScheduler;


network TestNetwork1
{
    @display("bgl=2");
    submodules:
        randomPriorityPacketGenerator: RandomPriorityPacketGenerator {
            @display("p=24,27");
        }
        priorityBasedAdmissionControl: PriorityBasedAdmissionControl {
            @display("p=165,66");
        }
        roundRobinScheduler: RoundRobinScheduler {
            @display("p=244,169");
        }
        receiver: Receiver {
            @display("p=359,198");
        }
        leakyBucketProfiler: LeakyBucketProfiler {
            @display("p=109,149");
        }
    connections:
        randomPriorityPacketGenerator.out --> priorityBasedAdmissionControl.in++;
        roundRobinScheduler.out --> receiver.in;
        priorityBasedAdmissionControl.out --> leakyBucketProfiler.in++;
        leakyBucketProfiler.out --> roundRobinScheduler.in++;
}
