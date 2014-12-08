################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
O_SRCS += \
../kernel/ac.o \
../kernel/adj.o \
../kernel/audit.o \
../kernel/csum.o \
../kernel/deff.o \
../kernel/dmd.o \
../kernel/error.o \
../kernel/file.o \
../kernel/flip.o \
../kernel/font.o \
../kernel/frame.o \
../kernel/freetimer.o \
../kernel/game.o \
../kernel/idle.o \
../kernel/init.o \
../kernel/ladder.o \
../kernel/lamp.o \
../kernel/lamplist.o \
../kernel/lampset.o \
../kernel/lang.o \
../kernel/leff.o \
../kernel/log.o \
../kernel/mbmode.o \
../kernel/message.o \
../kernel/misc.o \
../kernel/player.o \
../kernel/printf.o \
../kernel/puts.o \
../kernel/random.o \
../kernel/score.o \
../kernel/sol.o \
../kernel/sound.o \
../kernel/switches.o \
../kernel/sysinfo.o \
../kernel/task.o \
../kernel/timedmode.o \
../kernel/timer.o \
../kernel/triac.o 

C_SRCS += \
../kernel/ac.c \
../kernel/adj.c \
../kernel/animation.c \
../kernel/audit.c \
../kernel/csum.c \
../kernel/deff.c \
../kernel/dmd.c \
../kernel/error.c \
../kernel/file.c \
../kernel/flip.c \
../kernel/font.c \
../kernel/frame.c \
../kernel/freetimer.c \
../kernel/game.c \
../kernel/idle.c \
../kernel/init.c \
../kernel/ladder.c \
../kernel/lamp.c \
../kernel/lamplist.c \
../kernel/lampset.c \
../kernel/lang.c \
../kernel/leff.c \
../kernel/list.c \
../kernel/log.c \
../kernel/mbmode.c \
../kernel/message.c \
../kernel/misc.c \
../kernel/player.c \
../kernel/printf.c \
../kernel/puts.c \
../kernel/random.c \
../kernel/score.c \
../kernel/segment.c \
../kernel/sol.c \
../kernel/sound.c \
../kernel/switches.c \
../kernel/sysinfo.c \
../kernel/task.c \
../kernel/timedmode.c \
../kernel/timer.c \
../kernel/triac.c 

OBJS += \
./kernel/ac.o \
./kernel/adj.o \
./kernel/animation.o \
./kernel/audit.o \
./kernel/csum.o \
./kernel/deff.o \
./kernel/dmd.o \
./kernel/error.o \
./kernel/file.o \
./kernel/flip.o \
./kernel/font.o \
./kernel/frame.o \
./kernel/freetimer.o \
./kernel/game.o \
./kernel/idle.o \
./kernel/init.o \
./kernel/ladder.o \
./kernel/lamp.o \
./kernel/lamplist.o \
./kernel/lampset.o \
./kernel/lang.o \
./kernel/leff.o \
./kernel/list.o \
./kernel/log.o \
./kernel/mbmode.o \
./kernel/message.o \
./kernel/misc.o \
./kernel/player.o \
./kernel/printf.o \
./kernel/puts.o \
./kernel/random.o \
./kernel/score.o \
./kernel/segment.o \
./kernel/sol.o \
./kernel/sound.o \
./kernel/switches.o \
./kernel/sysinfo.o \
./kernel/task.o \
./kernel/timedmode.o \
./kernel/timer.o \
./kernel/triac.o 

C_DEPS += \
./kernel/ac.d \
./kernel/adj.d \
./kernel/animation.d \
./kernel/audit.d \
./kernel/csum.d \
./kernel/deff.d \
./kernel/dmd.d \
./kernel/error.d \
./kernel/file.d \
./kernel/flip.d \
./kernel/font.d \
./kernel/frame.d \
./kernel/freetimer.d \
./kernel/game.d \
./kernel/idle.d \
./kernel/init.d \
./kernel/ladder.d \
./kernel/lamp.d \
./kernel/lamplist.d \
./kernel/lampset.d \
./kernel/lang.d \
./kernel/leff.d \
./kernel/list.d \
./kernel/log.d \
./kernel/mbmode.d \
./kernel/message.d \
./kernel/misc.d \
./kernel/player.d \
./kernel/printf.d \
./kernel/puts.d \
./kernel/random.d \
./kernel/score.d \
./kernel/segment.d \
./kernel/sol.d \
./kernel/sound.d \
./kernel/switches.d \
./kernel/sysinfo.d \
./kernel/task.d \
./kernel/timedmode.d \
./kernel/timer.d \
./kernel/triac.d 


# Each subdirectory must supply rules for building sources it contributes
kernel/%.o: ../kernel/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: Cross GCC Compiler'
	gcc -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


