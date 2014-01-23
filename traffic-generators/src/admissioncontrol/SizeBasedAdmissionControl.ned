package traffic_generators.admissioncontrol;

simple SizeBasedAdmissionControl
{
    parameters:
        volatile int minPacketSize @unit("B") = default(0B);
        volatile int maxPacketSize @unit("B") = default(1KiB);

        @class(SizeBasedAdmissionControl);
        @display("i=block/control");

        double delay @unit("s") = default(0s);

    gates:
        input in[];
        output out;
}
