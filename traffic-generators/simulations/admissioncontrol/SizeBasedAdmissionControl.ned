package traffic_generators.simulations.admissioncontrol;

import traffic_generators.generators.RandomSizePacketGenerator;
import traffic_generators.receivers.Receiver;
import traffic_generators.generators.Source;

network SizeBasedAdmissionControl
{
    @display("bgl=3");
    submodules:
        sizeBasedAdmissionControl: traffic_generators.admissioncontrol.SizeBasedAdmissionControl {
            @display("p=211,132");
        }
        receiver: Receiver {
            @display("p=346,132");
        }
        randomSizePacketGenerator1: RandomSizePacketGenerator {
            @display("p=31,74");
        }
        randomSizePacketGenerator2: RandomSizePacketGenerator {
            @display("p=31,201");
        }
    connections:
        sizeBasedAdmissionControl.out --> receiver.in;
        randomSizePacketGenerator1.out --> sizeBasedAdmissionControl.in++;
        randomSizePacketGenerator2.out --> sizeBasedAdmissionControl.in++;
}
