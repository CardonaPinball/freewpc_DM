################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../tools/lamptools/lamporder.c \
../tools/lamptools/lampset.c 

OBJS += \
./tools/lamptools/lamporder.o \
./tools/lamptools/lampset.o 

C_DEPS += \
./tools/lamptools/lamporder.d \
./tools/lamptools/lampset.d 


# Each subdirectory must supply rules for building sources it contributes
tools/lamptools/%.o: ../tools/lamptools/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: Cross GCC Compiler'
	gcc -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


