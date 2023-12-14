
/*******************************************************************************
 * Copyright (C) 2023 by <Tharuni Gelli>
 *
 * Redistribution, modification or use of this software in source or binary
 * forms is permitted as long as the files maintain this copyright. Users are
 * permitted to modify this and use it to learn about the field of embedded
 * software. <Tharuni Gelli> and the University of Colorado are not liable for
 * any misuse of this material.
 * ****************************************************************************/

/**
 * @file    rgb_blink.c
 * @brief   This file gives the definitions for all the
 *          functions mentioned in rgb_blink.h
 *
 *
 *
 *
 * @author  <Tharuni Gelli>
 * @date    <16/10/2023>
 *
 *
 */

#include "rgb_led.h"

/******************************************************************************
 * Defines
 *****************************************************************************/
#define PWM_MAX				(255)	// Maximum PWM value for RGB Led
#define ONE_MS			(5347)	// Constant to generate 1ms delay

//Delay function to generate loop as per the input time.
void Delay(volatile int time)
{
    time = time*ONE_MS;				// Multiplying time with an approximated value to get desired delay.
    while(time--)							// Decrementing the counter to get the desired delay.
    {
        __asm volatile("NOP");
    }
}

void RGB_Manup(unsigned int R_value, unsigned int G_value, unsigned int B_value)
{
	TPM2->CONTROLS[0].CnV = R_value ; // Update cnv value for R as per input
	TPM2->CONTROLS[1].CnV = G_value ; // Update cnv value for G as per input
	TPM0->CONTROLS[1].CnV = B_value ; // Update cnv value for B as per input
}

// PWM test function to test all the values of different states
void test_pwm(void)
{
    for (int i=0; i<=PWM_MAX; i++)
    {
    	RGB_Manup(i,0,0);
        Delay(5);
    }
    for (int i=0; i<=PWM_MAX; i++)
    {
    	RGB_Manup(PWM_MAX,i,0);
        Delay(5);
    }
    for (int i=0; i<=PWM_MAX; i++)
    {
    	RGB_Manup(0,i,0);
        Delay(5);
    }
}
