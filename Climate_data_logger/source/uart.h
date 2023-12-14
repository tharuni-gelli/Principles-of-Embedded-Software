/*
 * uart.h
 *
 *  Created on: 13-Dec-2023
 *      Author: THARUNI GELLI
 */

#ifndef UART_H_
#define UART_H_

/**************************************************************************
 * File includes here
 **************************************************************************/
#include <stdint.h>
#include <MKL25Z4.H>
#include "cbfifo.h"

/*
 * Function header: __sys_write
 * ---------------------
 * Writes data to a given output handle.
 *
 * Parameters:
 *     handle - The output handle where data will be written.
 *     buf    - Pointer to the buffer containing the data to be written.
 *     size   - The size, in bytes, of the data to be written.
 *
 * Returns:
 *     int - The number of bytes successfully written, or an error code if negative.
 */
int __sys_write(int handle, char *buf, int size);


/*
 * Function header: __sys_readc
 * ---------------------
 * Reads a single character from the input source.
 *
 * Parameters:
 *     None
 *
 * Returns:
 *     int - The character read as an integer, or an error code if no character is available.
 */
int __sys_readc(void);

/*
 * Function header: init_UART0
 * ---------------------
 * Initializes UART0 for serial communication.
 *
 * Parameters:
 *     None
 *
 * Returns:
 *     void - This function does not return a value.
 */
void init_UART0(uint32_t baud_rate);

/*
 * Function header: UART0_IRQHandler
 * ---------------------
 * Interrupt Service Routine (ISR) for UART0.
 *
 * Parameters:
 *     None
 *
 * Returns:
 *     void - This function does not return a value.
 */
void UART0_IRQHandler(void);



#endif /* UART_H_ */
