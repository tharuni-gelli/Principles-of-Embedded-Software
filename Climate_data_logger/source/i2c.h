/*
 * i2c.h
 *
 *  Created on: 14-Dec-2023
 *      Author: THARUNI GELLI
 */

#ifndef I2C_H_
#define I2C_H_

/******************************************************************************
 * File includes here
 *****************************************************************************/
#include <stdio.h>
#include "MKL25Z4.h"
#include "fsl_debug_console.h"
#include <stdint.h>
#include <ctype.h>
#include <string.h>
#include <stdbool.h>
#include "assert.h"

/******************************************************************************
 *	Defines
 *****************************************************************************/

// I2c start signal with selecting master mode
#define I2C1_M_START (I2C1->C1 |= I2C_C1_MST_MASK)

// I2c Stop signal with selecting slave mode
#define I2C1_M_STOP 	(I2C1->C1 &= ~I2C_C1_MST_MASK)

// define to set the repeat start bit for generating the repeated start condition of I2c
#define I2C1_M_RSTART (I2C1->C1 |= I2C_C1_RSTA_MASK)

//Transit mode for I2c
#define I2C1_TRAN (I2C1->C1 |= I2C_C1_TX_MASK)

//Receiver mode for I2c
#define I2C1_REC (I2C1->C1 &= ~I2C_C1_TX_MASK)

// I2c wait define to wait until interrupt
#define I2C1_WAIT while((I2C1->S & I2C_S_IICIF_MASK)==0);\
					I2C1->S |= I2C_S_IICIF_MASK;

// Not acknowledge signal for I2c
#define I2C1_NACK (I2C1->C1 |= I2C_C1_TXAK_MASK)

// Acknowledge signal for I2c
#define I2C1_ACK (I2C1->C1 &= ~I2C_C1_TXAK_MASK)

// Wait until the transfer of byte and acknowledgment signal is completed
#define TRANS_COM while((I2C1->S & I2C_S_TCF_MASK)==0);


// Function: initialize_I2C1
// Description: Initializes I2C1 by enabling the necessary clocks.
// Parameters: None
// Return: None
void initialize_I2C1(void);

// Function: set_I2C1_flags
// Description: Configures I2C1 by setting the necessary port and control registers.
// Parameters: None
// Return: None
void set_I2C1_flags(void);

// Function: read_raw_data_from_sensor
// Description: Reads raw data from a sensor using I2C communication.
// Parameters:
//   - device_addr: I2C address of the sensor device.
//   - reg_addr: Register address from which to read the data.
// Return: The 16-bit raw data read from the sensor.
uint16_t I2C1_read(uint8_t device_address,uint8_t register_address);



#endif /* I2C_H_ */
