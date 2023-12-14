/*
 * cbfifo.h
 *
 *  Created on: 13-Dec-2023
 *      Author: THARUNI GELLI
 */

#ifndef CBFIFO_H_
#define CBFIFO_H_

/***********************************************************
 * File includes here
 ***********************************************************/
#include <stdlib.h>  // for size_t
#include <stdbool.h>
#include <string.h>
#include <stdint.h>
#include <stdio.h>
#include <MKL25Z4.H>

/************************************************************
 * Declaring enum for two types of cbfifo
 *************************************************************/

typedef enum fifo_buffers {
	trans = 0,
	rec= 1
}cb_fifo_type;

/*
 * Function header: cbfifo_init
 * ---------------------
 * Initializes a circular buffer FIFO by resetting its parameters.
 *
 * Parameters:
 *     queue - Pointer to the FIFO structure to be initialized.
 *
 * Returns:
 *     void - This function does not return a value.
 */
void cbfifo_init(uint32_t command_type);

/*
 * Function header: cbfifo_enqueue
 * ---------------------
 * Enqueues data into a circular buffer FIFO, updating the buffer parameters.
 *
 * Parameters:
 *     queue  - Pointer to the FIFO structure.
 *     nbyte  - Number of bytes to enqueue into the FIFO.
 *
 * Returns:
 *     size_t - The actual number of bytes successfully enqueued into the FIFO.
 */
size_t cbfifo_enqueue(void *buf, size_t nbyte, uint32_t command_type);

/*
 * Function header: cbfifo_dequeue
 * ---------------------
 * Dequeues data from a circular buffer FIFO, updating the buffer parameters.
 *
 * Parameters:
 *     queue - Pointer to the FIFO structure.
 *
 * Returns:
 *     size_t - The actual number of bytes dequeued from the FIFO.
 */
size_t cbfifo_dequeue(void *buf, size_t nbyte, uint32_t command_type);

/*
 * Function header: cbfifo_length
 * ---------------------
 * Returns the current length of data in a circular buffer FIFO.
 *
 * Parameters:
 *     queue - Pointer to the FIFO structure.
 *
 * Returns:
 *     size_t - The current length of data in the FIFO.
 */
size_t cbfifo_length(uint32_t command_type);

/*
 * Function header: cbfifo_empty
 * ---------------------
 * Checks if a circular buffer FIFO is empty.
 *
 * Parameters:
 *     queue - Pointer to the FIFO structure.
 *
 * Returns:
 *     int - 1 if the FIFO is empty, 0 otherwise.
 */
int cbfifo_empty(uint32_t command_type);


/*
 * Function header: cbfifo_full
 * ---------------------
 * Checks if a circular buffer FIFO is full.
 *
 * Parameters:
 *     queue - Pointer to the FIFO structure.
 *
 * Returns:
 *     int - 1 if the FIFO is full, 0 otherwise.
 */
int cbfifo_full(uint32_t command_type);

#endif /* CBFIFO_H_ */
