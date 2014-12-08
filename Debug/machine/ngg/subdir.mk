################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../machine/ngg/acmag.c \
../machine/ngg/bonus.c \
../machine/ngg/combos.c \
../machine/ngg/dm_ball_search.c \
../machine/ngg/dm_modes_locals.c \
../machine/ngg/eject.c \
../machine/ngg/fortress.c \
../machine/ngg/jackpots.c \
../machine/ngg/jets.c \
../machine/ngg/lock_freeze_mbstart.c \
../machine/ngg/orbits.c \
../machine/ngg/ramps.c \
../machine/ngg/simple_switches.c \
../machine/ngg/skillshot.c \
../machine/ngg/startup_shutdown.c 

OBJS += \
./machine/ngg/acmag.o \
./machine/ngg/bonus.o \
./machine/ngg/combos.o \
./machine/ngg/dm_ball_search.o \
./machine/ngg/dm_modes_locals.o \
./machine/ngg/eject.o \
./machine/ngg/fortress.o \
./machine/ngg/jackpots.o \
./machine/ngg/jets.o \
./machine/ngg/lock_freeze_mbstart.o \
./machine/ngg/orbits.o \
./machine/ngg/ramps.o \
./machine/ngg/simple_switches.o \
./machine/ngg/skillshot.o \
./machine/ngg/startup_shutdown.o 

C_DEPS += \
./machine/ngg/acmag.d \
./machine/ngg/bonus.d \
./machine/ngg/combos.d \
./machine/ngg/dm_ball_search.d \
./machine/ngg/dm_modes_locals.d \
./machine/ngg/eject.d \
./machine/ngg/fortress.d \
./machine/ngg/jackpots.d \
./machine/ngg/jets.d \
./machine/ngg/lock_freeze_mbstart.d \
./machine/ngg/orbits.d \
./machine/ngg/ramps.d \
./machine/ngg/simple_switches.d \
./machine/ngg/skillshot.d \
./machine/ngg/startup_shutdown.d 


# Each subdirectory must supply rules for building sources it contributes
machine/ngg/%.o: ../machine/ngg/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: Cross GCC Compiler'
	gcc -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


