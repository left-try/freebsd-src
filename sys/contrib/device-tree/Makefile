DTC ?= dtc
CPP ?= cpp

# Disable noisy checks by default
ifeq ($(findstring 1,$(DTC_VERBOSE)),)
DTC_FLAGS += -Wno-unit_address_vs_reg \
        -Wno-unit_address_format \
        -Wno-avoid_unnecessary_addr_size \
        -Wno-alias_paths \
        -Wno-graph_child_address \
        -Wno-simple_bus_reg \
        -Wno-unique_unit_address \
        -Wno-pci_device_reg
endif

ifneq ($(findstring 2,$(DTC_VERBOSE)),)
DTC_FLAGS += -Wnode_name_chars_strict \
        -Wproperty_name_chars_strict
endif

MAKEFLAGS += -rR --no-print-directory

ALL_ARCHES := $(patsubst src/%,%,$(wildcard src/*))

PHONY += all
all: $(foreach i,$(ALL_ARCHES),all_$(i))

PHONY += clean
clean: $(foreach i,$(ALL_ARCHES),clean_$(i))

# Do not:
# o  use make's built-in rules and variables
#    (this increases performance and avoids hard-to-debug behaviour);
# o  print "Entering directory ...";
MAKEFLAGS += -rR --no-print-directory

# To put more focus on warnings, be less verbose as default
# Use 'make V=1' to see the full commands

ifeq ("$(origin V)", "command line")
  KBUILD_VERBOSE = $(V)
endif
ifndef KBUILD_VERBOSE
  KBUILD_VERBOSE = 0
endif

# Beautify output
# ---------------------------------------------------------------------------
#
# Normally, we echo the whole command before executing it. By making
# that echo $($(quiet)$(cmd)), we now have the possibility to set
# $(quiet) to choose other forms of output instead, e.g.
#
#         quiet_cmd_cc_o_c = Compiling $(RELDIR)/$@
#         cmd_cc_o_c       = $(CC) $(c_flags) -c -o $@ $<
#
# If $(quiet) is empty, the whole command will be printed.
# If it is set to "quiet_", only the short version will be printed. 
# If it is set to "silent_", nothing will be printed at all, since
# the variable $(silent_cmd_cc_o_c) doesn't exist.
#
# A simple variant is to prefix commands with $(Q) - that's useful
# for commands that shall be hidden in non-verbose mode.
#
#       $(Q)ln $@ :<
#
# If KBUILD_VERBOSE equals 0 then the above command will be hidden.
# If KBUILD_VERBOSE equals 1 then the above command is displayed.

ifeq ($(KBUILD_VERBOSE),1)
  quiet =
  Q =
else
  quiet=quiet_
  Q = @
endif

# If the user is running make -s (silent mode), suppress echoing of
# commands

ifneq ($(filter 4.%,$(MAKE_VERSION)),)	# make-4
ifneq ($(filter %s ,$(firstword x$(MAKEFLAGS))),)
  quiet=silent_
endif
else					# make-3.8x
ifneq ($(filter s% -s%,$(MAKEFLAGS)),)
  quiet=silent_
endif
endif

export quiet Q KBUILD_VERBOSE

all_%:
	$(Q)$(MAKE) ARCH=$* all_arch

clean_%:
	$(Q)$(MAKE) ARCH=$* clean_arch

ifeq ($(ARCH),)

ALL_DTS		:= $(shell find src/* -name \*.dts)
ALL_DTSO	:= $(shell find src/* -name \*.dtso)

ALL_DTB		:= $(patsubst %.dts,%.dtb,$(ALL_DTS))
ALL_DTBO	:= $(patsubst %.dtso,%.dtbo,$(ALL_DTSO))

$(ALL_DTB) $(ALL_DTBO): ARCH=$(word 2,$(subst /, ,$@))
$(ALL_DTB) $(ALL_DTBO): FORCE
	$(Q)$(MAKE) ARCH=$(ARCH) $@

else

ARCH_DTS	:= $(shell find src/$(ARCH) -name \*.dts)
ARCH_DTSO	:= $(shell find src/$(ARCH) -name \*.dtso)

ARCH_DTB	:= $(patsubst %.dts,%.dtb,$(ARCH_DTS))
ARCH_DTBO	:= $(patsubst %.dtso,%.dtbo,$(ARCH_DTSO))

src	:= src/$(ARCH)
obj	:= src/$(ARCH)

include scripts/Kbuild.include

cmd_files := $(wildcard $(foreach f,$(ARCH_DTB) $(ARCH_DTBO),$(dir $(f)).$(notdir $(f)).cmd))

ifneq ($(cmd_files),)
  include $(cmd_files)
endif

quiet_cmd_clean    = CLEAN   $(obj)
      cmd_clean    = rm -f $(__clean-files)

dtc-tmp = $(subst $(comma),_,$(dot-target).dts.tmp)

dtc_cpp_flags  = -Wp,-MD,$(depfile).pre.tmp -nostdinc		\
                 -Iinclude -I$(src) -Isrc -Itestcase-data	\
                 -undef -D__DTS__

quiet_cmd_dtc = DTC     $@
cmd_dtc = $(CPP) $(dtc_cpp_flags) -x assembler-with-cpp -o $(dtc-tmp) $< ; \
        $(DTC) -O dtb -o $@ -b 0 \
                -i $(src) $(DTC_FLAGS) \
                -d $(depfile).dtc.tmp $(dtc-tmp) ; \
        cat $(depfile).pre.tmp $(depfile).dtc.tmp > $(depfile)

$(obj)/%.dtb: $(src)/%.dts FORCE
	$(call if_changed_dep,dtc)

quiet_cmd_dtco = DTCO    $@
cmd_dtco = $(CPP) $(dtc_cpp_flags) -x assembler-with-cpp -o $(dtc-tmp) $< ; \
        $(DTC) -@ -O dtb -o $@ -b 0 \
                -i $(src) $(DTC_FLAGS) \
                -d $(depfile).dtc.tmp $(dtc-tmp) ; \
        cat $(depfile).pre.tmp $(depfile).dtc.tmp > $(depfile)

$(obj)/%.dtbo: $(src)/%.dtso FORCE
	$(call if_changed_dep,dtco)

PHONY += all_arch
all_arch: $(ARCH_DTB) $(ARCH_DTBO)
	@:

RCS_FIND_IGNORE := \( -name SCCS -o -name BitKeeper -o -name .svn -o -name CVS \
                   -o -name .pc -o -name .hg -o -name .git \) -prune -o

PHONY += clean_arch
clean_arch: __clean-files = $(ARCH_DTB) $(ARCH_DTBO)
clean_arch: FORCE
	$(call cmd,clean)
	@find . $(RCS_FIND_IGNORE) \
		\( -name '.*.cmd' \
		-o -name '.*.d' \
		-o -name '.*.tmp' \
		\) -type f -print | xargs rm -f

endif

help:
	@echo "Targets:"
	@echo "  all:                   Build all device tree binaries for all architectures"
	@echo "  clean:                 Clean all generated files"
	@echo ""
	@echo "  all_<ARCH>:            Build all device tree binaries for <ARCH>"
	@echo "  clean_<ARCH>:          Clean all generated files for <ARCH>"
	@echo ""
	@echo "  src/<ARCH>/<DTS>.dtb   Build a single device tree binary"
	@echo ""
	@echo "Architectures: $(ALL_ARCHES)"

PHONY += FORCE
FORCE:

.PHONY: $(PHONY)
