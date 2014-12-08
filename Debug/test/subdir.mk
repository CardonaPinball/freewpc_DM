################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
O_SRCS += \
../test/adjust.o \
../test/burnin.o \
../test/dmdtest.o \
../test/format.o \
../test/histogram.o \
../test/preset.o \
../test/pricing.o \
../test/stress.o \
../test/swtest.o \
../test/timestamp.o \
../test/window.o \
../test/wire.o 

C_SRCS += \
../test/adjust.c \
../test/burnin.c \
../test/dmdtest.c \
../test/format.c \
../test/histogram.c \
../test/preset.c \
../test/pricing.c \
../test/stress.c \
../test/swtest.c \
../test/timestamp.c \
../test/window.c \
../test/wire.c 

OBJS += \
./test/adjust.o \
./test/burnin.o \
./test/dmdtest.o \
./test/format.o \
./test/histogram.o \
./test/preset.o \
./test/pricing.o \
./test/stress.o \
./test/swtest.o \
./test/timestamp.o \
./test/window.o \
./test/wire.o 

C_DEPS += \
./test/adjust.d \
./test/burnin.d \
./test/dmdtest.d \
./test/format.d \
./test/histogram.d \
./test/preset.d \
./test/pricing.d \
./test/stress.d \
./test/swtest.d \
./test/timestamp.d \
./test/window.d \
./test/wire.d 


# Each subdirectory must supply rules for building sources it contributes
test/%.o: ../test/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: Cross GCC Compiler'
	gcc -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


