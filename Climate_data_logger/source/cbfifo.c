/*
 * cbfifo.c
 *
 *  Created on: 13-Dec-2023
 *      Author: THARUNI GELLI
 */

#include "cbfifo.h"

#define FIFO_MAX_SIZE (256) // max size of buffer with static allocation

// Define a structure for a First In, First Out (FIFO) buffer.
typedef struct
{
    // Array to hold the data in the FIFO.
    uint8_t data[FIFO_MAX_SIZE];

    // Length of the current data in the FIFO.
    unsigned int length;

    // Index of the head of the FIFO (where data is read from).
    unsigned int head;

    // Index of the tail of the FIFO (where data is written to).
    unsigned int tail;

} fifo_t;

/******************************************************
 * Two types of fifo. Enum defined for this in .h file
 *******************************************************/
fifo_t fifo_type[2];

// Initialize circular buffer FIFO (First In, First Out) queue
void cbfifo_init(uint32_t command_type)
{

	// Initialize head and tail indices to 0
	fifo_type[command_type].head = 0;
	fifo_type[command_type].tail = 0;

	// Initialize the length of the queue to 0
	fifo_type[command_type].length = 0;
}

// Enqueue a byte into the circular buffer FIFO queue
size_t cbfifo_enqueue(void *buf, size_t nbyte, uint32_t command_type)
{
	uint32_t masking_state;
	size_t length_e =0;

	if(buf == NULL)
	{
		return -1;
	}

	else if(nbyte == 0)
	{
		return 0;
	}

	//Checking whether buffer length is more than or equal to maximum size
	else if (fifo_type[command_type].length >= FIFO_MAX_SIZE)
	{
	    return 0;                                          // Return Value
	}

	// If nbyte is more than difference of maximum size and length of buffer
	else if (nbyte > (FIFO_MAX_SIZE - fifo_type[command_type].length))
	{
	    nbyte = FIFO_MAX_SIZE - fifo_type[command_type].length; 	// Assigning value of nbyte
	}
	{
		// Save and disable the interrupt state
		masking_state = __get_PRIMASK();
		__disable_irq();

		for (int i = 0; i < nbyte; i++)
		{
			 //filling data into the buffer
			 fifo_type[command_type].data[fifo_type[command_type].tail] = *(uint8_t*) (buf + i);
			 length_e++;                  					//Incrementing length of bytes enqueued
			 fifo_type[command_type].length++; 	//Incrementing the length of buffer
			 fifo_type[command_type].tail++; 			//Incrementing the write pointer
			 if (fifo_type[command_type].tail == FIFO_MAX_SIZE)//If write pointer reaches maximum size
			 {
			       fifo_type[command_type].tail = 0; 		//Write pointer points to beginning i.e. 0
			 }
		}

		// restore the interrupt state
		__set_PRIMASK(masking_state);
		return length_e;
	}

}

// Dequeue a byte from the circular buffer FIFO queue
size_t cbfifo_dequeue(void *buf, size_t nbyte, uint32_t command_type)
{
	uint32_t masking_state;
    size_t length_d = 0;

    if(buf == NULL)
    {
    	return -1;
    }

    else if(fifo_type[command_type].length == 0)
    {
    	return 0;
    }

    else if(nbyte == 0)
    {
    	return 0;
    }

    else if(nbyte > fifo_type[command_type].length)
    {
    	nbyte = fifo_type[command_type].length;
    }

    else
    {
    	nbyte = nbyte;
    }

	// Save and disable the interrupt state
	masking_state = __get_PRIMASK();
	__disable_irq();

	for (int i = 0; i < nbyte; i++)                 		// For loop to dequeue bytes
	{
	    // dequeuing bytes to location pointed by buff
	    *(uint8_t*) buf = fifo_type[command_type].data[fifo_type[command_type].head];
	    length_d++;                     					// Incrementing length of bytes dequeued
	    fifo_type[command_type].length--; 		// Decrementing buffer length
	    buf = (uint8_t*) buf + 1;                         	// Incrementing buffer
	    fifo_type[command_type].head++;          		// Incrementing read pointer
	    if (fifo_type[command_type].head == FIFO_MAX_SIZE) 	// If read pointer reaches maximum size
	    {
	        fifo_type[command_type].head = 0; 			// Read pointer points to beginning i.e. 0
	    }

    	// restore the interrupt state
    	__set_PRIMASK(masking_state);
	}

	// Return the dequeued byte
	return length_d;
}

// Check if the circular buffer FIFO queue is empty
int cbfifo_empty(uint32_t command_type)
{
	return fifo_type[command_type].length == 0;
}

// Check if the circular buffer FIFO queue is full
int cbfifo_full(uint32_t command_type)
{
	return FIFO_MAX_SIZE;
}

// Get the current length of the circular buffer FIFO queue
size_t cbfifo_length(uint32_t command_type)
{
	return fifo_type[command_type].length;
}


