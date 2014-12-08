################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../platform/wpcsound/bell.c \
../platform/wpcsound/cvsd.c \
../platform/wpcsound/dac.c \
../platform/wpcsound/fm.c \
../platform/wpcsound/host.c \
../platform/wpcsound/interrupt.c \
../platform/wpcsound/main.c \
../platform/wpcsound/volume.c 

OBJS += \
./platform/wpcsound/bell.o \
./platform/wpcsound/cvsd.o \
./platform/wpcsound/dac.o \
./platform/wpcsound/fm.o \
./platform/wpcsound/host.o \
./platform/wpcsound/interrupt.o \
./platform/wpcsound/main.o \
./platform/wpcsound/volume.o 

C_DEPS += \
./platform/wpcsound/bell.d \
./platform/wpcsound/cvsd.d \
./platform/wpcsound/dac.d \
./platform/wpcsound/fm.d \
./platform/wpcsound/host.d \
./platform/wpcsound/interrupt.d \
./platform/wpcsound/main.d \
./platform/wpcsound/volume.d 


# Each subdirectory must supply rules for building sources it contributes
platform/wpcsound/%.o: ../platform/wpcsound/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: Cross GCC Compiler'
	gcc -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


