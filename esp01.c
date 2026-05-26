/* Include string handling functions */
#include <string.h>

/* Include UART0 header file */
#include "uart0.h"

/* Include delay function header */
#include "delay.h"

/* Include LCD function header */
#include "lcd.h"

/* External buffer to store ESP01 response */
extern char buff[200];

/* External variable to track buffer index */
extern unsigned char i;

/* Function to connect ESP01 to Wi-Fi access point */
void esp01_connectAP()
{
	/* Clear LCD display */
	Write_CMD_LCD(0x01);

	/* Move cursor to first row */
	Write_CMD_LCD(0x80);

	/* Display "AT" on LCD */
	Write_str_LCD("AT");

	/* Wait for 1 second */
	delay_ms(1000);

	/* Send AT command to ESP01 */
	UART0_Str("AT\r\n");

	/* Reset index and clear receive buffer */
	i=0;memset(buff,'\0',200);

	/* Wait until 4 characters are received */
	while(i<4);

	/* Delay for response stability */
	delay_ms(500);

	/* Add null terminator to received string */
	buff[i] = '\0';

	/* Clear LCD display */
	Write_CMD_LCD(0x01);

	/* Move cursor to first row */
	Write_CMD_LCD(0x80);

	/* Display received response */
	Write_str_LCD(buff);

	/* Delay for 2 seconds */
	delay_ms(2000);

	/* Check if response contains "OK" */
	if(strstr(buff,"OK"))
	{
		/* Move cursor to second row */
		Write_CMD_LCD(0xC0);

		/* Display "OK" */
		Write_str_LCD("OK");

		/* Delay for 1 second */
		delay_ms(1000);		
	}
	else
	{
		/* Move cursor to second row */
		Write_CMD_LCD(0xC0);

		/* Display "ERROR" */
		Write_str_LCD("ERROR");

		/* Delay for 1 second */
		delay_ms(1000);		

		/* Exit function if error */
		return;
	}

	/* Clear LCD display */
	Write_CMD_LCD(0x01);

	/* Move cursor to first row */
	Write_CMD_LCD(0x80);

	/* Display "ATE0" on LCD */
	Write_str_LCD("ATE0");

	/* Delay for 1 second */
	delay_ms(1000);

	/* Send ATE0 command to disable echo */
	UART0_Str("ATE0\r\n");

	/* Reset index and clear buffer */
	i=0;memset(buff,'\0',200);

	/* Wait until 4 characters received */
	while(i<4);

	/* Delay for response stability */
	delay_ms(500);

	/* Null terminate received string */
	buff[i] = '\0';

	/* Clear LCD display */
	Write_CMD_LCD(0x01);

	/* Move cursor to first row */
	Write_CMD_LCD(0x80);

	/* Display received response */
	Write_str_LCD(buff);

	/* Delay for 2 seconds */
	delay_ms(2000);

	/* Check if response contains "OK" */
	if(strstr(buff,"OK"))
	{
		/* Move cursor to second row */
		Write_CMD_LCD(0xC0);

		/* Display "OK" */
		Write_str_LCD("OK");

		/* Delay for 1 second */
		delay_ms(1000);		
	}
	else
	{
		/* Move cursor to second row */
		Write_CMD_LCD(0xC0);

		/* Display "ERROR" */
		Write_str_LCD("ERROR");

		/* Delay for 1 second */
		delay_ms(1000);		

		/* Exit function */
		return;
	}

	/* Clear LCD display */
	Write_CMD_LCD(0x01);

	/* Move cursor to first row */
	Write_CMD_LCD(0x80);

	/* Display "AT+CIPMUX" */
	Write_str_LCD("AT+CIPMUX");

	/* Delay for 1 second */
	delay_ms(1000);

	/* Send command to set single connection mode */
	UART0_Str("AT+CIPMUX=0\r\n");

	/* Reset index and clear buffer */
	i=0;memset(buff,'\0',200);

	/* Wait for response */
	while(i<4);

	/* Delay for stability */
	delay_ms(500);

	/* Null terminate response */
	buff[i] = '\0';

	/* Clear LCD */
	Write_CMD_LCD(0x01);

	/* Move cursor */
	Write_CMD_LCD(0x80);

	/* Display response */
	Write_str_LCD(buff);

	/* Delay for 2 seconds */
	delay_ms(2000);

	/* Check for successful response */
	if(strstr(buff,"OK"))
	{
		/* Move cursor to second row */
		Write_CMD_LCD(0xC0);

		/* Display "OK" */
		Write_str_LCD("OK");

		/* Delay */
		delay_ms(1000);		
	}
	else
	{
		/* Move cursor to second row */
		Write_CMD_LCD(0xC0);

		/* Display "ERROR" */
		Write_str_LCD("ERROR");

		/* Delay */
		delay_ms(1000);		

		/* Exit */
		return;
	}
	/* Clear LCD display */
	Write_CMD_LCD(0x01);

	/* Move cursor to first row */
	Write_CMD_LCD(0x80);

	/* Display "AT+CWQAP" on LCD */
	Write_str_LCD("AT+CWQAP");

	/* Wait for 1 second */
	delay_ms(1000);

	/* Send command to disconnect from current Wi-Fi */
	UART0_Str("AT+CWQAP\r\n");

	/* Reset index and clear buffer */
	i=0;memset(buff,'\0',200);

	/* Wait until 4 characters are received */
	while(i<4);

	/* Wait for response completion */
	delay_ms(1500);

	/* Null terminate response string */
	buff[i] = '\0';

	/* Clear LCD display */
	Write_CMD_LCD(0x01);

	/* Move cursor to first row */
	Write_CMD_LCD(0x80);

	/* Display ESP01 response */
	Write_str_LCD(buff);

	/* Delay for 2 seconds */
	delay_ms(2000);

	/* Check if response contains "OK" */
	if(strstr(buff,"OK"))
	{
		/* Move cursor to second row */
		Write_CMD_LCD(0xC0);

		/* Display success message */
		Write_str_LCD("OK");

		/* Delay for 1 second */
		delay_ms(1000);		
	}
	else
	{
		/* Move cursor to second row */
		Write_CMD_LCD(0xC0);

		/* Display error message */
		Write_str_LCD("ERROR");

		/* Delay for 1 second */
		delay_ms(1000);		

		/* Exit function */
		return;
	}

	/* Clear LCD display */
	Write_CMD_LCD(0x01);

	/* Move cursor to first row */
	Write_CMD_LCD(0x80);

	/* Display "AT+CWJAP" */
	Write_str_LCD("AT+CWJAP");

	/* Wait for 1 second */
	delay_ms(1000);

	/* Need to change Wi-Fi name and password */
	//need to change the wifi network name and password

	/* Send Wi-Fi connection command with SSID and password */
	UART0_Str("AT+CWJAP=\"AK\",\"123456789\"\r\n");

	/* Reset index and clear buffer */
	i=0;memset(buff,'\0',200);

	/* Wait until 4 characters received */
	while(i<4);

	/* Wait longer for Wi-Fi connection */
	delay_ms(2500);

	/* Null terminate received string */
	buff[i] = '\0';

	/* Clear LCD */
	Write_CMD_LCD(0x01);

	/* Move cursor to first row */
	Write_CMD_LCD(0x80);

	/* Display received response */
	Write_str_LCD(buff);

	/* Delay for 2 seconds */
	delay_ms(2000);

	/* Check if Wi-Fi connected successfully */
	if(strstr(buff,"WIFI CONNECTED"))
	{
		/* Move cursor to second row */
		Write_CMD_LCD(0xC0);

		/* Display "OK" */
		Write_str_LCD("OK");

		/* Delay for 1 second */
		delay_ms(1000);		
	}
	else
	{
		/* Move cursor to second row */
		Write_CMD_LCD(0xC0);

		/* Display "ERROR" */
		Write_str_LCD("ERROR");

		/* Delay for 1 second */
		delay_ms(1000);		

		/* Exit function */
		return;
	}
}

