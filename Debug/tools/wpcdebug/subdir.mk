################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
O_SRCS += \
../tools/wpcdebug/input.o \
../tools/wpcdebug/wpcdebug.o 

C_SRCS += \
../tools/wpcdebug/input.c \
../tools/wpcdebug/wpcdebug.c 

OBJS += \
./tools/wpcdebug/input.o \
./tools/wpcdebug/wpcdebug.o 

C_DEPS += \
./tools/wpcdebug/input.d \
./tools/wpcdebug/wpcdebug.d 


# Each subdirectory must supply rules for building sources it contributes
tools/wpcdebug/%.o: ../tools/wpcdebug/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: Cross GCC Compiler'
	gcc -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


