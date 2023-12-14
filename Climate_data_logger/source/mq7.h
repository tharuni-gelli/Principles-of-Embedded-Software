/*
 * mq7.h
 *
 *  Created on: 14-Dec-2023
 *      Author: THARUNI GELLI
 */

#ifndef MQ7_H_
#define MQ7_H_


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
#include "math.h"
#include "adc.h"

/**
 * @brief Obtain the averaged CO levels value from the Analog-to-Digital Converter (ADC).
 *
 * This function reads 16 samples from the specified channel of the ADC, computes the average,
 * and returns the result. It also ensures that the ADC module is disabled after sampling.
 *
 * @return uint16_t The averaged CO levels value obtained from the ADC.
 */
int get_co_values(void);


#endif /* MQ7_H_ */
