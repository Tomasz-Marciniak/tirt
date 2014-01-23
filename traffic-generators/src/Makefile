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
INCLUDE_PATH = -I. -Iadmissioncontrol -Iprofiler -Ischeduler

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
    $O/Source.o \
    $O/OnOff.o \
    $O/RandomPriorityPacketGenerator.o \
    $O/Exponential.o \
    $O/Receiver.o \
    $O/RandomSizePacketGenerator.o \
    $O/Poisson.o \
    $O/admissioncontrol/BlockDeniedSourceAdmissionControl.o \
    $O/admissioncontrol/PriorityBasedAdmissionControl.o \
    $O/admissioncontrol/SizeBasedAdmissionControl.o \
    $O/profiler/LeakyBucketProfiler.o \
    $O/profiler/DualLeakyBucketProfiler.o \
    $O/profiler/TokenBucketProfiler.o \
    $O/scheduler/FIFOQueue.o \
    $O/scheduler/PriorityQueue.o \
    $O/scheduler/RoundRobinScheduler.o \
    $O/scheduler/WeightedRoundRobinScheduler.o \
    $O/Packet_m.o

# Message files
MSGFILES = \
    Packet.msg

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
	$(Q)-rm -f profiler/*_m.cc profiler/*_m.h
	$(Q)-rm -f scheduler/*_m.cc scheduler/*_m.h

cleanall: clean
	$(Q)-rm -rf $(PROJECT_OUTPUT_DIR)

depend:
	$(qecho) Creating dependencies...
	$(Q)$(MAKEDEPEND) $(INCLUDE_PATH) -f Makefile -P\$$O/ -- $(MSG_CC_FILES)  ./*.cc admissioncontrol/*.cc profiler/*.cc scheduler/*.cc

# DO NOT DELETE THIS LINE -- make depend depends on it.
$O/Exponential.o: Exponential.cc \
	Exponential.h \
	Packet_m.h \
	Source.h
$O/OnOff.o: OnOff.cc \
	OnOff.h
$O/Packet_m.o: Packet_m.cc \
	Packet_m.h
$O/Poisson.o: Poisson.cc \
	Packet_m.h \
	Poisson.h \
	Source.h
$O/RandomPriorityPacketGenerator.o: RandomPriorityPacketGenerator.cc \
	Packet_m.h \
	RandomPriorityPacketGenerator.h \
	Source.h
$O/RandomSizePacketGenerator.o: RandomSizePacketGenerator.cc \
	Packet_m.h \
	RandomSizePacketGenerator.h \
	Source.h
$O/Receiver.o: Receiver.cc \
	Packet_m.h \
	Receiver.h
$O/Source.o: Source.cc \
	Packet_m.h \
	Source.h
$O/admissioncontrol/BlockDeniedSourceAdmissionControl.o: admissioncontrol/BlockDeniedSourceAdmissionControl.cc \
	Packet_m.h \
	admissioncontrol/BlockDeniedSourceAdmissionControl.h
$O/admissioncontrol/PriorityBasedAdmissionControl.o: admissioncontrol/PriorityBasedAdmissionControl.cc \
	Packet_m.h \
	admissioncontrol/PriorityBasedAdmissionControl.h
$O/admissioncontrol/SizeBasedAdmissionControl.o: admissioncontrol/SizeBasedAdmissionControl.cc \
	Packet_m.h \
	admissioncontrol/SizeBasedAdmissionControl.h
$O/profiler/DualLeakyBucketProfiler.o: profiler/DualLeakyBucketProfiler.cc \
	Packet_m.h \
	ProfilerType.h \
	profiler/DualLeakyBucketProfiler.h
$O/profiler/LeakyBucketProfiler.o: profiler/LeakyBucketProfiler.cc \
	Packet_m.h \
	ProfilerType.h \
	profiler/LeakyBucketProfiler.h
$O/profiler/TokenBucketProfiler.o: profiler/TokenBucketProfiler.cc \
	Packet_m.h \
	ProfilerType.h \
	profiler/TokenBucketProfiler.h
$O/scheduler/FIFOQueue.o: scheduler/FIFOQueue.cc \
	Packet_m.h \
	scheduler/FIFOQueue.h
$O/scheduler/PriorityQueue.o: scheduler/PriorityQueue.cc \
	Packet_m.h \
	scheduler/PriorityQueue.h
$O/scheduler/RoundRobinScheduler.o: scheduler/RoundRobinScheduler.cc \
	Packet_m.h \
	SchedulerType.h \
	scheduler/RoundRobinScheduler.h
$O/scheduler/WeightedRoundRobinScheduler.o: scheduler/WeightedRoundRobinScheduler.cc \
	Packet_m.h \
	SchedulerType.h \
	scheduler/WeightedRoundRobinScheduler.h

