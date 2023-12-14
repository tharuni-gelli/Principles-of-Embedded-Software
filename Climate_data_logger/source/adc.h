/*
 * adc.h
 *
 *  Created on: 14-Dec-2023
 *      Author: THARUNI GELLI
 */

#ifndef ADC_H_
#define ADC_H_

/*********************
 * File includes here
 *********************/
#include <stdio.h>
#include "MKL25Z4.h"
#include "fsl_debug_console.h"
#include <stdint.h>
#include <ctype.h>
#include <string.h>
#include <stdbool.h>
#include "assert.h"


// Function: adc_read
// Description: Reads analog input from the specified ADC channel.
// Parameters:
//   - adc_channel: The ADC channel to read from.
// Return: The 16-bit digital value representing the analog input.
uint16_t adc_read(uint8_t adc_channel);


// Function: init_ADC
// Description: Initializes the ADC module.
// Note: Assumes the presence of a function 'adc_cal' for ADC calibration.
//       The calibration process is repeated until successful.
//       The ADC module is configured for single-ended 10-bit mode,
//       with a conversion complete interrupt enabled and hardware averaging enabled.
//       The ADC clock source is set to (Bus Clock)/2, and the divide ratio is 8.
//       Low-power configuration is also enabled.
// Return: None
void init_ADC(void);





#endif /* ADC_H_ */
