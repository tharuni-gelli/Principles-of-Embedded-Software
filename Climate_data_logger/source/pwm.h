/**
 * @file    pwm.h
 * @brief   Declaration for all functions in pwm.c file
 *
 * @author  <Tharuni Gelli>
 * @date    <11/14/2023>
 *
 */
#ifndef PWM_H
#define PWM_H

/******************************************************************************
 * File includes here
 *****************************************************************************/
#include "systick.h"
#include <MKL25Z4.h>
#include "rgb_led.h"

#define PWM_PERIOD (255)	//Defined max value for MOD


/*
 * Function brief: This function initializes the clocks for PORD B,D & TPM @ freq of 48Mhz
 *
 * Parameters: null
 *
 * Returns: null
 */
void Init_TPM_LED(void);

/*
 * Function brief: Initializes PWM for red led of PORTB pin 18
 *
 * Parameters: period (to load MOD value)
 *
 * Returns: null
 */
void Init_Red_LED_PWM(uint16_t period);

/*
 * Function brief: Initializes PWM for green led of PORTB pin 19
 *
 * Parameters: period (to load MOD value)
 *
 * Returns: null
 */
void Init_Green_LED_PWM(uint16_t period);

/*
 * Function brief: Initializes PWM for blue led of PORTB pin 1
 *
 * Parameters: period (to load MOD value)
 *
 * Returns: null
 */
void Init_Blue_LED_PWM(uint16_t period);

#endif
