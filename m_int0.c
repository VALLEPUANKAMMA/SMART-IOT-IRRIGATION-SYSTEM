/* Include LPC21xx microcontroller register definitions */
#include <lpc21xx.h>

/* Include user-defined typedef header file */
#include "typedef.h"

/* Include delay function declarations */
#include "delay.h"

/* Define pin configuration for external interrupt input */
#define EINT0_INPUT_PIN 0x000000C5

/* Define VIC channel number for external interrupt */
#define EINT0_VIC_CHNO 15

/* Global volatile flag variable for interrupt detection */
volatile int flag = 0;

/* Optional status LED pin definition (currently disabled) */
/* #define EINT0_STATUS_LED 20 */

/* Interrupt Service Routine declaration for external interrupt */
void eint0_isr(void) __irq;

/* Optional global counter variable (currently disabled) */
/* u32 gcount; */


/* Function to initialize external interrupt */
void init_int(void)
{
	/* Optional clearing of pin select bits (currently disabled) */
	/* PINSEL0 &= ~(3<<2); */

	/* Configure pin for external interrupt function */
	PINSEL0 |= EINT0_INPUT_PIN;

	/* Enable external interrupt in VIC */
	VICIntEnable = 1 << EINT0_VIC_CHNO;

	/* Configure vector control register for interrupt channel */
	VICVectCntl1 = (1 << 5) | EINT0_VIC_CHNO;

	/* Assign ISR address to vector address register */
	VICVectAddr1 = (u32)eint0_isr;

	/* Configure interrupt as edge-triggered mode */
	EXTMODE |= 1 << 1;
}


/* Interrupt Service Routine for external interrupt */
void eint0_isr(void) __irq
{
	/* Delay for switch debounce */
	delay_ms(20);

	/* Set interrupt flag */
	flag = 1;

	/* Clear external interrupt flag */
	EXTINT = 1 << 1;

	/* Inform VIC that interrupt handling is complete */
	VICVectAddr = 0;
}
