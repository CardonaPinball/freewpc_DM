################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../tools/wpclib/client.c \
../tools/wpclib/server.c \
../tools/wpclib/wpclib.c 

OBJS += \
./tools/wpclib/client.o \
./tools/wpclib/server.o \
./tools/wpclib/wpclib.o 

C_DEPS += \
./tools/wpclib/client.d \
./tools/wpclib/server.d \
./tools/wpclib/wpclib.d 


# Each subdirectory must supply rules for building sources it contributes
tools/wpclib/%.o: ../tools/wpclib/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: Cross GCC Compiler'
	gcc -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


