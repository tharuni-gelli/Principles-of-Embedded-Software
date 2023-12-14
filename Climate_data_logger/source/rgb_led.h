/*
 * rgb_led.h
 *
 *  Created on: 14-Dec-2023
 *      Author: THARUNI GELLI
 */

#ifndef RGB_LED_H_
#define RGB_LED_H_

/******************************************************************************
 * File includes here
 *****************************************************************************/
#include "MKL25Z4.h"
#include"pwm.h"

void Delay(volatile int time);


/*
 * Function brief: This function updates TPM channels values for each led
 *
 * Parameters: R_value, G_value & B_value
 *
 * Returns: null
 */
void RGB_Manup(unsigned int R_value, unsigned int G_value, unsigned int B_value);


/**
 * @brief Test the Pulse Width Modulation (PWM) functionality.
 *
 * This function is responsible for testing and demonstrating the PWM functionality.
 * It may involve configuring PWM settings, generating PWM signals, and observing
 * the behavior of the PWM output. The specifics of the test can be found within the
 * function implementation.
 */
void test_pwm(void);



#endif /* RGB_LED_H_ */
