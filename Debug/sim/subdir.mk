################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../sim/asciidmd.c \
../sim/coil.c \
../sim/conf.c \
../sim/hwtimer.c \
../sim/io.c \
../sim/io_min.c \
../sim/io_p2k.c \
../sim/io_wpc.c \
../sim/keyboard.c \
../sim/main.c \
../sim/node.c \
../sim/script.c \
../sim/segment.c \
../sim/signal.c \
../sim/sound.c \
../sim/switch.c \
../sim/timing.c \
../sim/tz_sim.c \
../sim/ui_console.c \
../sim/ui_curses.c \
../sim/ui_gtk.c \
../sim/ui_remote.c \
../sim/ui_sdl.c \
../sim/watchdog.c \
../sim/wpc-pic.c \
../sim/zerocross.c 

OBJS += \
./sim/asciidmd.o \
./sim/coil.o \
./sim/conf.o \
./sim/hwtimer.o \
./sim/io.o \
./sim/io_min.o \
./sim/io_p2k.o \
./sim/io_wpc.o \
./sim/keyboard.o \
./sim/main.o \
./sim/node.o \
./sim/script.o \
./sim/segment.o \
./sim/signal.o \
./sim/sound.o \
./sim/switch.o \
./sim/timing.o \
./sim/tz_sim.o \
./sim/ui_console.o \
./sim/ui_curses.o \
./sim/ui_gtk.o \
./sim/ui_remote.o \
./sim/ui_sdl.o \
./sim/watchdog.o \
./sim/wpc-pic.o \
./sim/zerocross.o 

C_DEPS += \
./sim/asciidmd.d \
./sim/coil.d \
./sim/conf.d \
./sim/hwtimer.d \
./sim/io.d \
./sim/io_min.d \
./sim/io_p2k.d \
./sim/io_wpc.d \
./sim/keyboard.d \
./sim/main.d \
./sim/node.d \
./sim/script.d \
./sim/segment.d \
./sim/signal.d \
./sim/sound.d \
./sim/switch.d \
./sim/timing.d \
./sim/tz_sim.d \
./sim/ui_console.d \
./sim/ui_curses.d \
./sim/ui_gtk.d \
./sim/ui_remote.d \
./sim/ui_sdl.d \
./sim/watchdog.d \
./sim/wpc-pic.d \
./sim/zerocross.d 


# Each subdirectory must supply rules for building sources it contributes
sim/%.o: ../sim/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: Cross GCC Compiler'
	gcc -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


