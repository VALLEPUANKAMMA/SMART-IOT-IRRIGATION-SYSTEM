/* Include LPC21xx microcontroller register definitions */
#include <lpc21xx.h>

/* Include user-defined typedef header file */
#include "typedef.h"

/* Include bit manipulation macro definitions */
#include "defines.h"

/* Include string handling functions */
#include <string.h>

/* Include delay function declarations */
#include "delay.h"

/* Include keypad macro definitions */
#include "kpm_defines.h"

/* Include LCD function declarations */
#include "lcd.h"

/* Keypad lookup table for key mapping */
u8 kpmLUT[4][4]={{'1','2','3','4'},
	{'5','6','7','8'},
	{'9','0','*','#'},
	{'A','B','C','1'}};	

/* Function to initialize keypad */
void Initkpm(void)
{
	/* Configure row pins as output */
	WNIBBLE(IODIR1,ROW0,15);
}

/* Function to scan keypad columns */
u32 ColScan(void)
{
	/* Check if any key is pressed in columns */
	return ((RNIBBLE(IOPIN1,COL0)<15)?0:1);
}

/* Function to identify which row is active */
u32 RowCheck(void)
{
	/* Variable to store row number */
	u32 rno;

	/* Scan all rows one by one */
	for(rno=0;rno<4;rno++)
	{
		/* Activate one row at a time */
		WNIBBLE(IOPIN1,ROW0,~(1<<rno));

		/* Check if key is detected */
		if(ColScan()==0)
		{
			/* Exit loop when key is found */
			break;
		}
	}

	/* Restore all rows to default state */
	WNIBBLE(IOPIN1,ROW0,0X0);

	/* Return detected row number */
	return rno;
}

/* Function to identify which column is active */
u32 ColCheck(void)
{
	/* Variable to store column number */
	u32 cno;

	/* Scan all columns */
	for(cno=0;cno<4;cno++)
	{
		/* Check for active low signal */
		if(RBIT(IOPIN1,(COL0+cno))==0)
		{
			/* Exit loop when key is found */
			break;
		}
	}

	/* Return detected column number */
	return cno;
}

/* Function to scan keypad and return key value */
u32 keyScan(void)
{
	/* Variables for row, column, and key value */
	u32 rno,cno,keyV;

	/* Wait until key is pressed */
	while(ColScan());

	/* Detect row number */
	rno=RowCheck();

	/* Detect column number */
	cno=ColCheck();

	/* Get actual key value from lookup table */
	keyV=kpmLUT[rno][cno];

	/* Wait until key is released */
	while(!ColScan());

	/* Return key value */
	return keyV;
}

/* Function to read multiple-digit number from keypad */
u32 ReadNum(void)
{
	/* Variable to store pressed key */
	u8 key;

	/* Variable to store final number */
	u32 sum=0;

	/* Infinite loop for reading keys */
	while(1)
	{
		/* Scan pressed key */
		key=keyScan();

		/* Check if key is numeric */
		if(key>='0' && key<='9')
		{
			/* Initialize LCD */
			LCD_Init();

			/* Display pressed key */
			Write_LCD(key);

			/* Convert character to number and append */
			sum=(sum*10)+(key-'0');
		}

		/* Check if '=' key is pressed */
		else if(key=='=')
		{
			/* Stop input */
			break;
		} 
	}

	/* Return entered number */
	return sum;
}

