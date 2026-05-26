/* Include user-defined typedef header file */
#include "typedef.h"

/* Function to generate microsecond delay */
void delay_us(u32 dlys)
{
	/* Loop for required microsecond delay */
	for(dlys*=12;dlys>0;dlys--);
}

/* Function to generate millisecond delay */
void delay_ms(u32 dlys)
{
	/* Loop for required millisecond delay */
	for(dlys*=12000;dlys>0;dlys--);
}

/* Function to generate second delay */
void delay_s(u32 dlys)
{
	/* Loop for required second delay */
	for(dlys*=12000000;dlys>0;dlys--);
}