/* Function to send temperature and humidity data to ThingSpeak */
void esp01_sendToThingspeak1(float val1,float val2)
{
	/* Commented LCD clear command */
	//Write_CMD_LCD(0x01);

	/* Commented LCD cursor set */
	//	Write_CMD_LCD(0x80);

	/* Commented LCD display command */
	//Write_str_LCD("AT+CIPSTART");

	/* Wait for 1 second */
	delay_ms(1000);

	/* Start TCP connection to ThingSpeak server */
	UART0_Str("AT+CIPSTART=\"TCP\",\"api.thingspeak.com\",80\r\n");

	/* Reset index and clear buffer */
	i=0;memset(buff,'\0',200);

	/* Wait until 5 characters received */
	while(i<5);

	/* Wait for connection response */
	delay_ms(2500);

	/* Null terminate response */
	buff[i] = '\0';

	/* Delay for 2 seconds */
	delay_ms(2000);

	/* Check if connection successful */
	if(strstr(buff,"CONNECT") || strstr(buff,"ALREADY CONNECTED"))
	{
		/* Delay before next command */
		delay_ms(1000);

		/* Delay before sending data */
		delay_ms(1000);

		/* Send command specifying data length */
		UART0_Str("AT+CIPSEND=64\r\n");

		/* Reset buffer */
		i=0;memset(buff,'\0',200);

		/* Wait for prompt */
		//while(buff[i] != '>');

		/* Delay */
		delay_ms(500);

		/* Need to change ThingSpeak API key */
		//need to change the thingspeak write API key accordind to your channel

		/* Send HTTP GET request with API key */
		UART0_Str("GET /update?api_key=HWVLM0FXWP9G7IAM&field1=");

		/* Send humidity value */
		UART0_Float(val2);

		/* Send second field identifier */
		UART0_Str("&field2=");

		/* Send temperature value */
		UART0_Float(val1);

		/* End HTTP request */
		UART0_Str("\r\n\r\n");

		/* Wait for upload */
		delay_ms(5000);

		/* Additional delay */
		delay_ms(5000);

		/* Null terminate buffer */
		buff[i] = '\0';

		/* Delay for response */
		delay_ms(2000);

		/* Check if data sent successfully */
		if(strstr(buff,"SEND OK"))
		{
			/* Delay after successful update */
			delay_ms(1000);			
		}
		else
		{
			/* Clear LCD */
			Write_CMD_LCD(0x01);

			/* Show error message */
			Write_str_LCD("TEMPRATURE IS NOT UPDATED");

			/* Delay */
			delay_ms(1000);
			
			/* Clear LCD */
			Write_CMD_LCD(0x01);	
		}
	}
	else
	{
		/* Move cursor to second row */
		Write_CMD_LCD(0xC0);

		/* Display connection error */
		Write_str_LCD("ERROR1");

		/* Delay */
		delay_ms(1000);
		
		/* Clear LCD */
		Write_CMD_LCD(0x01);		

		/* Exit function */
		return;
	}
}
/* Function to send humidity data to ThingSpeak */
void esp01_sendToThingspeak2(float val)
{
	/* Commented LCD clear command */
	//	Write_CMD_LCD(0x01);

	/* Commented LCD cursor command */
	//	Write_CMD_LCD(0x80);

	/* Commented LCD display text */
	//	Write_str_LCD("AT+CIPSTART");

	/* Wait for 1 second */
	delay_ms(1000);

	/* Start TCP connection with ThingSpeak server */
	UART0_Str("AT+CIPSTART=\"TCP\",\"api.thingspeak.com\",80\r\n");

	/* Reset buffer index and clear buffer */
	i=0;
	memset(buff,'\0',200);

	/* Wait until at least 5 characters received */
	while(i<5);

	/* Wait for response completion */
	delay_ms(2500);

	/* Add string terminator */
	buff[i] = '\0';

	/* Commented LCD commands */
	//	Write_CMD_LCD(0x01);
	//	Write_CMD_LCD(0x80);
	//	Write_str_LCD(buff);

	/* Delay for 2 seconds */
	delay_ms(2000);

	/* Check if ESP connected successfully */
	if(strstr(buff,"CONNECT") || strstr(buff,"ALREADY CONNECTED"))
	{
		/* Commented LCD success display */
		//	Write_CMD_LCD(0xC0);
		//	Write_str_LCD("OK");

		/* Wait before sending data */
		delay_ms(1000);

		/* Commented LCD commands */
		//	Write_CMD_LCD(0x01);
		//	Write_CMD_LCD(0x80);
		//	Write_str_LCD("AT+CIPSEND");

		/* Wait for 1 second */
		delay_ms(1000);

		/* Send data length command */
		UART0_Str("AT+CIPSEND=51\r\n");

		/* Reset index and clear buffer */
		i=0;
		memset(buff,'\0',200);

		/* Wait for > prompt (commented) */
		//while(buff[i] != '>');

		/* Delay before sending GET request */
		delay_ms(500);

		/* Need to change ThingSpeak API key */
		//need to change the thingspeak write API key accordind to your channel

		/* Send HTTP GET request with field2 */
		UART0_Str("GET /update?api_key=HWVLM0FXWP9G7IAM&field2=");

		/* Commented string send */
		//	UART0_Str(val);

		/* Send float humidity value */
		UART0_Float(val);

		/* End HTTP request */
		UART0_Str("\r\n\r\n");

		/* Wait for upload */
		delay_ms(5000);

		/* Additional wait */
		delay_ms(5000);

		/* Null terminate buffer */
		buff[i] = '\0';

		/* Commented LCD response display */
		//	Write_CMD_LCD(0x01);
		//	Write_CMD_LCD(0x80);
		//	Write_str_LCD(buff);

		/* Delay for 2 seconds */
		delay_ms(2000);

		/* Check if data was sent successfully */
		if(strstr(buff,"SEND OK"))
		{
			/* Commented LCD success message */
			//	Write_CMD_LCD(0x01);
			//	Write_str_LCD("DATA UPDATED");

			/* Delay after successful transmission */
			delay_ms(1000);

			/* Commented LCD clear */
			//	Write_CMD_LCD(0x01);
		}
		else
		{
			/* Clear LCD */
			Write_CMD_LCD(0x01);

			/* Show humidity update failure */
			Write_str_LCD("HUMIDITY IS NOT UPADTED");

			/* Delay for 1 second */
			delay_ms(1000);

			/* Clear LCD */
			Write_CMD_LCD(0x01);
		}
	}
	else
	{
		/* Move cursor to second row */
		Write_CMD_LCD(0xC0);

		/* Display connection error */
		Write_str_LCD("ERROR2");

		/* Delay for 1 second */
		delay_ms(1000);

		/* Clear LCD */
		Write_CMD_LCD(0x01);

		/* Exit function */
		return;
	}
}


