/*
 * systick.c
 *
 *  Created on: 13-Dec-2023
 *      Author: THARUNI GELLI
 */

#include "systick.h"

volatile uint32_t count_value = 0; // to store no of ticks for every IRQ encounter
volatile uint32_t count_reset_value = 0; // to store count value till reset occurrence

void Init_SysTick() 						// initialize the timing system
{
    SysTick->LOAD = SYSTICK_VALUE;			//Storing value in load register-30000 for 10msec
    NVIC_SetPriority(SysTick_IRQn,3);		//setting interrupt priority
    SysTick->VAL = 0;
    SysTick->CTRL=	SysTick_CTRL_TICKINT_Msk| SysTick_CTRL_ENABLE_Msk;	//enabling interrupt
    NVIC_EnableIRQ(SysTick_IRQn);
}

void SysTick_Handler() 						//Systick module interrupt handler to handle IRQ
{
	count_value++; // Increment the value to store no of ticks (every 100msecs)
}

ticktime_t now()							// returns time since startup
{
    return(count_value); // No of counts till startup
}
void reset_timer()							// resets timer to Zero
{
    count_reset_value = now(); // No of counts till startup, till reset
    Init_SysTick(); // Resets by initializing
}

ticktime_t get_timer()						//returns time since the last call to reset_timer()
{
    return(count_value-count_reset_value); // returns time since the last call to reset_timer()
}
