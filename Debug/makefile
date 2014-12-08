################################################################################
# Automatically-generated file. Do not edit!
################################################################################

-include ../makefile.init

RM := rm -rf

# All of the sources participating in the build are defined here
-include sources.mk
-include tools/wpclib/subdir.mk
-include tools/wpcdebug/subdir.mk
-include tools/wavegen/subdir.mk
-include tools/srec2bin/subdir.mk
-include tools/softscope/subdir.mk
-include tools/scope/subdir.mk
-include tools/sched/subdir.mk
-include tools/lamptools/subdir.mk
-include tools/imglib/subdir.mk
-include tools/imgld/subdir.mk
-include tools/fontedit/subdir.mk
-include tools/csum/subdir.mk
-include tools/acpulse/subdir.mk
-include test/subdir.mk
-include sim/subdir.mk
-include platform/wpcsound/subdir.mk
-include platform/wpc/subdir.mk
-include machine/ngg/subdir.mk
-include machine/dm/subdir.mk
-include kernel/subdir.mk
-include fonts/free/subdir.mk
-include fonts/subdir.mk
-include effect/subdir.mk
-include cpu/native/subdir.mk
-include cpu/m6809/subdir.mk
-include common/subdir.mk
-include build/subdir.mk
-include subdir.mk
-include objects.mk

ifneq ($(MAKECMDGOALS),clean)
ifneq ($(strip $(C++_DEPS)),)
-include $(C++_DEPS)
endif
ifneq ($(strip $(C_DEPS)),)
-include $(C_DEPS)
endif
ifneq ($(strip $(CC_DEPS)),)
-include $(CC_DEPS)
endif
ifneq ($(strip $(CPP_DEPS)),)
-include $(CPP_DEPS)
endif
ifneq ($(strip $(CXX_DEPS)),)
-include $(CXX_DEPS)
endif
ifneq ($(strip $(C_UPPER_DEPS)),)
-include $(C_UPPER_DEPS)
endif
endif

-include ../makefile.defs

# Add inputs and outputs from these tool invocations to the build variables 

# All Target
all: freewpc

# Tool invocations
freewpc: $(OBJS) $(USER_OBJS)
	@echo 'Building target: $@'
	@echo 'Invoking: Cross G++ Linker'
	g++  -o "freewpc" $(OBJS) $(USER_OBJS) $(LIBS)
	@echo 'Finished building target: $@'
	@echo ' '

# Other Targets
clean:
	-$(RM) $(C++_DEPS)$(OBJS)$(C_DEPS)$(CC_DEPS)$(CPP_DEPS)$(EXECUTABLES)$(CXX_DEPS)$(C_UPPER_DEPS) freewpc
	-@echo ' '

.PHONY: all clean dependents
.SECONDARY:

-include ../makefile.targets
