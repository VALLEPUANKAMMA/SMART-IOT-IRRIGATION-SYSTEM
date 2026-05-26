/* Include LPC214x microcontroller register definitions */
#include <lpc214x.h>				

/* Include UART0 function declarations */
#include "uart0.h"

/* Include delay function declarations */
#include "delay.h"

/* Include LCD function declarations */
#include "lcd.h"

/* Include ESP01 Wi-Fi module function declarations */
#include "esp01.h"

/* Include DHT11 sensor function declarations */
#include "dht11.h"

/* Include keypad function declarations */
#include "kpm.h"


/* Define crystal oscillator frequency as 12 MHz */
#define FOSC      12000000

/* Define CPU clock frequency as 5 × oscillator frequency */
#define CCLK  	  5*FOSC

/* Define peripheral clock frequency as CPU clock / 4 */
#define PCLK  	  CCLK/4

/* Calculate RTC integer prescaler value */
#define PREINT_VAL  ((PCLK/32768)-1)

/* Calculate RTC fractional prescaler value */
#define PREFRAC_VAL  (PCLK - ((PREINT_VAL + 1) * 32768))


/* Function to initialize RTC time */
void rtc_init()
{
	/* Initialize seconds register with 20 */
	SEC = 20;

	/* Initialize minutes register with 21 */
	MIN = 21;

	/* Initialize hours register with 12 */
	HOUR = 12;
}


/* External UART receive buffer */
extern char buff[100];

/* External dummy variable */
extern char dummy;

/* External UART receive index */
extern unsigned char i;

/* External received character */
extern unsigned char ch;

/* External UART receive flag */
extern unsigned char r_flag;


/* Irrigation timing variables
   Stores motor ON duration for different conditions */
char I_t1, I_t2, I_t3;

/* Temperature and humidity threshold variables */
char T_t1, H_t1;
char T_t2, H_t2;
char T_t3, H_t3;

/* External interrupt flag */
extern volatile int flag;


/* Variables to store DHT11 humidity data */
unsigned char humidity_integer;
unsigned char humidity_decimal;

/* Variables to store DHT11 temperature data */
unsigned char temp_integer;
unsigned char temp_decimal;

/* Variable to store DHT11 checksum */
unsigned char checksum;

/* Final humidity and temperature values */
extern int humidity;
extern int temperature;


/* Flags to check if settings are configured */
int flag1 = 0;
int flag2 = 0;


/* Function to configure irrigation timings */
void SetIrrigationTiming(void)
{
    /* Local variable to store keypad input */
    int val;

    /* Set irrigation timing configured flag */
    flag1 = 1;

    /* Clear LCD display */
    Write_CMD_LCD(0x01);

    /* Display heading */
    Write_str_LCD("Set Motor Time");

    /* Delay for readability */
    delay_ms(800);

    /* Ask user for high temp / low humidity motor time */
    val = Get1DigitValue("Enter HighTem LowHum:");

    /* If user entered valid value, store in I_t1 */
    if(val != -1)
        I_t1 = val;

    /* Clear LCD */
    Write_CMD_LCD(0x01);

    /* Ask user for moderate temp / moderate humidity time */
    val = Get1DigitValue("Enter ModTem ModHum:");

    /* Store if valid */
    if(val != -1)
        I_t2 = val;

    /* Clear LCD */
    Write_CMD_LCD(0x01);

    /* Ask user for low temp / high humidity time */
    val = Get1DigitValue("Enter LowTemp HighHum:");

    /* Store if valid */
    if(val != -1)
        I_t3 = val;

    /* Clear LCD */
    Write_CMD_LCD(0x01);

    /* Move cursor to first row */
    Write_CMD_LCD(0x80);

    /* Show success message */
    Write_str_LCD("Saved Successfully");

    /* Wait for 1 second */
    delay_ms(1000);

    /* Clear LCD */
    Write_CMD_LCD(0x01);
}


/* Function to configure temperature and humidity thresholds */
void Set_Temp_Humidity(void)
{
    /* Local variable to store keypad input */
    int val;

    /* Set threshold configured flag */
    flag2 = 1;

    /* Clear LCD */
    Write_CMD_LCD(0x01);

    /* Show heading */
    Write_str_LCD("Set Temp & Hum");

    /* Delay for readability */
    delay_ms(800);

    /* Show valid temperature range */
    Write_str_LCD("Temp Range (0-50)");

    /* Read first temperature threshold */
    val = Get2DigitValue("ENTER TEMPRATURE1:");

    /* Store if valid */
    if(val != -1)
        T_t1 = val;

    /* Show humidity range */
    Write_str_LCD("Hum range (0-99)");

    /* Read first humidity threshold */
    val = Get2DigitValue("ENTER HUMIDITY1:");

    /* Store if valid */
    if(val != -1)
        H_t1 = val;

    /* Show temperature range again */
    Write_str_LCD("Temp Range (0-50)");

    /* Read second temperature threshold */
    val = Get2DigitValue("ENTER TEMPRATURE2:");

    /* Store if valid */
    if(val != -1)
        T_t2 = val;

    /* Show humidity range */
    Write_str_LCD("Hum range (0-100)");

    /* Read second humidity threshold */
    val = Get2DigitValue("ENTER HUMIDITY2:");

    /* Store if valid */
    if(val != -1)
        H_t2 = val;

    /* Show temperature range */
    Write_str_LCD("Temp Range (0-50)");

    /* Read third temperature threshold */
    val = Get2DigitValue("ENTER TEMPRATURE3:");

    /* Store if valid */
    if(val != -1)
        T_t3 = val;

    /* Show humidity range */
    Write_str_LCD("Hum range (0-100)");

    /* Read third humidity threshold */
    val = Get2DigitValue("ENTER HUMIDITY3:");

    /* Store if valid */
    if(val != -1)
        H_t3 = val;

    /* Clear LCD */
    Write_CMD_LCD(0x01);

    /* Show saved confirmation */
    Write_str_LCD("Saved");

    /* Delay */
    delay_ms(1000);

    /* Clear LCD */
    Write_CMD_LCD(0x01);
}
