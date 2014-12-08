################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
O_SRCS += \
../tools/sched/sched.o 

C_SRCS += \
../tools/sched/sched.c 

OBJS += \
./tools/sched/sched.o 

C_DEPS += \
./tools/sched/sched.d 


# Each subdirectory must supply rules for building sources it contributes
tools/sched/%.o: ../tools/sched/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: Cross GCC Compiler'
	gcc -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


