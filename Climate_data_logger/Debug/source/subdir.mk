################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../source/Climate_data_logger.c \
../source/adc.c \
../source/cbfifo.c \
../source/hex_dump.c \
../source/i2c.c \
../source/input_line.c \
../source/mq7.c \
../source/mtb.c \
../source/process_command.c \
../source/pwm.c \
../source/rgb_led.c \
../source/semihost_hardfault.c \
../source/sht21.c \
../source/system_clock.c \
../source/systick.c \
../source/uart.c 

C_DEPS += \
./source/Climate_data_logger.d \
./source/adc.d \
./source/cbfifo.d \
./source/hex_dump.d \
./source/i2c.d \
./source/input_line.d \
./source/mq7.d \
./source/mtb.d \
./source/process_command.d \
./source/pwm.d \
./source/rgb_led.d \
./source/semihost_hardfault.d \
./source/sht21.d \
./source/system_clock.d \
./source/systick.d \
./source/uart.d 

OBJS += \
./source/Climate_data_logger.o \
./source/adc.o \
./source/cbfifo.o \
./source/hex_dump.o \
./source/i2c.o \
./source/input_line.o \
./source/mq7.o \
./source/mtb.o \
./source/process_command.o \
./source/pwm.o \
./source/rgb_led.o \
./source/semihost_hardfault.o \
./source/sht21.o \
./source/system_clock.o \
./source/systick.o \
./source/uart.o 


# Each subdirectory must supply rules for building sources it contributes
source/%.o: ../source/%.c source/subdir.mk
	@echo 'Building file: $<'
	@echo 'Invoking: MCU C Compiler'
	arm-none-eabi-gcc -D__REDLIB__ -DCPU_MKL25Z128VLK4 -DCPU_MKL25Z128VLK4_cm0plus -DFSL_RTOS_BM -DSDK_OS_BAREMETAL -DSDK_DEBUGCONSOLE=0 -DCR_INTEGER_PRINTF -DPRINTF_FLOAT_ENABLE=0 -D__MCUXPRESSO -D__USE_CMSIS -DDEBUG -I"C:\Users\THARUNI GELLI\Documents\MCUXpressoIDE_11.8.0_1165\workspace\Climate_data_logger\board" -I"C:\Users\THARUNI GELLI\Documents\MCUXpressoIDE_11.8.0_1165\workspace\Climate_data_logger\source" -I"C:\Users\THARUNI GELLI\Documents\MCUXpressoIDE_11.8.0_1165\workspace\Climate_data_logger" -I"C:\Users\THARUNI GELLI\Documents\MCUXpressoIDE_11.8.0_1165\workspace\Climate_data_logger\drivers" -I"C:\Users\THARUNI GELLI\Documents\MCUXpressoIDE_11.8.0_1165\workspace\Climate_data_logger\CMSIS" -I"C:\Users\THARUNI GELLI\Documents\MCUXpressoIDE_11.8.0_1165\workspace\Climate_data_logger\utilities" -I"C:\Users\THARUNI GELLI\Documents\MCUXpressoIDE_11.8.0_1165\workspace\Climate_data_logger\startup" -O0 -fno-common -g3 -Wall -c -fmessage-length=0 -fno-builtin -ffunction-sections -fdata-sections -fmerge-constants -fmacro-prefix-map="$(<D)/"= -mcpu=cortex-m0plus -mthumb -D__REDLIB__ -fstack-usage -specs=redlib.specs -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.o)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


clean: clean-source

clean-source:
	-$(RM) ./source/Climate_data_logger.d ./source/Climate_data_logger.o ./source/adc.d ./source/adc.o ./source/cbfifo.d ./source/cbfifo.o ./source/hex_dump.d ./source/hex_dump.o ./source/i2c.d ./source/i2c.o ./source/input_line.d ./source/input_line.o ./source/mq7.d ./source/mq7.o ./source/mtb.d ./source/mtb.o ./source/process_command.d ./source/process_command.o ./source/pwm.d ./source/pwm.o ./source/rgb_led.d ./source/rgb_led.o ./source/semihost_hardfault.d ./source/semihost_hardfault.o ./source/sht21.d ./source/sht21.o ./source/system_clock.d ./source/system_clock.o ./source/systick.d ./source/systick.o ./source/uart.d ./source/uart.o

.PHONY: clean-source