/* Function to send motor status data to ThingSpeak */
void esp01_sendToThingspeak3(float val)
{
	/* Commented LCD clear */
	// Write_CMD_LCD(0x01);

	/* Commented cursor set */
	// Write_CMD_LCD(0x80);

	/* Commented LCD text */
	// Write_str_LCD("AT+CIPSTART");

	/* Wait for 1 second */
	delay_ms(1000);

	/* Start TCP connection to ThingSpeak */
	UART0_Str("AT+CIPSTART=\"TCP\",\"api.thingspeak.com\",80\r\n");

	/* Reset index */
	i = 0;

	/* Clear receive buffer */
	memset(buff, '\0', 200);

	/* Wait until response received */
	while(i < 5);

	/* Wait for connection completion */
	delay_ms(2500);

	/* Add null terminator */
	buff[i] = '\0';

	/* Commented LCD display */
	// Write_CMD_LCD(0x01);
	// Write_CMD_LCD(0x80);
	// Write_str_LCD(buff);

	/* Delay for 2 seconds */
	delay_ms(2000);

	/* Check connection success */
	if(strstr(buff, "CONNECT") || strstr(buff, "ALREADY CONNECTED"))
	{
		/* Commented LCD OK display */
		// Write_CMD_LCD(0xC0);
		// Write_str_LCD("OK");

		/* Wait before next command */
		delay_ms(1000);

		/* Commented LCD commands */
		// Write_CMD_LCD(0x01);
		// Write_CMD_LCD(0x80);
		// Write_str_LCD("AT+CIPSEND");

		/* Wait 1 second */
		delay_ms(1000);

		/* Send data length command */
		UART0_Str("AT+CIPSEND=51\r\n");

		/* Reset index */
		i = 0;

		/* Clear buffer */
		memset(buff, '\0', 200);

		/* Wait for prompt (commented) */
		// while(buff[i] != '>');

		/* Delay before GET request */
		delay_ms(500);

		/* Change API key according to your ThingSpeak channel */
		// Change the ThingSpeak Write API key according to your channel

		/* Send GET request with field3 */
		UART0_Str("GET /update?api_key=HWVLM0FXWP9G7IAM&field3=");

		/* Send motor status float value */
		UART0_Float(val);

		/* End HTTP request */
		UART0_Str("\r\n\r\n");

		/* Wait for transmission */
		delay_ms(5000);

		/* Additional wait */
		delay_ms(5000);

		/* Null terminate response */
		buff[i] = '\0';

		/* Commented LCD display */
		// Write_CMD_LCD(0x01);
		// Write_CMD_LCD(0x80);
		// Write_str_LCD(buff);

		/* Delay for response */
		delay_ms(2000);

		/* Check if data sent successfully */
		if(strstr(buff, "SEND OK"))
		{
			/* Commented success message */
			// Write_CMD_LCD(0x01);
			// Write_str_LCD("DATA UPDATED");

			/* Delay */
			delay_ms(1000);

			/* Commented LCD clear */
			// Write_CMD_LCD(0x01);
		}
		else
		{
			/* Clear LCD */
			Write_CMD_LCD(0x01);

			/* Display motor update failure */
			Write_str_LCD("MOTOR DATA NOT UPDATED");

			/* Delay */
			delay_ms(1000);

			/* Clear LCD */
			Write_CMD_LCD(0x01);
		}
	}
	else
	{
		/* Move cursor to second line */
		Write_CMD_LCD(0xC0);

		/* Display error message */
		Write_str_LCD("ERROR2");

		/* Delay */
		delay_ms(1000);

		/* Clear LCD */
		Write_CMD_LCD(0x01);

		/* Exit function */
		return;
	}
}
