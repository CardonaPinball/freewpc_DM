################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../tools/softscope/softscope.c 

OBJS += \
./tools/softscope/softscope.o 

C_DEPS += \
./tools/softscope/softscope.d 


# Each subdirectory must supply rules for building sources it contributes
tools/softscope/%.o: ../tools/softscope/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: Cross GCC Compiler'
	gcc -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


