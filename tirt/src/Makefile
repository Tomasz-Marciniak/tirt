#
# OMNeT++/OMNEST Makefile for tirt
#
# This file was generated with the command:
#  opp_makemake -f --deep
#

# Name of target to be created (-o option)
TARGET = tirt$(EXE_SUFFIX)

# User interface (uncomment one) (-u option)
USERIF_LIBS = $(ALL_ENV_LIBS) # that is, $(TKENV_LIBS) $(CMDENV_LIBS)
#USERIF_LIBS = $(CMDENV_LIBS)
#USERIF_LIBS = $(TKENV_LIBS)

# C++ include paths (with -I)
INCLUDE_PATH = \
    -I. \
    -Iadmission \
    -Ichannels \
    -Iforks \
    -Igenerators \
    -Ipackets \
    -Iprofilers \
    -Ischedulers \
    -Isimulation \
    -Isinks

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
    $O/Sink.o \
    $O/Source.o \
    $O/admission/AbstractAdmissionControl.o \
    $O/admission/PriorityControlAdmissionControl.o \
    $O/admission/RateBasedAdmissionControl.o \
    $O/admission/SizeAdmissionControl.o \
    $O/admission/SrcAdmissionControl.o \
    $O/forks/DummyModule.o \
    $O/forks/RandomFork.o \
    $O/generators/AbstractGenerator.o \
    $O/generators/ExponentialGenerator.o \
    $O/generators/MarkovModulatedPoissonProcessGenerator.o \
    $O/generators/OnOffGenerator.o \
    $O/generators/PoissonGenerator.o \
    $O/profilers/AbstractProfiler.o \
    $O/profilers/JitterControlProfiler.o \
    $O/profilers/LeakyBucketProfiler.o \
    $O/profilers/LoadSheddingProfiler.o \
    $O/profilers/TokenBucketProfiler.o \
    $O/schedulers/AbstractScheduler.o \
    $O/schedulers/FcfsScheduler.o \
    $O/schedulers/LcfsScheduler.o \
    $O/schedulers/PriorityQueueScheduler.o \
    $O/schedulers/RoundRobinScheduler.o \
    $O/schedulers/WeightedRoundRobinScheduler.o \
    $O/simulation/TimeLogScheduler.o \
    $O/sinks/SimpleSink.o \
    $O/packets/NetPacket_m.o

