package traffic_generators.admissioncontrol;

simple BlockDeniedSourceAdmissionControl
{
    parameters:
        volatile int priority = default(3);

        @class(BlockDeniedSourceAdmissionControl);
        @display("i=block/control");

        double delay @unit("s") = default(0s);
        string blackList = default("");

    gates:
        input in[];
        output out;
}
