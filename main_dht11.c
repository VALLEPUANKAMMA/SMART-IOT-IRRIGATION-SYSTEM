#include <lpc214x.h>				

#include "uart0.h"

#include "delay.h"

#include "lcd.h"

#include "esp01.h"

#include "dht11.h"

#include "kpm.h"

#define FOSC      12000000

#define CCLK  	  5*FOSC

#define PCLK  	  CCLK/4

#define PREINT_VAL  ((PCLK/32768)-1)

#define PREFRAC_VAL  (PCLK - ((PREINT_VAL + 1) * 32768))

 

void rtc_init()
{

	SEC=20; //Initialized seconds

	MIN=21; //Initialized minutes

	HOUR=12;//Initialized hour

}

extern char buff[100],dummy;

extern unsigned char i,ch,r_flag;

char I_t1,I_t2,I_t3;//Iregation timings	are 1 min / 2 min / 3 min
//char S_t1,S_t2;	//soil readings
 char T_t1,H_t1,T_t2,H_t2,T_t3,H_t3; // Temprature and Humidity timings
extern volatile int flag;

unsigned char humidity_integer, humidity_decimal, temp_integer, temp_decimal, checksum;
   
extern int humidity,temperature;

  /*InitUART0();

	LCD_Init();

	PREINT=PREINT_VAL;

  PREFRAC=PREFRAC_VAL;

   CCR=0x01; //timer started

   rtc_init();

	Write_CMD_LCD(0x80);

	Write_str_LCD("ESP01 Interface");
                                                                                                               
  delay_ms(1000);
  
  esp01_connectAP();
   */

/*void dht11_display(void)
{

		dht11_request();

		dht11_response();

		humidity_integer = dht11_data();

		humidity_decimal = dht11_data();

		temp_integer = dht11_data();

		temp_decimal = dht11_data();

		checksum = dht11_data();

		humidity=humidity_integer+humidity_decimal;

		temperature=temp_integer+temp_decimal;

		if( (humidity_integer + humidity_decimal + temp_integer + temp_decimal) != checksum )
		  {
			Write_str_LCD("Checksum Error\r\n");
		   }
		else
		{
		   	//Write_DAT_LCD('.');

			Write_CMD_LCD(0x80);

			Write_str_LCD("H : ");

			Write_int_LCD(humidity_integer);

			Write_DAT_LCD('.');

			Write_int_LCD(humidity_decimal);

			Write_str_LCD(" % RH ");

			Write_CMD_LCD(0xC0);

			Write_str_LCD("T : ");

			Write_int_LCD(temp_integer);

			Write_DAT_LCD('.');

			Write_int_LCD(temp_decimal);

			Write_DAT_LCD(223);

			Write_str_LCD("C");

			Write_CMD_LCD(0xD4);

			Write_str_LCD("Checksum : ");

			Write_int_LCD(checksum);

			delay_ms(3000);

			//Write_CMD_LCD(0x01);
			//arr[0]=humidity_integer;

			//arr[1]=temp_integer;

			esp01_sendToThingspeak1(humidity);
			
			delay_s(16);

			esp01_sendToThingspeak2(temperature);
			
			delay_s(16);
			}
} */
int flag1=0,flag2=0;
void SetIrrigationTiming(void)
{
int val;
flag1=1;
    

    Write_CMD_LCD(0x01);
    
    Write_str_LCD("Set Motor Time");
    
    delay_ms(800);
    
    val = Get1DigitValue("Enter HighTem LowHum:");
    
	    if(val != -1) I_t1 = val;

		Write_CMD_LCD(0x01);

    val = Get1DigitValue("Enter ModTem ModHum:");
    
    if(val != -1) I_t2 = val;

		Write_CMD_LCD(0x01);


    val = Get1DigitValue("Enter LowTemp HighHum:");
    
    if(val != -1) I_t3 = val;

    Write_CMD_LCD(0x01);

    Write_CMD_LCD(0x80);
    
    Write_str_LCD("Saved Successfully");
    
    delay_ms(1000);
    
    Write_CMD_LCD(0X01);
}


