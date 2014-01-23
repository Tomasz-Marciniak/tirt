package traffic_generators.simulations.admissioncontrol;

import traffic_generators.admissioncontrol.PriorityBasedAdmissionControl;
import traffic_generators.RandomPriorityPacketGenerator;
import traffic_generators.RandomSizePacketGenerator;
import traffic_generators.Receiver;
import traffic_generators.Source;

network PriorityBasedAdmissionControl
{
    @display("bgl=3");
    submodules:
        receiver: Receiver {
            @display("p=347,126");
        }
        priorityBasedAdmissionControl: PriorityBasedAdmissionControl {
            @display("p=188,132");
        }
        randomPriorityPacketGenerator1: RandomPriorityPacketGenerator {
            @display("p=26,69");
        }
        randomPriorityPacketGenerator2: RandomPriorityPacketGenerator {
            @display("p=26,171");
        }
    connections:
        priorityBasedAdmissionControl.out --> receiver.in;
        randomPriorityPacketGenerator1.out --> priorityBasedAdmissionControl.in++;
        randomPriorityPacketGenerator2.out --> priorityBasedAdmissionControl.in++;
}
