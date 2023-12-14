/*
 * process_command.h
 *
 *  Created on: 14-Dec-2023
 *      Author: THARUNI GELLI
 */

#ifndef PROCESS_COMMAND_H_
#define PROCESS_COMMAND_H_

#include <stdint.h>
#include <stdio.h>
#include <MKL25Z4.H>
#include <string.h>
#include <stdbool.h>
#include <ctype.h>
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
#include "rgb_led.h"
#include "sht21.h"
#include "uart.h"

/**
 * @brief Process a user command based on the provided input.
 *
 * This function takes a character array representing a user command as input
 * and processes it accordingly. The specific actions and behaviors triggered by
 * different command inputs are defined within the function implementation.
 *
 * @param input A null-terminated string containing the user command to be processed.
 */
void process_command(char *input);




#endif /* PROCESS_COMMAND_H_ */
