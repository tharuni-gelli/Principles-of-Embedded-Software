/*
 * adc.c
 *
 *  Created on: 14-Dec-2023
 *      Author: THARUNI GELLI
 */

/*********************
 * File includes here
 *********************/
#include "adc.h"

/*********************
 * Defines
 *********************/
#define MSB_MASK 		(0x8000)

/**************************************************
Local function prototype
***************************************************/

// Function: adc_calculate
// Description: Performs calibration for the ADC module.
//              Configures ADC for single-ended 16-bit conversion mode with a divide ratio of 8,
//              sets the ADC clock source to (Bus Clock)/2.
//              Enables hardware averaging with 32 samples and initiates the calibration process.
//              Waits for calibration to complete and checks for success.
//              If successful, calculates the calibration values and sets the MSB.
// Parameters: None
// Return: 0 if calibration is successful, -1 otherwise.

static int adc_calculate(void);


uint16_t adc_read(uint8_t adc_channel)
{
    // Start the conversion by writing to SC1A
    ADC0->SC1[0] = ((adc_channel & ADC_SC1_ADCH_MASK) |
                    (ADC0->SC1[0] &
                     (ADC_SC1_AIEN_MASK | ADC_SC1_DIFF_MASK)));

    // Wait for the conversion to complete
    while(ADC0->SC2 & ADC_SC2_ADACT_MASK);      // Check for conversion in progress
    while(!(ADC0->SC1[0] & ADC_SC1_COCO_MASK));  // Wait until the Conversion Complete Flag is set

    // Return the 16-bit digital value
    return ADC0->R[0];
}



void init_ADC(void)
{
    int calibration_result; // Variable used for calibrating ADC.

    // Enable ADC0 Clock
    SIM->SCGC6 |= SIM_SCGC6_ADC0_MASK;

    // Calibration of ADC
    do
    {
        calibration_result = adc_calculate();
    } while (calibration_result == -1);

    // Configure ADC
    ADC0->SC1[0] |= (ADC_SC1_AIEN_MASK); // Enable conversion complete interrupt
    ADC0->SC1[0] &= ~ADC_SC1_DIFF_MASK;  // Set to Single-Ended ADC

    // Reset CFG1 register
    ADC0->CFG1 = 0;
    ADC0->CFG1 |= (ADC_CFG1_MODE(2)  |    // Single-ended 10-bit mode
                   ADC_CFG1_ADICLK(1)|    // ADC clock source: (Bus Clock)/2
                   ADC_CFG1_ADIV(3)  |     // Divide ratio: 8 (clock rate is (input clock)/8)
                   ADC_CFG1_ADLPC_MASK);  // Low-power configuration

    ADC0->SC3 &= ~ADC_SC3_AVGE_MASK;  // Enable hardware average function
}


static int adc_calculate(void)
{
    uint16_t calib;

    // Configure ADC for calibration
    ADC0->CFG1 |= (ADC_CFG1_MODE(3)  |    // Single-ended 16-bit conversion
                   ADC_CFG1_ADICLK(1)|    // ADC clock source: (Bus Clock)/2
                   ADC_CFG1_ADIV(3));     // Divide ratio: 8 (clock rate is (input clock)/8)

    ADC0->SC3  |= (ADC_SC3_AVGE_MASK |    // Enable hardware average function
                   ADC_SC3_AVGS(3)   |    // Set hardware average to 32 samples
                   ADC_SC3_CAL_MASK);    // Initiate the calibration process

    while (ADC0->SC3 & ADC_SC3_CAL_MASK);  // Wait for calibration to complete

    if (ADC0->SC3 & ADC_SC3_CALF_MASK)    // Check if calibration failed
        return -1;

    // Calculate and set calibration values for gain and offset
    calib = 0;
    calib += ADC0->CLPS + ADC0->CLP4 + ADC0->CLP3 +
             ADC0->CLP2 + ADC0->CLP1 + ADC0->CLP0;
    calib /= 2;
    calib |= MSB_MASK;    // Set MSB
    ADC0->PG = calib;

    calib = 0;
    calib += ADC0->CLMS + ADC0->CLM4 + ADC0->CLM3 +
             ADC0->CLM2 + ADC0->CLM1 + ADC0->CLM0;
    calib /= 2;
    calib |= MSB_MASK;    // Set MSB
    ADC0->MG = calib;

    return 0;
}

