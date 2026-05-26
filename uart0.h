/*
 Header guard start
 Prevents multiple inclusion of this file
*/
#ifndef _UART0_H_
#define _UART0_H_


/*
 Macro to enable UART interrupt (1 = enabled)
*/
#define UART_INT_ENABLE 1


/*
 Oscillator frequency = 12 MHz
*/
#define FOSC      12000000   //Hz


/*
 CPU clock = 5 × oscillator frequency
*/
#define CCLK  	  5*FOSC


/*
 Peripheral clock = CPU clock / 4
*/
#define PCLK  	  CCLK/4


/*
 Baud rate for UART communication
*/
#define BAUD  	  9600


/*
 Divisor value for UART baud rate generation
 Formula: PCLK / (16 × BAUD)
*/
#define DIVISOR   (PCLK/(16 * BAUD))


/*
 Function to initialize UART0
 Sets baud rate, frame format, etc.
*/
void InitUART0(void);


/*
 Function to transmit a single character
*/
void UART0_Tx(char ch);


/*
 Function to receive a single character
*/
char UART0_Rx(void);


/*
 Function to transmit a string
*/
void UART0_Str(char *);


/*
 Function to transmit an unsigned integer
*/
void UART0_Int(unsigned int);


/*
 Function to transmit floating point value
*/
void UART0_Float(float);


#endif