/* void SetMoisture_Threshold(void)
{
    int val;

    Write_CMD_LCD(0x01);
    Write_str_LCD("Set Moisture");
    delay_ms(800);

    val = Get2DigitValue("Dry Threshold:");
    if(val != -1) S_t1 = val;

    val = Get2DigitValue("Wet Threshold:");
    if(val != -1) S_t2 = val;

    Write_CMD_LCD(0x01);
    Write_str_LCD("Saved");
    delay_ms(1000);
}  */


void Set_Temp_Humidity(void)
{
	int val;
	flag2=1;
    

    Write_CMD_LCD(0x01);
    Write_str_LCD("Set Temp & Hum");
    delay_ms(800);


	Write_str_LCD("Temp Range (0-50)");

    val = Get2DigitValue("ENTER TEMPRATURE1:");
    if(val != -1) T_t1 = val;

    Write_str_LCD("Humrange is (0-99)");
	val = Get2DigitValue("ENTER HUMIDITY1:");
    if(val != -1) H_t1 = val;


 Write_str_LCD("Temp Range (0-50)");
    val = Get2DigitValue("ENTER TEMPRATURE2:");
    if(val != -1) T_t2 = val;

	Write_str_LCD("Humrange is (0-100)");
    val = Get2DigitValue("ENTER HUMIDITY2:");
    if(val != -1) H_t2 = val;


 Write_str_LCD("Temp Range (0-50)");
    val = Get2DigitValue("ENTER TEMPRATURE3:");
    if(val != -1) T_t3 = val;

	Write_str_LCD("Humrange is (0-100)");
    val = Get2DigitValue("ENTER HUMIDITY3:");
    if(val != -1) H_t3 = val;

    Write_CMD_LCD(0x01);
    Write_str_LCD("Saved");
    delay_ms(1000);
    Write_CMD_LCD(0X01);
}



void menu_base_int(void)
{	 char ch;
    if(flag == 1)
    {
        
		flag = 0;
        Write_CMD_LCD(0x01);
        Write_CMD_LCD(0x80);
        Write_str_LCD("1.Irrigation Time");
        Write_CMD_LCD(0xC0);
        //Write_str_LCD("2.Moisture Thresh");
        //Write_CMD_LCD(0x94);
        Write_str_LCD("3.Temp & Humidity");
        Write_CMD_LCD(0xD4);
        Write_str_LCD("Select Option:");
	ch = keyScan();
        switch(ch)
        {
            case '1': SetIrrigationTiming(); break;
            //case '2': SetMoisture_Threshold(); break;
            case '3': Set_Temp_Humidity(); break;
            default:
                Write_CMD_LCD(0x01);
                Write_str_LCD("Invalid Option");
                delay_ms(1000);
        }
    }
}

void compare_temp_hum(void)
{
int delay_time;
 if((flag1==1) && (flag2==1))
{
delay_time=0;
	//flag1=0;
  

// Check soil moisture first
if ((IOPIN0 >> 21) & 1)
{
int cnt=0;
    if ((temperature >= T_t1) && (humidity <= H_t1))
        delay_time = I_t1;

    else if ((temperature >= T_t2) && (humidity >= H_t2))
        delay_time = I_t2;

    else if ((temperature <= T_t3) && (humidity <= H_t3))
        delay_time = I_t3;

    // If any condition matched
    if (delay_time > 0)
    {
        Write_CMD_LCD(0x01);
        Write_str_LCD("MOTOR TURN ON");

        IOSET0 = 1 << 20;   // Motor ON
        esp01_sendToThingspeak3(1);
				
				while(1)
				{

        //delay_s(60 * delay_time);

				cnt++;

				delay_s(1);
				if((cnt==(delay_time*60)) || ((IOPIN0 >> 21) & 1)==0)
				{
				break;
				}

				}
				IOCLR0 = 1 << 20;   // Motor OFF
        
				Write_CMD_LCD(0x01);

				
				esp01_sendToThingspeak3(0);
        

        
    }
}
}
}
