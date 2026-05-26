/*
 Project : Smart IoT Irrigation System
 MCU     : LPC2148 (ARM7)
 Author  : Ankamma Vallepu
 Platform: Embedded C (Keil / LPC21xx)
*/ 


/*
 Include LPC21xx microcontroller register definitions
*/
#include <lpc21xx.h>

/*
 Include LCD function declarations
*/
#include "lcd.h"

/*
 Include keypad module declarations
*/
#include "kpm.h"

/*
 Include UART0 communication functions
*/
#include "uart0.h"

/*
 Include ESP01 Wi-Fi module functions
*/
#include "esp01.h"

/*
 RTC header is currently not used
*/
//#include "rtc.h"

/*
 Include delay functions
*/
#include "delay.h"

/*
 Include external interrupt functions
*/
#include "m_int0.h"

/*
 Include UART0 again (duplicate include)
*/
#include "uart0.h"

/*
 Include DHT11 sensor functions
*/
#include "dht11.h"

/*
 Include main DHT11 related declarations
*/
#include "main_dht11.h"

/*
 Include main project function declarations
*/
#include "main_code.h"


/*
 Define ThingSpeak send interval
 Data will be sent every 3 minutes
*/
#define SEND_INTERVAL 3


/*
 External interrupt flag variable
*/
extern int flag;


/*
 Global variables to store final humidity
 and temperature values
*/
int humidity, temperature;


/*
 Stores the last minute at which
 data was sent to ThingSpeak
*/
int last_sent_min = -1;



/*
 Main function starts here
*/
int main()
{
	/*
	 Variables to store DHT11 raw data
	*/
	unsigned char humidity_integer;
	unsigned char humidity_decimal;
	unsigned char temp_integer;
	unsigned char temp_decimal;
	unsigned char checksum;

	/*
	 Configure P0.20 as output
	 Used to control motor ON/OFF
	*/
	IODIR0 = 1 << 20;

	/*
	 Configure P0.21 as input
	 Used to read soil moisture sensor
	 0 = Wet
	 1 = Dry
	*/
	IODIR0 &= ~(1 << 21);

	/*
	 Initialize UART0 communication
	*/
	InitUART0();

	/*
	 Initialize LCD display
	*/
	LCD_Init();

	/*
	 Display project title
	*/
	Write_str_LCD("SMART IRRIGATION");

	/*
	 Wait 1 second
	*/
	delay_ms(1000);

	/*
	 Clear LCD
	*/
	Write_CMD_LCD(0x01);

	/*
	 Initialize keypad module
	*/
	Initkpm();

	/*
	 Initialize external interrupt
	*/
	init_int();

	/*
	 Initialize Real Time Clock
	*/
	rtc_init();

	/*
	 Connect ESP01 to Wi-Fi
	*/
	esp01_connectAP();

	/*
	 Wait for stability
	*/
	delay_ms(1000);

	/*
	 Clear LCD
	*/
	Write_CMD_LCD(0x01);

	/*
	 Infinite loop starts
	*/
	while(1)
	{
		/*
		 Delay 3 seconds before
		 reading DHT11 sensor
		*/
		delay_s(3);

		/*
		 Send start signal to DHT11
		*/
		dht11_request();

		/*
		 Wait for DHT11 response
		*/
		dht11_response();

		/*
		 Read humidity integer part
		*/
		humidity_integer = dht11_data();

		/*
		 Read humidity decimal part
		*/
		humidity_decimal = dht11_data();

		/*
		 Read temperature integer part
		*/
		temp_integer = dht11_data();

		/*
		 Read temperature decimal part
		*/
		temp_decimal = dht11_data();

		/*
		 Read checksum byte
		*/
		checksum = dht11_data();

		/*
		 Calculate total humidity
		*/
		humidity = humidity_integer + humidity_decimal;

		/*
		 Calculate total temperature
		*/
		temperature = temp_integer + temp_decimal;

		/*
		 Verify checksum correctness
		*/
		if((humidity_integer + humidity_decimal +
		    temp_integer + temp_decimal) != checksum)
		{
			/*
			 Display checksum error
			*/
			Write_str_LCD("Checksum Error\r\n");
		}
		else
		{
			/*
			 Move LCD cursor to first line
			*/
			Write_CMD_LCD(0x80);

			/*
			 Display humidity label
			*/
			Write_str_LCD("Humidity : ");

			/*
			 Display humidity integer
			*/
			Write_int_LCD(humidity_integer);

			/*
			 Display decimal point
			*/
			Write_DAT_LCD('.');

			/*
			 Display humidity decimal
			*/
			Write_int_LCD(humidity_decimal);

			/*
			 Display humidity unit
			*/
			Write_str_LCD(" % RH ");

			/*
			 Move cursor to second line
			*/
			Write_CMD_LCD(0xC0);

			/*
			 Display temperature label
			*/
			Write_str_LCD("Temprature : ");

			/*
			 Display temperature integer
			*/
			Write_int_LCD(temp_integer);

			/*
			 Display decimal point
			*/
			Write_DAT_LCD('.');

			/*
			 Display temperature decimal
			*/
			Write_int_LCD(temp_decimal);

			/*
			 Display degree symbol
			*/
			Write_DAT_LCD(223);

			/*
			 Display Celsius symbol
			*/
			Write_str_LCD("C");

			/*
			 Move cursor to fourth line
			*/
			Write_CMD_LCD(0xD4);

			/*
			 Display checksum label
			*/
			Write_str_LCD("Checksum : ");

			/*
			 Display checksum value
			*/
			Write_int_LCD(checksum);

			/*
			 Delay 3 seconds so user can read
			*/
			delay_ms(3000);

			/*
			 Check if current minute is a
			 multiple of SEND_INTERVAL
			 and ensure data is sent only once
			*/
			if((MIN % SEND_INTERVAL == 0) &&
			   (MIN != last_sent_min))
			{
				/*
				 Send humidity and temperature
				 to ThingSpeak cloud
				*/
				esp01_sendToThingspeak1(
					humidity,
					temperature
				);

				/*
				 Update last sent minute
				*/
				last_sent_min = MIN;
			}
		}

		/*
		 Check if interrupt occurred
		 and open configuration menu
		*/
		menu_base_int();

		/*
		 Compare current temperature
		 and humidity with user thresholds
		 and control motor
		*/
		compare_temp_hum();
	}
}
