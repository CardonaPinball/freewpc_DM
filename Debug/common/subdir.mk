################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
O_SRCS += \
../common/abort.o \
../common/amode.o \
../common/auto_replay.o \
../common/ballsave.o \
../common/coin.o \
../common/db.o \
../common/device.o \
../common/diag.o \
../common/dmd_overlay.o \
../common/dmd_rough.o \
../common/dmd_shadow.o \
../common/dmdtrans.o \
../common/eb.o \
../common/effect.o \
../common/effect_update.o \
../common/event-audit.o \
../common/flash.o \
../common/flipcode.o \
../common/highscore.o \
../common/initials.o \
../common/knocker.o \
../common/lamptimer.o \
../common/locale.o \
../common/optocheck.o \
../common/plunger.o \
../common/replay.o \
../common/reset.o \
../common/rtc.o \
../common/score_deff.o \
../common/score_deff_dmd.o \
../common/search.o \
../common/serve.o \
../common/service.o \
../common/shootalert.o \
../common/sound_effect.o \
../common/special.o \
../common/start_button.o \
../common/status.o \
../common/swinfo.o \
../common/tilt.o \
../common/tournament.o \
../common/trough.o 

C_SRCS += \
../common/abort.c \
../common/amode.c \
../common/auto_replay.c \
../common/ballsave.c \
../common/coin.c \
../common/db.c \
../common/device.c \
../common/diag.c \
../common/dmd_overlay.c \
../common/dmd_rough.c \
../common/dmd_shadow.c \
../common/dmdtrans.c \
../common/eb.c \
../common/ebflex.c \
../common/effect.c \
../common/effect_update.c \
../common/event-audit.c \
../common/flash.c \
../common/flex.c \
../common/flipcode.c \
../common/highscore.c \
../common/initials.c \
../common/knocker.c \
../common/lamptimer.c \
../common/locale.c \
../common/optocheck.c \
../common/pause.c \
../common/pic.c \
../common/pin.c \
../common/plunger.c \
../common/replay.c \
../common/reset.c \
../common/rtc.c \
../common/score_deff.c \
../common/score_deff_dmd.c \
../common/score_deff_seg.c \
../common/score_rank.c \
../common/search.c \
../common/segtrans.c \
../common/serve.c \
../common/service.c \
../common/shootalert.c \
../common/sound_effect.c \
../common/special.c \
../common/start_button.c \
../common/status.c \
../common/swinfo.c \
../common/tilt.c \
../common/tournament.c \
../common/trough.c 

OBJS += \
./common/abort.o \
./common/amode.o \
./common/auto_replay.o \
./common/ballsave.o \
./common/coin.o \
./common/db.o \
./common/device.o \
./common/diag.o \
./common/dmd_overlay.o \
./common/dmd_rough.o \
./common/dmd_shadow.o \
./common/dmdtrans.o \
./common/eb.o \
./common/ebflex.o \
./common/effect.o \
./common/effect_update.o \
./common/event-audit.o \
./common/flash.o \
./common/flex.o \
./common/flipcode.o \
./common/highscore.o \
./common/initials.o \
./common/knocker.o \
./common/lamptimer.o \
./common/locale.o \
./common/optocheck.o \
./common/pause.o \
./common/pic.o \
./common/pin.o \
./common/plunger.o \
./common/replay.o \
./common/reset.o \
./common/rtc.o \
./common/score_deff.o \
./common/score_deff_dmd.o \
./common/score_deff_seg.o \
./common/score_rank.o \
./common/search.o \
./common/segtrans.o \
./common/serve.o \
./common/service.o \
./common/shootalert.o \
./common/sound_effect.o \
./common/special.o \
./common/start_button.o \
./common/status.o \
./common/swinfo.o \
./common/tilt.o \
./common/tournament.o \
./common/trough.o 

C_DEPS += \
./common/abort.d \
./common/amode.d \
./common/auto_replay.d \
./common/ballsave.d \
./common/coin.d \
./common/db.d \
./common/device.d \
./common/diag.d \
./common/dmd_overlay.d \
./common/dmd_rough.d \
./common/dmd_shadow.d \
./common/dmdtrans.d \
./common/eb.d \
./common/ebflex.d \
./common/effect.d \
./common/effect_update.d \
./common/event-audit.d \
./common/flash.d \
./common/flex.d \
./common/flipcode.d \
./common/highscore.d \
./common/initials.d \
./common/knocker.d \
./common/lamptimer.d \
./common/locale.d \
./common/optocheck.d \
./common/pause.d \
./common/pic.d \
./common/pin.d \
./common/plunger.d \
./common/replay.d \
./common/reset.d \
./common/rtc.d \
./common/score_deff.d \
./common/score_deff_dmd.d \
./common/score_deff_seg.d \
./common/score_rank.d \
./common/search.d \
./common/segtrans.d \
./common/serve.d \
./common/service.d \
./common/shootalert.d \
./common/sound_effect.d \
./common/special.d \
./common/start_button.d \
./common/status.d \
./common/swinfo.d \
./common/tilt.d \
./common/tournament.d \
./common/trough.d 


# Each subdirectory must supply rules for building sources it contributes
common/%.o: ../common/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: Cross GCC Compiler'
	gcc -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


