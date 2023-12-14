/*
 * systick.h
 *
 *  Created on: 13-Dec-2023
 *      Author: THARUNI GELLI
 */

#ifndef SYSTICK_H_
#define SYSTICK_H_

/******************************************************************************
 * File includes here
 *****************************************************************************/

#include <MKL25Z4.h>
#include <stdio.h>
#include <stdlib.h>

#define SYSTICK_VALUE 48000000L/1600 // MOD value to get ticks increments for every 10msecs
typedef uint32_t ticktime_t; // Variable to define API's

extern volatile uint32_t count_value; // variable to store no of ticks for every IRQ(for every 10msecs)
extern volatile uint32_t count_reset_value; // To store count value before reset occurred


/*
 * Function brief: This function initializes the systick timer with clock source of 48Mhz
 *
 * Parameters: null
 *
 * Returns: null
 */
void Init_SysTick (void);

/*
 * Function brief: This function increments the count value every time IRQ encountered
 *
 * Parameters: null
 *
 * Returns: null
 */
void SysTick_Handler ();

/*
 * Function brief: This function returns the no of counts occurred till now
 *
 * Parameters: null
 *
 * Returns: null
 */
ticktime_t now();

/*
 * Function brief: This function resets the timer and stores count value till reset in count reset value
 *
 * Parameters: null
 *
 * Returns: null
 */
void reset_timer();

/*
 * Function brief: This function returns time since the last call to reset_timer()
 *
 * Parameters: null
 *
 * Returns: null
 */
ticktime_t get_timer();

#endif /* SYSTICK_H_ */
