/*
 * Copyright 2016-2023 NXP
 * All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

/**
 * @file    Climate_data_logger.c
 * @brief   Application entry point.
 */
#include <stdio.h>
#include "board.h"
#include "peripherals.h"
#include "pin_mux.h"
#include "clock_config.h"
#include "MKL25Z4.h"
#include "fsl_debug_console.h"
/* TODO: insert other include files here. */
#include "system_clock.h"
#include "systick.h"
#include "adc.h"
#include "cbfifo.h"
#include "hex_dump.h"
#include "i2c.h"
#include "input_line.h"
#include "mq7.h"
#include "process_command.h"
#include "pwm.h"
#include "pwm.h"
#include "rgb_led.h"
#include "sht21.h"
#include "system_clock.h"
#include "systick.h"
#include "uart.h"

/* TODO: insert other definitions and declarations here. */
#define UART_BAUD_RATE 38400

/*
 * @brief   Application entry point.
 */
int main(void) {

    /* Init board hardware. */
    BOARD_InitBootPins();
    BOARD_InitBootClocks();
    BOARD_InitBootPeripherals();
#ifndef BOARD_INIT_DEBUG_CONSOLE_PERIPHERAL
    /* Init FSL debug console. */
    BOARD_InitDebugConsole();
#endif

    init_UART0(UART_BAUD_RATE);

    Init_TPM_LED();

    Init_Red_LED_PWM(PWM_PERIOD);

    Init_Green_LED_PWM(PWM_PERIOD);

    Init_Blue_LED_PWM(PWM_PERIOD);

    init_sysclock();

    initialize_I2C1();

    init_ADC();

    Init_SysTick();


    printf("\n\rWelcome PES Final Project :) \n\r");
    printf("Designed by Tharuni Gelli.\n\r");
    printf("? ");

    test_pwm();


    // Enter an infinite loop
    while(1)
    {
        process_command_input();
    }
    return 0 ;
}
