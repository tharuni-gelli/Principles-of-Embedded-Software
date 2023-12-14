/*
 * sht21.c
 *
 *  Created on: 14-Dec-2023
 *      Author: THARUNI GELLI
 */

/******************************************************************************
 * File includes here
 *****************************************************************************/
#include "sht21.h"


/******************************************************************************
 * Defines
 *****************************************************************************/
/**
 * @brief I2C device address for SHT21 sensor (refer to the datasheet).
 */
#define SHT21_ADDRESS (0x40)

/**
 * @brief Hold master register address to obtain the temperature value from the SHT21 sensor.
 */
#define TEMPERATURE (0xE3)

/**
 * @brief Hold master register address to obtain the humidity value from the SHT21 sensor.
 */
#define HUMIDITY (0xE5)


float read_temperature(void) {
    // Save the raw values obtained from the sensor in a variable
    uint16_t raw_data = I2C1_read(SHT21_ADDRESS, TEMPERATURE);

    // Clear the last 2 bits of the raw data
    raw_data &= ~0x003;

    // Calculate and return the result in °C using the formula from the datasheet (page 9, module 6.2)
    return (-46.85 + 175.72 / 65536 * (float)raw_data);
}


float read_humidity(void) {
    // Save the raw values obtained from the sensor in a variable
    uint16_t raw_data = I2C1_read(SHT21_ADDRESS, HUMIDITY);

    // Clear the last 2 bits of the raw data
    raw_data &= ~0x003;

    // Calculate and return the result in %RH using the formula from the datasheet (page 9, module 6.1)
    return (-6.0 + 125.0 / 65536 * (float)raw_data);
}
