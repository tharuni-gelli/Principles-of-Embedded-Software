/*
 * input_line.c
 *
 *  Created on: 14-Dec-2023
 *      Author: THARUNI GELLI
 */

/******************************************************************************
 * File includes here
 *****************************************************************************/
#include"input_line.h"

/******************************************************************************
 * Defines here
 *****************************************************************************/

// Define the size of the input buffer
#define buffer_size     	(2000)

// Define the Hex ASCII value for Enter
#define Carriage_Return 	(0X0D)

// Define the Hex ASCII value for Backspace
#define Backspace      		(0X08)

// Function to process user input character by character until Enter is pressed
void process_command_input() {
    // Declare local variables
    char buffer[buffer_size];   // Buffer to store user input
    char character;             // Variable to store the currently received character
    int i = 0;                  // Index to track the position in the buffer

    // Continue processing input until Enter is pressed
    while (1) {
        // Wait until a character is received
        while ((cbfifo_length(rec) == 0)) {
            ;
        }

        // Dequeue the received character
        cbfifo_dequeue(&character, 1, rec);

        // Echo the character back to the terminal
        putchar(character);

        // Check if Enter is pressed
        if (character == Carriage_Return) {
            buffer[i] = '\0';   // Terminate the string
            break;
        } else if (character == Backspace) {
            // Handle Backspace: delete the character from the terminal and input buffer
            i--;
            printf(" \b");     // Print a space to overwrite the backspaced character on the terminal
        } else {
            // Store the received character in the input buffer
            buffer[i] = character;
            i++;                // Increment index for the next character
        }
    }

    // Print a new line to move to the next line on the terminal
    printf("\n\r");

    // Process the command based on the user input
    process_command(buffer);
}

