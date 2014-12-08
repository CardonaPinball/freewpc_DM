################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
O_SRCS += \
../tools/srec2bin/srec2bin.o 

C_SRCS += \
../tools/srec2bin/srec2bin.c 

OBJS += \
./tools/srec2bin/srec2bin.o 

C_DEPS += \
./tools/srec2bin/srec2bin.d 


# Each subdirectory must supply rules for building sources it contributes
tools/srec2bin/%.o: ../tools/srec2bin/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: Cross GCC Compiler'
	gcc -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