/* Function to read 2-digit value from keypad */
int Get2DigitValue(char *msg)
{
    /* Array to store two input digits */
    char arr[3] = {0};

    /* Variable for key input */
    char key;

    /* Index variable */
    int i = 0;

    /* Variable to store converted value */
    int val;

again:
    /* Reset index */
    i = 0;

    /* Clear stored digits */
    arr[0] = arr[1] = 0;

    /* Clear LCD display */
    Write_CMD_LCD(0x01);

    /* Move cursor to row 1 */
    Write_CMD_LCD(0x80);

    /* Display input message */
    Write_str_LCD(msg);

    /* Move cursor to row 4 */
    Write_CMD_LCD(0xD4);

    /* Read two digits */
    while(i < 2)
    {
        /* Scan keypad */
        key = keyScan();

        /* Accept only numeric keys */
        if(key >= '0' && key <= '9')
        {
            /* Store digit */
            arr[i++] = key;

            /* Display digit */
            Write_DAT_LCD(key);

            /* Delay for debounce */
            delay_ms(100);
        }

        /* Handle backspace using C key */
        else if(key == 'C' && i > 0)
        {
            /* Move back index */
            i--;

            /* Move LCD cursor left */
            Write_CMD_LCD(0x10);

            /* Clear previous digit */
            Write_DAT_LCD(' ');

            /* Move cursor back */
            Write_CMD_LCD(0x10);
        }

        /* Handle skip using * key */
        else if(key == '*')
        {
            /* Clear LCD */
            Write_CMD_LCD(0x01);

            /* Display skipped message */
            Write_str_LCD("Skipped");

            /* Delay */
            delay_ms(500);

            /* Return skip code */
            return -1;
        }
    }

    /* Convert characters to integer */
    val = (arr[0]-'0')*10 + (arr[1]-'0');

    /* Validate temperature input */
    if(strstr(msg, "TEMP") != 0 && val > 50)
    {
        /* Clear LCD */
        Write_CMD_LCD(0x01);

        /* Display error message */
        Write_str_LCD("Invalid Temp!");

        /* Move to second line */
        Write_CMD_LCD(0xC0);

        /* Display valid range */
        Write_str_LCD("Enter 0-50");

        /* Delay */
        delay_ms(1000);

        /* Retry input */
        goto again;
    }

    /* Validate humidity input */
    if(strstr(msg, "HUM") != 0 && val > 99)
    {
        /* Clear LCD */
        Write_CMD_LCD(0x01);

        /* Display error message */
        Write_str_LCD("Invalid Hum!");

        /* Move to second line */
        Write_CMD_LCD(0xC0);

        /* Display valid range */
        Write_str_LCD("Enter 0-99");

        /* Delay */
        delay_ms(1000);

        /* Retry input */
        goto again;
    }

    /* Return valid input */
    return val;
}

/* Function to read single digit value */
int Get1DigitValue(char *msg)
{
    /* Variable for key input */
    char key;

again:
    /* Clear LCD */
    Write_CMD_LCD(0x01);

    /* Move cursor to row 1 */
    Write_CMD_LCD(0x80);

    /* Display input message */
    Write_str_LCD(msg);

    /* Move cursor to row 4 */
    Write_CMD_LCD(0xD4);

    /* Wait for valid input */
    while(1)
    {
        /* Scan keypad */
        key = keyScan();

        /* Accept only numeric keys */
        if(key >= '0' && key <= '9')
        {
            /* Allow values only from 0 to 3 */
            if(key >= '0' && key <= '3')
            {
                /* Display entered key */
                Write_DAT_LCD(key);

                /* Delay */
                delay_ms(500);

                /* Return integer value */
                return (key - '0');
            }
            else
            {
                /* Clear LCD */
                Write_CMD_LCD(0x01);

                /* Display invalid message */
                Write_str_LCD("Invalid!");

                /* Move to second line */
                Write_CMD_LCD(0xC0);

                /* Show valid range */
                Write_str_LCD("Enter 0-3 only");

                /* Delay */
                delay_ms(1000);

                /* Retry input */
                goto again;
            }
        }

        /* Handle skip using * key */
        else if(key == '*')
        {
            /* Clear LCD */
            Write_CMD_LCD(0x01);

            /* Display skipped message */
            Write_str_LCD("Skipped");

            /* Delay */
            delay_ms(500);

            /* Return skip code */
            return -1;
        }
    }
}
