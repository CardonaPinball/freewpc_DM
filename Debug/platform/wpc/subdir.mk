################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
O_SRCS += \
../platform/wpc/bitmap.o \
../platform/wpc/dmd.o \
../platform/wpc/dot.o \
../platform/wpc/init-wpc.o \
../platform/wpc/interrupt.o \
../platform/wpc/main.o \
../platform/wpc/shadow.o \
../platform/wpc/start.o \
../platform/wpc/wpc-lamp.o \
../platform/wpc/wpc-sol.o \
../platform/wpc/wpc-switch.o 

C_SRCS += \
../platform/wpc/init-wpc.c \
../platform/wpc/interrupt.c \
../platform/wpc/main.c \
../platform/wpc/wpc-lamp.c \
../platform/wpc/wpc-sol.c \
../platform/wpc/wpc-switch.c 

OBJS += \
./platform/wpc/init-wpc.o \
./platform/wpc/interrupt.o \
./platform/wpc/main.o \
./platform/wpc/wpc-lamp.o \
./platform/wpc/wpc-sol.o \
./platform/wpc/wpc-switch.o 

C_DEPS += \
./platform/wpc/init-wpc.d \
./platform/wpc/interrupt.d \
./platform/wpc/main.d \
./platform/wpc/wpc-lamp.d \
./platform/wpc/wpc-sol.d \
./platform/wpc/wpc-switch.d 


# Each subdirectory must supply rules for building sources it contributes
platform/wpc/%.o: ../platform/wpc/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: Cross GCC Compiler'
	gcc -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


