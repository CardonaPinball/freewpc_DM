################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
O_SRCS += \
../tools/imglib/imglib.o 

C_SRCS += \
../tools/imglib/dmdsim.c \
../tools/imglib/font.c \
../tools/imglib/genmask.c \
../tools/imglib/imglib.c \
../tools/imglib/test_compression.c \
../tools/imglib/testpgm.c 

OBJS += \
./tools/imglib/dmdsim.o \
./tools/imglib/font.o \
./tools/imglib/genmask.o \
./tools/imglib/imglib.o \
./tools/imglib/test_compression.o \
./tools/imglib/testpgm.o 

C_DEPS += \
./tools/imglib/dmdsim.d \
./tools/imglib/font.d \
./tools/imglib/genmask.d \
./tools/imglib/imglib.d \
./tools/imglib/test_compression.d \
./tools/imglib/testpgm.d 


# Each subdirectory must supply rules for building sources it contributes
tools/imglib/%.o: ../tools/imglib/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: Cross GCC Compiler'
	gcc -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


