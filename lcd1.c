/* Include LPC21xx microcontroller register definitions */
#include <LPC21xx.h>

/* Include delay function declarations */
#include "delay.h"

/* Include LCD function declarations */
#include "lcd.h"

/* Include bit manipulation macro definitions */
#include "defines.h"

/* Define LCD data pins starting from P0.8 */
#define LCD_DAT 8

/* Define LCD Register Select pin as P0.16 */
#define RS 16

/* Define LCD Read/Write pin as P0.18 */
#define RW 18

/* Define LCD Enable pin as P0.17 */
#define EN 17


/* Function to initialize LCD */
void LCD_Init(void)
{
	/* Configure LCD data pins as output */
	WRITEBYTE(IODIR0,LCD_DAT,0xFF);

	/* Configure RS pin as output */
	WRITEBIT(IODIR0,RS,1);

	/* Configure RW pin as output */
	WRITEBIT(IODIR0,RW,1);

	/* Configure EN pin as output */
	WRITEBIT(IODIR0,EN,1);

	/* Delay for LCD power stabilization */
	delay_ms(16);

	/* Send initialization command */
	Write_CMD_LCD(0x30);

	/* Delay after command */
	delay_ms(6);

	/* Send initialization command again */
	Write_CMD_LCD(0x30);

	/* Delay after command */
	delay_ms(1);

	/* Send initialization command third time */
	Write_CMD_LCD(0x30);

	/* Set LCD to 8-bit mode, 2-line display */
	Write_CMD_LCD(0x38);

	/* Turn ON display and cursor OFF, 5x7 font */
	Write_CMD_LCD(0x0C);

	/* Optional command to shift cursor left (currently disabled) */
	/* Write_CMD_LCD(0x10); */

	/* Clear LCD display */
	Write_CMD_LCD(0x01);

	/* Move cursor to right after each character */
	Write_CMD_LCD(0x06);

	/* Optional command to enable blinking cursor (currently disabled) */
	/* Write_CMD_LCD(0x0F); */
}


/* Function to send command to LCD */
void Write_CMD_LCD(char cmd)
{
	/* Clear RS pin to indicate command mode */
	WRITEBIT(IOCLR0,RS,1);

	/* Send command byte to LCD */
	Write_LCD(cmd);
}


/* Function to send data to LCD */
void Write_DAT_LCD(char dat)
{
	/* Set RS pin to indicate data mode */
	WRITEBIT(IOSET0,RS,1);

	/* Send data byte to LCD */
	Write_LCD(dat);
}


/* Function to write a byte to LCD */
void Write_LCD(char ch)
{
	/* Clear RW pin to select write mode */
	WRITEBIT(IOCLR0,RW,1);

	/* Write byte to LCD data pins */
	WRITEBYTE(IOPIN0,LCD_DAT,ch);

	/* Set Enable pin HIGH */
	WRITEBIT(IOSET0,EN,1);

	/* Small delay for enable pulse */
	delay_us(1);

	/* Set Enable pin LOW */
	WRITEBIT(IOCLR0,EN,1);

	/* Delay for LCD processing */
	delay_ms(2);
}


/* Function to display string on LCD */
void Write_str_LCD(char *p)
{
	/* Loop until end of string */
	while(*p)

		/* Display current character and move pointer */
		Write_DAT_LCD(*p++);
}


/* Function to display signed integer on LCD */
void Write_int_LCD(signed int n)
{
	/* Array to store digits */
	char a[10],i=0;

	/* Check if number is negative */
	if(n<0)
	{
		/* Display minus sign */
		Write_DAT_LCD('-');

		/* Convert number to positive */
		n=-n;
	}

	/* Extract digits one by one */
	do
	{
		/* Store ASCII value of digit */
		a[i++]=n%10+48;

		/* Remove last digit */
		n=n/10;

	}while(n);

	/* Display digits in correct order */
	for(;i>0;i--)

		/* Print each digit */
		Write_DAT_LCD(a[i-1]);
}


/* Function to display floating point number on LCD */
void Write_float_LCD(float f,char i)

/* First argument (f) is float number to display */

/* Second argument (i) is number of digits after decimal point */
{
	/* Extract integer part */
	unsigned long int n=f;

	/* Display integer part */
	Write_int_LCD(n);

	/* Display decimal point */
	Write_DAT_LCD('.');

	/* Loop to display fractional digits */
	for(;i>0;i--)
	{
		/* Shift next decimal digit */
		f=f*10;

		/* Extract shifted digit */
		n=f;

		/* Display current decimal digit */
		Write_DAT_LCD(n%10+48);
	}
}
