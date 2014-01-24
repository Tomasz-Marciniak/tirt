package traffic_generators.simulations.admissioncontrol;

import traffic_generators.admissioncontrol.PriorityBasedAdmissionControl;
import traffic_generators.generators.RandomPriorityPacketGenerator;
import traffic_generators.generators.RandomSizePacketGenerator;
import traffic_generators.receivers.Receiver;
import traffic_generators.generators.Source;

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