# Message files
MSGFILES = \
    packets/NetPacket.msg

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
	$(Q)-rm -f tirt tirt.exe libtirt.so libtirt.a libtirt.dll libtirt.dylib
	$(Q)-rm -f ./*_m.cc ./*_m.h
	$(Q)-rm -f admission/*_m.cc admission/*_m.h
	$(Q)-rm -f channels/*_m.cc channels/*_m.h
	$(Q)-rm -f forks/*_m.cc forks/*_m.h
	$(Q)-rm -f generators/*_m.cc generators/*_m.h
	$(Q)-rm -f packets/*_m.cc packets/*_m.h
	$(Q)-rm -f profilers/*_m.cc profilers/*_m.h
	$(Q)-rm -f schedulers/*_m.cc schedulers/*_m.h
	$(Q)-rm -f simulation/*_m.cc simulation/*_m.h
	$(Q)-rm -f sinks/*_m.cc sinks/*_m.h

cleanall: clean
	$(Q)-rm -rf $(PROJECT_OUTPUT_DIR)

depend:
	$(qecho) Creating dependencies...
	$(Q)$(MAKEDEPEND) $(INCLUDE_PATH) -f Makefile -P\$$O/ -- $(MSG_CC_FILES)  ./*.cc admission/*.cc channels/*.cc forks/*.cc generators/*.cc packets/*.cc profilers/*.cc schedulers/*.cc simulation/*.cc sinks/*.cc

# DO NOT DELETE THIS LINE -- make depend depends on it.
$O/Sink.o: Sink.cc \
	Sink.h
$O/Source.o: Source.cc \
	Source.h
$O/admission/AbstractAdmissionControl.o: admission/AbstractAdmissionControl.cc \
	admission/AbstractAdmissionControl.h \
	packets/NetPacket_m.h
$O/admission/PriorityControlAdmissionControl.o: admission/PriorityControlAdmissionControl.cc \
	admission/AbstractAdmissionControl.h \
	admission/PriorityControlAdmissionControl.h \
	packets/NetPacket_m.h
$O/admission/RateBasedAdmissionControl.o: admission/RateBasedAdmissionControl.cc \
	admission/AbstractAdmissionControl.h \
	admission/RateBasedAdmissionControl.h \
	packets/NetPacket_m.h
$O/admission/SizeAdmissionControl.o: admission/SizeAdmissionControl.cc \
	admission/AbstractAdmissionControl.h \
	admission/SizeAdmissionControl.h \
	packets/NetPacket_m.h
$O/admission/SrcAdmissionControl.o: admission/SrcAdmissionControl.cc \
	admission/AbstractAdmissionControl.h \
	admission/SrcAdmissionControl.h \
	packets/NetPacket_m.h
$O/forks/DummyModule.o: forks/DummyModule.cc \
	forks/DummyModule.h
$O/forks/RandomFork.o: forks/RandomFork.cc \
	forks/RandomFork.h
$O/generators/AbstractGenerator.o: generators/AbstractGenerator.cc \
	generators/AbstractGenerator.h \
	packets/NetPacket_m.h
$O/generators/ExponentialGenerator.o: generators/ExponentialGenerator.cc \
	generators/AbstractGenerator.h \
	generators/ExponentialGenerator.h \
	packets/NetPacket_m.h
$O/generators/MarkovModulatedPoissonProcessGenerator.o: generators/MarkovModulatedPoissonProcessGenerator.cc \
	generators/AbstractGenerator.h \
	generators/MarkovModulatedPoissonProcessGenerator.h \
	packets/NetPacket_m.h
$O/generators/OnOffGenerator.o: generators/OnOffGenerator.cc \
	generators/AbstractGenerator.h \
	generators/OnOffGenerator.h \
	packets/NetPacket_m.h
$O/generators/PoissonGenerator.o: generators/PoissonGenerator.cc \
	generators/AbstractGenerator.h \
	generators/PoissonGenerator.h \
	packets/NetPacket_m.h
$O/packets/NetPacket_m.o: packets/NetPacket_m.cc \
	packets/NetPacket_m.h
$O/profilers/AbstractProfiler.o: profilers/AbstractProfiler.cc \
	packets/NetPacket_m.h \
	profilers/AbstractProfiler.h
$O/profilers/JitterControlProfiler.o: profilers/JitterControlProfiler.cc \
	packets/NetPacket_m.h \
	profilers/AbstractProfiler.h \
	profilers/JitterControlProfiler.h
$O/profilers/LeakyBucketProfiler.o: profilers/LeakyBucketProfiler.cc \
	packets/NetPacket_m.h \
	profilers/AbstractProfiler.h \
	profilers/LeakyBucketProfiler.h
$O/profilers/LoadSheddingProfiler.o: profilers/LoadSheddingProfiler.cc \
	packets/NetPacket_m.h \
	profilers/AbstractProfiler.h \
	profilers/LoadSheddingProfiler.h
$O/profilers/TokenBucketProfiler.o: profilers/TokenBucketProfiler.cc \
	packets/NetPacket_m.h \
	profilers/AbstractProfiler.h \
	profilers/TokenBucketProfiler.h
$O/schedulers/AbstractScheduler.o: schedulers/AbstractScheduler.cc \
	packets/NetPacket_m.h \
	schedulers/AbstractScheduler.h
$O/schedulers/FcfsScheduler.o: schedulers/FcfsScheduler.cc \
	packets/NetPacket_m.h \
	schedulers/AbstractScheduler.h \
	schedulers/FcfsScheduler.h
$O/schedulers/LcfsScheduler.o: schedulers/LcfsScheduler.cc \
	packets/NetPacket_m.h \
	schedulers/AbstractScheduler.h \
	schedulers/LcfsScheduler.h
$O/schedulers/PriorityQueueScheduler.o: schedulers/PriorityQueueScheduler.cc \
	packets/NetPacket_m.h \
	schedulers/AbstractScheduler.h \
	schedulers/PriorityQueueScheduler.h
$O/schedulers/RoundRobinScheduler.o: schedulers/RoundRobinScheduler.cc \
	packets/NetPacket_m.h \
	schedulers/AbstractScheduler.h \
	schedulers/RoundRobinScheduler.h
$O/schedulers/WeightedRoundRobinScheduler.o: schedulers/WeightedRoundRobinScheduler.cc \
	packets/NetPacket_m.h \
	schedulers/AbstractScheduler.h \
	schedulers/WeightedRoundRobinScheduler.h
$O/simulation/TimeLogScheduler.o: simulation/TimeLogScheduler.cc \
	simulation/TimeLogScheduler.h
$O/sinks/SimpleSink.o: sinks/SimpleSink.cc \
	packets/NetPacket_m.h \
	sinks/SimpleSink.h

