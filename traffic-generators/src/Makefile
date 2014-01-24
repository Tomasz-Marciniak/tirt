#
# OMNeT++/OMNEST Makefile for traffic-generators
#
# This file was generated with the command:
#  opp_makemake -f --deep
#

# Name of target to be created (-o option)
TARGET = traffic-generators$(EXE_SUFFIX)

# User interface (uncomment one) (-u option)
USERIF_LIBS = $(ALL_ENV_LIBS) # that is, $(TKENV_LIBS) $(CMDENV_LIBS)
#USERIF_LIBS = $(CMDENV_LIBS)
#USERIF_LIBS = $(TKENV_LIBS)

# C++ include paths (with -I)
INCLUDE_PATH = \
    -I. \
    -Iadmissioncontrol \
    -Igenerators \
    -Imessages \
    -Iprofilers \
    -Ireceivers \
    -Ischedulers

# Additional object and library files to link with
EXTRA_OBJS =

# Additional libraries (-L, -l options)
LIBS =

# Output directory
PROJECT_OUTPUT_DIR = ../out
PROJECTRELATIVE_PATH = src
O = $(PROJECT_OUTPUT_DIR)/$(CONFIGNAME)/$(PROJECTRELATIVE_PATH)

# Object files for local .cc and .msg files
OBJS = \
    $O/admissioncontrol/BlockDeniedSourceAdmissionControl.o \
    $O/admissioncontrol/PriorityBasedAdmissionControl.o \
    $O/admissioncontrol/SizeBasedAdmissionControl.o \
    $O/admissioncontrol/TailDropAdmissionControl.o \
    $O/generators/Exponential.o \
    $O/generators/OnOff.o \
    $O/generators/Poisson.o \
    $O/generators/RandomPriorityPacketGenerator.o \
    $O/generators/RandomSizePacketGenerator.o \
    $O/generators/Source.o \
    $O/profilers/DualLeakyBucketProfiler.o \
    $O/profilers/LeakyBucketProfiler.o \
    $O/profilers/LeakyBucketProfiler2.o \
    $O/profilers/TokenBucketProfiler.o \
    $O/receivers/Receiver.o \
    $O/schedulers/FIFOQueue.o \
    $O/schedulers/PriorityQueue.o \
    $O/schedulers/RoundRobinScheduler.o \
    $O/schedulers/WeightedRoundRobinScheduler.o \
    $O/messages/Packet_m.o

# Message files
MSGFILES = \
    messages/Packet.msg

#------------------------------------------------------------------------------

# Pull in OMNeT++ configuration (Makefile.inc or configuser.vc)

ifneq ("$(OMNETPP_CONFIGFILE)","")
CONFIGFILE = $(OMNETPP_CONFIGFILE)
else
ifneq ("$(OMNETPP_ROOT)","")
CONFIGFILE = $(OMNETPP_ROOT)/Makefile.inc
else
CONFIGFILE = $(shell opp_configfilepath)
endif
endif

ifeq ("$(wildcard $(CONFIGFILE))","")
$(error Config file '$(CONFIGFILE)' does not exist -- add the OMNeT++ bin directory to the path so that opp_configfilepath can be found, or set the OMNETPP_CONFIGFILE variable to point to Makefile.inc)
endif

include $(CONFIGFILE)

# Simulation kernel and user interface libraries
OMNETPP_LIB_SUBDIR = $(OMNETPP_LIB_DIR)/$(TOOLCHAIN_NAME)
OMNETPP_LIBS = -L"$(OMNETPP_LIB_SUBDIR)" -L"$(OMNETPP_LIB_DIR)" -loppmain$D $(USERIF_LIBS) $(KERNEL_LIBS) $(SYS_LIBS)

COPTS = $(CFLAGS)  $(INCLUDE_PATH) -I$(OMNETPP_INCL_DIR)
MSGCOPTS = $(INCLUDE_PATH)

# we want to recompile everything if COPTS changes,
# so we store COPTS into $COPTS_FILE and have object
# files depend on it (except when "make depend" was called)
COPTS_FILE = $O/.last-copts
ifneq ($(MAKECMDGOALS),depend)
ifneq ("$(COPTS)","$(shell cat $(COPTS_FILE) 2>/dev/null || echo '')")
$(shell $(MKPATH) "$O" && echo "$(COPTS)" >$(COPTS_FILE))
endif
endif

#------------------------------------------------------------------------------
# User-supplied makefile fragment(s)
# >>>
# <<<
#------------------------------------------------------------------------------

# Main target
all: $O/$(TARGET)
	$(Q)$(LN) $O/$(TARGET) .

$O/$(TARGET): $(OBJS)  $(wildcard $(EXTRA_OBJS)) Makefile
	@$(MKPATH) $O
	@echo Creating executable: $@
	$(Q)$(CXX) $(LDFLAGS) -o $O/$(TARGET)  $(OBJS) $(EXTRA_OBJS) $(AS_NEEDED_OFF) $(WHOLE_ARCHIVE_ON) $(LIBS) $(WHOLE_ARCHIVE_OFF) $(OMNETPP_LIBS)

.PHONY: all clean cleanall depend msgheaders

.SUFFIXES: .cc

$O/%.o: %.cc $(COPTS_FILE)
	@$(MKPATH) $(dir $@)
	$(qecho) "$<"
	$(Q)$(CXX) -c $(COPTS) -o $@ $<

