/**
 * @file    pwm.c
 * @brief   This file gives the definitions for all the
 *          functions mentioned in pwm.h
 *          It includes pin definitions, MASK & initialization of TPM modes for port B and port D.
 *
 *
 *
 *
 * @author  <Tharuni Gelli>
 * @date    <11/14/2023>
 * @credits <Dean-Dean's Book>
 * @resource <alexander-g-dean - github>
 *
 */


#include "pwm.h"


#define MASK(x) (1UL << (x)) // To define MASK


#define RED_LED (18)     // on port B blue pin is 18
#define GREEN_LED (19)   // on port B blue pin is 19
#define BLUE_LED (1)		// on port D blue pin is 1

void Init_TPM_LED(void)
{
	// Enable clock to port D
	SIM->SCGC5 |= SIM_SCGC5_PORTB_MASK | SIM_SCGC5_PORTD_MASK;
	// Configure TPM
	SIM->SCGC6 |= SIM_SCGC6_TPM2_MASK | SIM_SCGC6_TPM0_MASK;

	//set clock source for tpm: 24 MHz
	SIM->SOPT2 |= (SIM_SOPT2_TPMSRC(1));
}


void Init_Red_LED_PWM(uint16_t period)
{
	// Red TPM2_CH0, Mux Alt 3
	// Set pin to FTMs
	PORTB->PCR[RED_LED] &= ~PORT_PCR_MUX_MASK;
	PORTB->PCR[RED_LED] |= PORT_PCR_MUX(3);

	//load the counter and mod
	TPM2->MOD = period-1;
	//set TPM count direction to up with a divide by 2 prescaler
	TPM2->SC =  TPM_SC_PS(1);
	// Continue operation in debug mode
	TPM2->CONF |= TPM_CONF_DBGMODE(3);
	// Set channel 0 to edge-aligned low-true PWM
	TPM2->CONTROLS[0].CnSC = TPM_CnSC_MSB_MASK | TPM_CnSC_ELSA_MASK;
	// Set initial duty cycle
	TPM2->CONTROLS[0].CnV = 0;
	// Start TPM
	TPM2->SC |= TPM_SC_CMOD(1);
}

void Init_Green_LED_PWM(uint16_t period)
{
	// Green TPM2_CH1, Mux Alt 3
	// Set pin to FTMs
	PORTB->PCR[GREEN_LED] &= ~PORT_PCR_MUX_MASK;
	PORTB->PCR[GREEN_LED] |= PORT_PCR_MUX(3);

	// Set channel 1 to edge-aligned low-true PWM
	TPM2->CONTROLS[1].CnSC = TPM_CnSC_MSB_MASK | TPM_CnSC_ELSA_MASK;
	// Set initial duty cycle
	TPM2->CONTROLS[1].CnV = 0;
	// Start TPM
	TPM2->SC |= TPM_SC_CMOD(1);
}

void Init_Blue_LED_PWM(uint16_t period)
{
	// Blue TPM0_CH1, Mux Alt 4
	// Set pin to FTMs
	PORTD->PCR[BLUE_LED] &= ~PORT_PCR_MUX_MASK;
	PORTD->PCR[BLUE_LED] |= PORT_PCR_MUX(4);

	//load the counter and mod
	TPM0->MOD = period-1;
	//set TPM count direction to up with a divide by 2 prescaler
	TPM0->SC =  TPM_SC_PS(1);
	// Continue operation in debug mode
	TPM0->CONF |= TPM_CONF_DBGMODE(3);
	// Set channel 1 to edge-aligned low-true PWM
	TPM0->CONTROLS[1].CnSC = TPM_CnSC_MSB_MASK | TPM_CnSC_ELSA_MASK;
	// Set initial duty cycle
	TPM0->CONTROLS[1].CnV = 0;
	// Start TPM
	TPM0->SC |= TPM_SC_CMOD(1);
}


