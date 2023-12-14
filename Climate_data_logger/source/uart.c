/*
 * uart.c
 *
 *  Created on: 13-Dec-2023
 *      Author: THARUNI GELLI
 */
#include "uart.h"
// Define constants for UART configuration
#define OVERSAMPLE_RATE 16
#define DATA_BIT 0
#define STOP_BIT 1
#define PARITY_BIT 0
#define SYSCLOCK_FREQUENCY (24e6)

// Function for handling system write operations
int __sys_write(int handle, char *buf, int size)
{
    if(buf == NULL)
    {
    	return -1;
    }

    while(cbfifo_length(trans)==cbfifo_full(trans))
    {
    	;
    }

    if(cbfifo_enqueue(buf,size,trans)==0)
    {
    	return -1;
    }

    else
    {
    	  // If the transmit interrupt is not enabled, enable it
    	  if (!(UART0->C2 & UART0_C2_TIE_MASK))
    	  {
    	       UART0->C2 |= UART0_C2_TIE(1);
    	  }

    	  // Return success
    	  return 0;
    }
}

// Function for reading a character from the receive queue
int __sys_readc(void)
{
    uint8_t ch;

    // Wait until the receive queue is not empty
    while (cbfifo_length(rec) == 0);

    // Dequeue a character from the receive queue
    if(cbfifo_dequeue(&ch,1,rec)==1)
    {
    // Return the dequeued character
    return ch;
    }
    else
    {
    	return -1;
    }
}

// Function to initialize UART0
void init_UART0(uint32_t baud_rate) {

    uint16_t sbr;

    // Enable UART0 and its associated port
    SIM->SCGC4 |= SIM_SCGC4_UART0_MASK;
    SIM->SCGC5 |= SIM_SCGC5_PORTA_MASK;

    // Disable UART0 transmitter and receiver during configuration
    UART0->C2 &= ~UART0_C2_TE_MASK & ~UART0_C2_RE_MASK;

    // Select the clock source for UART0
    SIM->SOPT2 |= SIM_SOPT2_UART0SRC(1);

    // Configure UART0 pins (TX and RX)
    PORTA->PCR[1] = PORT_PCR_ISF_MASK | PORT_PCR_MUX(2); //Rx
    PORTA->PCR[2] = PORT_PCR_ISF_MASK | PORT_PCR_MUX(2); //Tx

    // Calculate the baud rate settings
    sbr = (uint16_t)((SYSCLOCK_FREQUENCY) / (baud_rate * OVERSAMPLE_RATE));

    // Set the baud rate registers
    UART0->BDH &= ~UART0_BDH_SBR_MASK;
    UART0->BDH |= UART0_BDH_SBR(sbr >> 8);
    UART0->BDL = UART0_BDL_SBR(sbr);
    UART0->C4 |= UART0_C4_OSR(OVERSAMPLE_RATE - 1);

    // Configure other UART0 settings
    UART0->BDH |= UART0_BDH_RXEDGIE(0) | UART0_BDH_SBNS(STOP_BIT) | UART0_BDH_LBKDIE(0);
    UART0->C1 = UART0_C1_LOOPS(0) | UART0_C1_M(DATA_BIT) | UART0_C1_PE(PARITY_BIT);
    UART0->C3 = UART0_C3_TXINV(0) | UART0_C3_ORIE(0) | UART0_C3_NEIE(0) | UART0_C3_FEIE(0) | UART0_C3_PEIE(0);
    UART0->S1 = UART0_S1_OR(1) | UART0_S1_NF(1) | UART0_S1_FE(1) | UART0_S1_PF(1);
    UART0->S2 = UART0_S2_MSBF(0) | UART0_S2_RXINV(0);

    // Enable interrupts. Listing 8.11 on p. 234

    NVIC_SetPriority(UART0_IRQn, 2); // 0, 1, 2, or 3
    NVIC_ClearPendingIRQ(UART0_IRQn);
    NVIC_EnableIRQ(UART0_IRQn);

    // Enable UART0 transmitter, receiver, and receive interrupt
    UART0->C2 |= UART0_C2_RIE(1) |  UART0_C2_TE(1) | UART0_C2_RE(1);

    // Clear the UART RDRF flag
    UART0->S1 &= ~UART0_S1_RDRF_MASK;
}

// Interrupt handler for UART0
void UART0_IRQHandler(void)
{
    uint8_t rec_ch;
    uint8_t trans_ch;


    // Check for overrun, noise, framing, or parity errors
    if (UART0->S1 & (UART_S1_OR_MASK | UART_S1_NF_MASK | UART_S1_FE_MASK | UART_S1_PF_MASK))
    {
        // Clear error flags
        UART0->S1 |= UART0_S1_OR_MASK | UART0_S1_NF_MASK | UART0_S1_FE_MASK | UART0_S1_PF_MASK;

        // Read the character causing the error
        rec_ch = UART0->D;
    }

    // Check if data is ready to be read
    if (UART0->S1 & UART0_S1_RDRF_MASK)
    {
        // Read the character
        rec_ch = UART0->D;

        // Check if the receive queue is not full
        if ((!cbfifo_full(rec) == cbfifo_length(rec)))
        {
            // Enqueue the character
            cbfifo_enqueue(&rec_ch,1,rec);
        }
        else
        {
            // Handle error (queue full)
        }
    }

    // Check if transmit buffer is empty and transmit interrupt is enabled
    if ((UART0->C2 & UART0_C2_TIE_MASK) && (UART0->S1 & UART0_S1_TDRE_MASK))
    {
        // Check if transmit queue is not empty
        if (cbfifo_dequeue(&trans_ch,1,trans))
        {
            // Dequeue and send the character
            UART0->D = trans_ch;
        }
        else
        {
            // Disable transmit interrupt
            UART0->C2 &= ~UART0_C2_TIE_MASK;
        }
    }
}





