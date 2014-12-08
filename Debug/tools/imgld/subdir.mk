################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
O_SRCS += \
../tools/imgld/imgld.o 

C_SRCS += \
../tools/imgld/imgld.c 

OBJS += \
./tools/imgld/imgld.o 

C_DEPS += \
./tools/imgld/imgld.d 


# Each subdirectory must supply rules for building sources it contributes
tools/imgld/%.o: ../tools/imgld/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: Cross GCC Compiler'
	gcc -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


