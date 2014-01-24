package traffic_generators.simulations.admissioncontrol;

import traffic_generators.receivers.Receiver;
import traffic_generators.generators.Source;

network BlockDeniedSourceAdmissionControl
{
    submodules:
        blockDeniedSourceAdmissionControl: traffic_generators.admissioncontrol.BlockDeniedSourceAdmissionControl {
            @display("p=242,92");
        }
        receiver: Receiver {
            @display("p=379,92");
        }
        source3: Source {
            @display("p=74,104");
        }
        source1: Source {
            @display("p=74,40");
        }
        source2: Source {
            @display("p=74,175");
        }
    connections:
        blockDeniedSourceAdmissionControl.out --> receiver.in;
        source3.out --> blockDeniedSourceAdmissionControl.in++;
        source1.out --> blockDeniedSourceAdmissionControl.in++;
        source2.out --> blockDeniedSourceAdmissionControl.in++;
}
