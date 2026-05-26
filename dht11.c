/* Include LPC214x microcontroller register definitions */
#include <lpc214x.h>

/* Include delay function declarations */
#include "delay.h"

/* Include bit manipulation macros */
#include "defines.h"

/* Define input mode for GPIO pin */
#define input 0

/* Define output mode for GPIO pin */
#define output 1

/* DHT11 data pin connected to P0.4 */
#define DHT11 4


/* Function to send start request signal to DHT11 sensor */
void dht11_request(void)
{
	/* Configure DHT11 pin as output */
	WRITEBIT(IODIR0, DHT11, output);

	/* Pull DHT11 pin LOW for at least 18 ms to start communication */
	WRITEBIT(IOPIN0, DHT11, 0);

	/* Wait for 20 ms */
	delay_ms(20);

	/* Pull DHT11 pin HIGH and wait for sensor response */
	WRITEBIT(IOPIN0, DHT11, 1);
}


/* Function to receive acknowledgment response from DHT11 */
void dht11_response(void)
{
	/* Configure DHT11 pin as input */
	WRITEBIT(IODIR0, DHT11, input);

	/* Wait until sensor pulls line LOW */
	while(READBIT(IOPIN0, DHT11) == 1);

	/* Wait until sensor pulls line HIGH */
	while(READBIT(IOPIN0, DHT11) == 0);

	/* Wait until sensor completes response and line goes LOW */
	while(READBIT(IOPIN0, DHT11) == 1);
}


/* Function to read one byte (8 bits) of data from DHT11 */
unsigned char dht11_data(void)
{
	/* Variable to count received bits */
	unsigned char count;

	/* Variable to store received data */
	unsigned char data = 0;

	/* Loop to receive 8 bits */
	for(count = 0; count < 8; count++)
	{
		/* Wait until DHT11 starts sending bit (line goes HIGH) */
		while(READBIT(IOPIN0, DHT11) == 0);

		/* Wait 30 microseconds to determine bit value */
		delay_us(30);

		/* Check if line is still HIGH (bit = 1) */
		if(READBIT(IOPIN0, DHT11))
		{
			/* Shift left and store 1 */
			data = ((data << 1) | 0x01);
		}
		else
		{
			/* Shift left and store 0 */
			data = (data << 1);
		}

		/* Wait until current bit transmission ends */
		while(READBIT(IOPIN0, DHT11));
	}

	/* Return received byte */
	return data;
}
