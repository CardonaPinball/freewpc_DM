################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
O_SRCS += \
../build/callset.o \
../build/claw.o \
../build/claw_test.o \
../build/clawmagnet.o \
../build/diverter.o \
../build/diverter_test.o \
../build/elevator.o \
../build/elevator_test.o \
../build/left_jet.o \
../build/left_sling.o \
../build/mach-containers.o \
../build/mach-deffs.o \
../build/mach-drives.o \
../build/mach-fonts.o \
../build/mach-lamplists.o \
../build/mach-scores.o \
../build/mach-strings.o \
../build/mach-switches.o \
../build/mach-switchmasks.o \
../build/mach-vars.o \
../build/page52.o \
../build/page53.o \
../build/page54.o \
../build/page55.o \
../build/page56.o \
../build/page57.o \
../build/page58.o \
../build/page59.o \
../build/page60.o \
../build/page61.o \
../build/right_jet.o \
../build/right_sling.o \
../build/sched_irq.o \
../build/shaker.o \
../build/top_sling.o 

C_SRCS += \
../build/callset.c \
../build/claw.c \
../build/claw_test.c \
../build/clawmagnet.c \
../build/diverter.c \
../build/diverter_test.c \
../build/elevator.c \
../build/elevator_test.c \
../build/left_jet.c \
../build/left_sling.c \
../build/mach-containers.c \
../build/mach-deffs.c \
../build/mach-drives.c \
../build/mach-fonts.c \
../build/mach-lamplists.c \
../build/mach-scores.c \
../build/mach-strings.c \
../build/mach-switches.c \
../build/mach-switchmasks.c \
../build/mach-vars.c \
../build/right_jet.c \
../build/right_sling.c \
../build/sched_irq.c \
../build/shaker.c \
../build/top_sling.c 

OBJS += \
./build/callset.o \
./build/claw.o \
./build/claw_test.o \
./build/clawmagnet.o \
./build/diverter.o \
./build/diverter_test.o \
./build/elevator.o \
./build/elevator_test.o \
./build/left_jet.o \
./build/left_sling.o \
./build/mach-containers.o \
./build/mach-deffs.o \
./build/mach-drives.o \
./build/mach-fonts.o \
./build/mach-lamplists.o \
./build/mach-scores.o \
./build/mach-strings.o \
./build/mach-switches.o \
./build/mach-switchmasks.o \
./build/mach-vars.o \
./build/right_jet.o \
./build/right_sling.o \
./build/sched_irq.o \
./build/shaker.o \
./build/top_sling.o 

C_DEPS += \
./build/callset.d \
./build/claw.d \
./build/claw_test.d \
./build/clawmagnet.d \
./build/diverter.d \
./build/diverter_test.d \
./build/elevator.d \
./build/elevator_test.d \
./build/left_jet.d \
./build/left_sling.d \
./build/mach-containers.d \
./build/mach-deffs.d \
./build/mach-drives.d \
./build/mach-fonts.d \
./build/mach-lamplists.d \
./build/mach-scores.d \
./build/mach-strings.d \
./build/mach-switches.d \
./build/mach-switchmasks.d \
./build/mach-vars.d \
./build/right_jet.d \
./build/right_sling.d \
./build/sched_irq.d \
./build/shaker.d \
./build/top_sling.d 


# Each subdirectory must supply rules for building sources it contributes
build/%.o: ../build/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: Cross GCC Compiler'
	gcc -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


