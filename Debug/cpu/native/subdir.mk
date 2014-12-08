################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../cpu/native/bcd_string.c \
../cpu/native/bits.c \
../cpu/native/dot.c \
../cpu/native/gpio.c \
../cpu/native/input.c \
../cpu/native/log.c \
../cpu/native/main.c \
../cpu/native/realtime.c \
../cpu/native/section.c \
../cpu/native/task_pth.c \
../cpu/native/task_pthread.c 

OBJS += \
./cpu/native/bcd_string.o \
./cpu/native/bits.o \
./cpu/native/dot.o \
./cpu/native/gpio.o \
./cpu/native/input.o \
./cpu/native/log.o \
./cpu/native/main.o \
./cpu/native/realtime.o \
./cpu/native/section.o \
./cpu/native/task_pth.o \
./cpu/native/task_pthread.o 

C_DEPS += \
./cpu/native/bcd_string.d \
./cpu/native/bits.d \
./cpu/native/dot.d \
./cpu/native/gpio.d \
./cpu/native/input.d \
./cpu/native/log.d \
./cpu/native/main.d \
./cpu/native/realtime.d \
./cpu/native/section.d \
./cpu/native/task_pth.d \
./cpu/native/task_pthread.d 


# Each subdirectory must supply rules for building sources it contributes
cpu/native/%.o: ../cpu/native/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: Cross GCC Compiler'
	gcc -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


