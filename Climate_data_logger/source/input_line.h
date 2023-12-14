/*
 * input_line.h
 *
 *  Created on: 14-Dec-2023
 *      Author: THARUNI GELLI
 */

#ifndef INPUT_LINE_H_
#define INPUT_LINE_H_

/*********************
 * File includes here
 *********************/

#include <string.h>
#include <stdio.h>
#include "process_command.h"
#include "uart.h"
#include "cbfifo.h"

/**
 * @brief Process user input character by character until Enter is pressed.
 *
 * This function reads characters from a circular buffer and echoes them back to
 * the terminal. It terminates when the Enter key is pressed, handling Backspace
 * to delete characters. The input is processed as a command after Enter is pressed.
 */
void process_command_input();



#endif /* INPUT_LINE_H_ */
