package traffic_generators.admissioncontrol;

simple PriorityBasedAdmissionControl
{
    parameters:
        volatile int priority = default(3);

        @class(PriorityBasedAdmissionControl);
        @display("i=block/control");

        double delay @unit("s") = default(0s);

    gates:
        input in[];
        output out;
}
