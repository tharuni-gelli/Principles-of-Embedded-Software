/*
 * i2c.c
 *
 *  Created on: 14-Dec-2023
 *      Author: THARUNI GELLI
 */


/******************************************************************************
 * File includes here
 *****************************************************************************/
#include "i2c.h"

/******************************************************************************
 * Defines
 *****************************************************************************/
#define MSB_SHIFT		(8)
#define ONE				(1)



// I2c1 Initialize function
void initialize_I2C1(void)
{
    // Enable clock for I2C1
    SIM->SCGC4 |= SIM_SCGC4_I2C1_MASK;

    // Enable clock for Port E
    SIM->SCGC5 |= SIM_SCGC5_PORTE_MASK;
}

// I2c1 Set flags function
void set_I2C1_flags(void)
{
    // Set port for I2C1 SDA (Serial Data Line)
    PORTE->PCR[0] |= PORT_PCR_MUX(6);

    // Set port for I2C1 SCL (Serial Clock Line)
    PORTE->PCR[1] |= PORT_PCR_MUX(6);

    // Clear bits in the control register C1
    I2C1->C1 = 0;

    // Set the frequency divider register and multiplier factor
    I2C1->F = I2C_F_ICR(0x11) |       // The SCL divider multiplied by multiplier factor (mul) determines the I2C baud rate.
              I2C_F_MULT(0);          // Multiplier factor = 1

    // Enable I2C1 interrupt requests
    I2C1->C1 |= (I2C_C1_IICEN_MASK);

    // Select High drive mode
    I2C1->C2 |= (I2C_C2_HDRS_MASK);
}

// Function to read a 16-bit value from a specified register of an I2C device using I2C1 peripheral

uint16_t I2C1_read(uint8_t device_address, uint8_t register_address) {
    // Declare variables
    uint8_t buffer;     // Variable to store MSB of the read value
    uint8_t buffer1;    // Variable to store LSB of the read value
    uint16_t result;    // Variable to store the final 16-bit result

    // Set I2C1 to transmit mode
    I2C1_TRAN;
    // Generate a start condition
    I2C1_M_START;
    // Send device address with LSB set to 0 for writing to the register
    I2C1->D = device_address << ONE;
    TRANS_COM
	I2C1_WAIT;

    // Send the register address to read from
    I2C1->D = register_address;
    TRANS_COM
	I2C1_WAIT;

    // Generate a repeated start condition for read operation
    I2C1_M_RSTART;
    // Send device address with LSB set to 1 for reading from the register
    I2C1->D = (device_address << ONE) | 0x01;
    TRANS_COM
	I2C1_WAIT;

    // Set I2C1 to receive mode
    I2C1_REC;
    // Configure I2C1 to send NACK after receiving a byte
    I2C1_NACK;

    // Read MSB of the value from the register
    buffer = I2C1->D;
    TRANS_COM
	I2C1_WAIT;

    // Read MSB of the value from the register
    buffer = I2C1->D;
    TRANS_COM
	I2C1_WAIT;

    // Read LSB of the value from the register
    buffer1 = I2C1->D;

    // Generate a stop condition
    I2C1_M_STOP;

    // Combine MSB and LSB to form the 16-bit result
    result = (buffer << MSB_SHIFT);
    result += buffer1;

    // Return the final result
    return result;
}

