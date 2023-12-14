/*
 * hex_dump.c
 *
 *  Created on: 14-Dec-2023
 *      Author: THARUNI GELLI
 */

/**************************************************************************
 * File includes here
 **************************************************************************/

#include"hex_dump.h"

/******************************************************************************
 * Custom Defines
 *****************************************************************************/
#define HEXDUMP_MAX_SIZE    (640)
#define CHARS_PER_LINE      (16)
#define RIGHT_SHIFT_28      (28)
#define RIGHT_SHIFT_24      (24)
#define RIGHT_SHIFT_20      (20)
#define RIGHT_SHIFT_16      (16)
#define RIGHT_SHIFT_12      (12)
#define RIGHT_SHIFT_8       (8)
#define RIGHT_SHIFT_4       (4)



// Function: int_to_hexchar
// Description: Converts an integer to its corresponding hexadecimal character.
// Parameters:
//   - x: Input integer.
// Return: Hexadecimal character.
static char int_to_hexchar(int x)
{
    if (x >= 0 && x <= 9)
        return '0' + x;
    else if (x >= 10 && x <= 15)
        return 'A' + x - 10;
    else
        return '-';
}


void hexdump(uint32_t start_addr, uint32_t length)
{
    // Declare Variables
    uint8_t *current_address = (uint8_t*) start_addr;
    const uint8_t *end_address = (uint8_t*) start_addr + length;

    // For loop to print hexdump from start address to the given length
    for (int i = 0; i < length; i += CHARS_PER_LINE)
    {
        // Print address header
        putchar(int_to_hexchar(((uint32_t)(current_address)) >> RIGHT_SHIFT_28));
        putchar(int_to_hexchar(((uint32_t)(current_address)) >> RIGHT_SHIFT_24));
        putchar(int_to_hexchar(((uint32_t)(current_address)) >> RIGHT_SHIFT_20));
        putchar(int_to_hexchar(((uint32_t)(current_address)) >> RIGHT_SHIFT_16));
        putchar('_');
        putchar(int_to_hexchar(((uint32_t)(current_address)) >> RIGHT_SHIFT_12));
        putchar(int_to_hexchar(((uint32_t)(current_address)) >> RIGHT_SHIFT_8));
        putchar(int_to_hexchar(((uint32_t)(current_address)) >> RIGHT_SHIFT_4));
        putchar(int_to_hexchar((uint32_t)(current_address) & 0x0000000F));
        putchar(' ');
        putchar(' ');

        // Print hex values
        for (int j = 0; j < CHARS_PER_LINE && current_address + j < end_address; j++)
        {
            putchar(int_to_hexchar(current_address[j] >> RIGHT_SHIFT_4));
            putchar(int_to_hexchar(current_address[j] & 0x0F));
            putchar(' ');
        }

        // Move to the next line
        current_address += CHARS_PER_LINE;
        putchar('\n');
        putchar('\r');
    }
}
