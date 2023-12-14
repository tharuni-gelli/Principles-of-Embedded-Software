/*
 * hex_dump.h
 *
 *  Created on: 14-Dec-2023
 *      Author: THARUNI GELLI
 */

#ifndef HEX_DUMP_H_
#define HEX_DUMP_H_

/******************************************************************************
 * File includes here
 *****************************************************************************/
#include <stdio.h>
#include <string.h>
#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <stdint.h>


// Function: hexdump
// Description: Prints a hexdump of memory starting from the specified address for the given length.
// Parameters:
//   - start_addr: Start address of the memory to hexdump.
//   - length: Length of memory to hexdump.
// Return: None.
void hexdump(uint32_t Start, uint32_t Len);


#endif /* HEX_DUMP_H_ */
