/*
 * mq7.c
 *
 *  Created on: 14-Dec-2023
 *      Author: THARUNI GELLI
 */

/******************************************************************************
 * File includes here
 *****************************************************************************/
#include "mq7.h"

/******************************************************************************
 * Defines
 *****************************************************************************/

#define CO_SENSOR_CHN   		(15)				// ADC15 channel is mapped to PTC1 pin of KL25Z
#define DISABLE_ADC  			(31)				// Writing 0x1F (31) to ADCH register to disable the ADC
#define Right_shift_4 			 (4)
#define AVG_16					(16)

int get_co_values(void)
{
    // Declare variables
    static uint16_t adc_result;        // Variable to accumulate ADC results
    static uint16_t adc_result_avg;    // Variable to store the averaged ADC result
    static uint8_t i;                  // Loop variable

    // Get 16 ADC results for CO sensor
    for (i = 0; i < AVG_16; i++) {
        adc_result += adc_read(CO_SENSOR_CHN);
    }

    // Compute the average ADC value
    adc_result_avg = adc_result >> Right_shift_4;
    adc_result = 0;  // Reset the result accumulator

    // Disable the ADC Module for the specified channel
    ADC0->SC1[0] |= ADC_SC1_ADCH(DISABLE_ADC);

    // Return the averaged CO levels value
    return adc_result_avg;
}
