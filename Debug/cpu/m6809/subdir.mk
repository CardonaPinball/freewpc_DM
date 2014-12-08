################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
O_SRCS += \
../cpu/m6809/bcd_string.o \
../cpu/m6809/div10.o \
../cpu/m6809/div32.o \
../cpu/m6809/farcall.o \
../cpu/m6809/irqload.o \
../cpu/m6809/section.o \
../cpu/m6809/string.o \
../cpu/m6809/task.o \
../cpu/m6809/task_6809.o \
../cpu/m6809/vector.o 

C_SRCS += \
../cpu/m6809/div10.c \
../cpu/m6809/malloc.c \
../cpu/m6809/task.c \
../cpu/m6809/vector.c 

OBJS += \
./cpu/m6809/div10.o \
./cpu/m6809/malloc.o \
./cpu/m6809/task.o \
./cpu/m6809/vector.o 

C_DEPS += \
./cpu/m6809/div10.d \
./cpu/m6809/malloc.d \
./cpu/m6809/task.d \
./cpu/m6809/vector.d 


# Each subdirectory must supply rules for building sources it contributes
cpu/m6809/%.o: ../cpu/m6809/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: Cross GCC Compiler'
	gcc -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


