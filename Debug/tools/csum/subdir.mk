################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
O_SRCS += \
../tools/csum/csum.o 

C_SRCS += \
../tools/csum/csum.c 

OBJS += \
./tools/csum/csum.o 

C_DEPS += \
./tools/csum/csum.d 


# Each subdirectory must supply rules for building sources it contributes
tools/csum/%.o: ../tools/csum/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: Cross GCC Compiler'
	gcc -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


