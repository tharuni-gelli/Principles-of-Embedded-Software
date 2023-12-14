/*
 * sht21.h
 *
 *  Created on: 14-Dec-2023
 *      Author: THARUNI GELLI
 */

#ifndef SHT21_H_
#define SHT21_H_

/******************************************************************************
 * File includes here
 *****************************************************************************/
#include "MKL25Z4.h"
#include "fsl_debug_console.h"
#include <stdio.h>
#include <stdint.h>
#include <ctype.h>
#include <string.h>
#include <stdbool.h>
#include "assert.h"
#include "i2c.h"

/**
 * @brief Read and calculate the current temperature value from the SHT21 sensor.
 *
 * This function reads the raw temperature values from the SHT21 sensor, applies
 * the necessary calculations based on the sensor's datasheet, and returns the
 * temperature in degrees Celsius.
 *
 * @return float The current temperature value in degrees Celsius.
 */
float read_temperature(void);

/**
 * @brief Read and calculate the current humidity level value from the SHT21 sensor.
 *
 * This function reads the raw humidity values from the SHT21 sensor, applies
 * the necessary calculations based on the sensor's datasheet, and returns the
 * humidity level in percentage relative humidity (%RH).
 *
 * @return float The current humidity level value in percentage relative humidity.
 */
float read_humidity(void);



#endif /* SHT21_H_ */