%_m.cc %_m.h: %.msg
	$(qecho) MSGC: $<
	$(Q)$(MSGC) -s _m.cc $(MSGCOPTS) $?

msgheaders: $(MSGFILES:.msg=_m.h)

clean:
	$(qecho) Cleaning...
	$(Q)-rm -rf $O
	$(Q)-rm -f traffic-generators traffic-generators.exe libtraffic-generators.so libtraffic-generators.a libtraffic-generators.dll libtraffic-generators.dylib
	$(Q)-rm -f ./*_m.cc ./*_m.h
	$(Q)-rm -f admissioncontrol/*_m.cc admissioncontrol/*_m.h
	$(Q)-rm -f generators/*_m.cc generators/*_m.h
	$(Q)-rm -f messages/*_m.cc messages/*_m.h
	$(Q)-rm -f profilers/*_m.cc profilers/*_m.h
	$(Q)-rm -f receivers/*_m.cc receivers/*_m.h
	$(Q)-rm -f schedulers/*_m.cc schedulers/*_m.h

cleanall: clean
	$(Q)-rm -rf $(PROJECT_OUTPUT_DIR)

depend:
	$(qecho) Creating dependencies...
	$(Q)$(MAKEDEPEND) $(INCLUDE_PATH) -f Makefile -P\$$O/ -- $(MSG_CC_FILES)  ./*.cc admissioncontrol/*.cc generators/*.cc messages/*.cc profilers/*.cc receivers/*.cc schedulers/*.cc

# DO NOT DELETE THIS LINE -- make depend depends on it.
$O/admissioncontrol/BlockDeniedSourceAdmissionControl.o: admissioncontrol/BlockDeniedSourceAdmissionControl.cc \
	admissioncontrol/BlockDeniedSourceAdmissionControl.h \
	messages/Packet_m.h
$O/admissioncontrol/PriorityBasedAdmissionControl.o: admissioncontrol/PriorityBasedAdmissionControl.cc \
	admissioncontrol/PriorityBasedAdmissionControl.h \
	messages/Packet_m.h
$O/admissioncontrol/SizeBasedAdmissionControl.o: admissioncontrol/SizeBasedAdmissionControl.cc \
	admissioncontrol/SizeBasedAdmissionControl.h \
	messages/Packet_m.h
$O/admissioncontrol/TailDropAdmissionControl.o: admissioncontrol/TailDropAdmissionControl.cc \
	admissioncontrol/TailDropAdmissionControl.h \
	messages/Packet_m.h
$O/generators/Exponential.o: generators/Exponential.cc \
	generators/Exponential.h \
	generators/Source.h \
	messages/Packet_m.h
$O/generators/OnOff.o: generators/OnOff.cc \
	generators/OnOff.h
$O/generators/Poisson.o: generators/Poisson.cc \
	generators/Poisson.h \
	generators/Source.h \
	messages/Packet_m.h
$O/generators/RandomPriorityPacketGenerator.o: generators/RandomPriorityPacketGenerator.cc \
	generators/RandomPriorityPacketGenerator.h \
	generators/Source.h \
	messages/Packet_m.h
$O/generators/RandomSizePacketGenerator.o: generators/RandomSizePacketGenerator.cc \
	generators/RandomSizePacketGenerator.h \
	generators/Source.h \
	messages/Packet_m.h
$O/generators/Source.o: generators/Source.cc \
	generators/Source.h \
	messages/Packet_m.h
$O/messages/Packet_m.o: messages/Packet_m.cc \
	messages/Packet_m.h
$O/profilers/DualLeakyBucketProfiler.o: profilers/DualLeakyBucketProfiler.cc \
	generators/ProfilerType.h \
	messages/Packet_m.h \
	profilers/DualLeakyBucketProfiler.h
$O/profilers/LeakyBucketProfiler.o: profilers/LeakyBucketProfiler.cc \
	generators/ProfilerType.h \
	messages/Packet_m.h \
	profilers/LeakyBucketProfiler.h
$O/profilers/LeakyBucketProfiler2.o: profilers/LeakyBucketProfiler2.cc \
	generators/ProfilerType.h \
	messages/Packet_m.h \
	profilers/LeakyBucketProfiler2.h
$O/profilers/TokenBucketProfiler.o: profilers/TokenBucketProfiler.cc \
	generators/ProfilerType.h \
	messages/Packet_m.h \
	profilers/TokenBucketProfiler.h
$O/receivers/Receiver.o: receivers/Receiver.cc \
	messages/Packet_m.h \
	receivers/Receiver.h
$O/schedulers/FIFOQueue.o: schedulers/FIFOQueue.cc \
	messages/Packet_m.h \
	schedulers/FIFOQueue.h
$O/schedulers/PriorityQueue.o: schedulers/PriorityQueue.cc \
	messages/Packet_m.h \
	schedulers/PriorityQueue.h
$O/schedulers/RoundRobinScheduler.o: schedulers/RoundRobinScheduler.cc \
	messages/Packet_m.h \
	schedulers/RoundRobinScheduler.h \
	schedulers/SchedulerType.h
$O/schedulers/WeightedRoundRobinScheduler.o: schedulers/WeightedRoundRobinScheduler.cc \
	messages/Packet_m.h \
	schedulers/SchedulerType.h \
	schedulers/WeightedRoundRobinScheduler.h

