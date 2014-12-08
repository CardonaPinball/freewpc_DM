################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../tools/fontedit/fontlib.c 

OBJS += \
./tools/fontedit/fontlib.o 

C_DEPS += \
./tools/fontedit/fontlib.d 


# Each subdirectory must supply rules for building sources it contributes
tools/fontedit/%.o: ../tools/fontedit/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: Cross GCC Compiler'
	gcc -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


