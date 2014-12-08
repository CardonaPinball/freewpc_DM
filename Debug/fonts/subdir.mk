################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
O_SRCS += \
../fonts/bitmap.o \
../fonts/bitmap8.o \
../fonts/dmgraphs.o \
../fonts/fixed10.o \
../fonts/fixed6.o \
../fonts/halobold12.o \
../fonts/halobold14.o \
../fonts/lucida9.o \
../fonts/mono5.o \
../fonts/mono9.o \
../fonts/symbol.o \
../fonts/term6.o \
../fonts/tinynum.o \
../fonts/var5.o 

C_SRCS += \
../fonts/bitmap.c \
../fonts/bitmap8.c \
../fonts/mono5.c \
../fonts/mono9.c \
../fonts/num5x7.c \
../fonts/symbol.c \
../fonts/tinynum.c \
../fonts/var5.c 

OBJS += \
./fonts/bitmap.o \
./fonts/bitmap8.o \
./fonts/mono5.o \
./fonts/mono9.o \
./fonts/num5x7.o \
./fonts/symbol.o \
./fonts/tinynum.o \
./fonts/var5.o 

C_DEPS += \
./fonts/bitmap.d \
./fonts/bitmap8.d \
./fonts/mono5.d \
./fonts/mono9.d \
./fonts/num5x7.d \
./fonts/symbol.d \
./fonts/tinynum.d \
./fonts/var5.d 


# Each subdirectory must supply rules for building sources it contributes
fonts/%.o: ../fonts/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: Cross GCC Compiler'
	gcc -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


