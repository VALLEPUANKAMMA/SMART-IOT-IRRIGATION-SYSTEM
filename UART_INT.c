#include <LPC21xx.H>  
/* Include LPC21xx register definitions */

#include <string.h>   
/* Include string handling library */

#define UART_INT_ENABLE 1  
/* Enable UART interrupt functionality */


/* Function declaration for UART initialization */
void InitUART0(void);

/* Function declaration for UART transmit */
void UART0_Tx(char ch);

/* Function declaration for UART receive */
char UART0_Rx(void);


/* Buffer to store received UART data */
/* Dummy variable used to clear interrupt */
char buff[10], dummy;

/* i = buffer index */
/* ch = received character */
/* r_flag = receive flag */
unsigned char i=0, ch, r_flag;


/* UART0 Interrupt Service Routine */
void UART0_isr(void) __irq
{
    /* Check if receive interrupt occurred */
    if((U0IIR & 0x04))
    {
        /* Read received character and clear interrupt */
        ch = U0RBR;

        /* Check buffer limit before storing */
        if(i < 200)
        {
            /* Store character and increment index */
            buff[i++] = ch;
        }
    }
    else
    {
        /* Read interrupt register to clear transmit interrupt */
        dummy = U0IIR;
    }

    /* Notify interrupt controller that ISR is complete */
    VICVectAddr = 0;
}


/* UART0 Initialization Function */
void InitUART0(void)
{
    /* Configure P0.0 as TXD0 and P0.1 as RXD0 */
    PINSEL0 = 0x00000005;

    /* Configure UART:
       8-bit data
       No parity
       1 stop bit
       Enable DLAB */
    U0LCR = 0x83;

    /* Set baud rate for 9600 */
    U0DLL = 97;

    /* Disable DLAB after baud configuration */
    U0LCR = 0x03;

#if UART_INT_ENABLE > 0

    /* Select IRQ mode */
    VICIntSelect = 0x00000000;

    /* Assign UART ISR address */
    VICVectAddr0 = (unsigned)UART0_isr;

    /* Enable UART0 interrupt slot */
    VICVectCntl0 = 0x20 | 6;

    /* Enable UART0 interrupt in VIC */
    VICIntEnable = 1 << 6;

    /* Enable UART receive and transmit interrupts */
    U0IER = 0x03;

#endif
}


/* UART Character Transmit Function */
void UART0_Tx(char ch)
{
    /* Wait until transmit holding register is empty */
    while (!(U0LSR & 0x20));

    /* Load character into transmit register */
    U0THR = ch;
}


/* UART Character Receive Function */
char UART0_Rx(void)
{
    /* Wait until data is received */
    while (!(U0LSR & 0x01));

    /* Return received character */
    return (U0RBR);
}


/* UART String Transmit Function */
void UART0_Str(char *s)
{
    /* Loop until null character is found */
    while(*s)
    {
        /* Send each character */
        UART0_Tx(*s++);
    }
}


/* UART Integer Transmit Function */
void UART0_Int(unsigned int n)
{
    /* Array to store extracted digits */
    unsigned char a[10]={0};

    /* Local index variable */
    int i=0;

    /* Check if number is zero */
    if(n==0)
    {
        /* Send zero */
        UART0_Tx('0');

        /* Exit function */
        return;
    }
    else
    {
        /* Extract digits one by one */
        while(n>0)
        {
            /* Convert digit to ASCII and store */
            a[i++] = (n%10)+48;

            /* Remove last digit */
            n = n/10;
        }

        /* Adjust index to last valid digit */
        --i;

        /* Send digits in correct order */
        for(; i>=0; i--)
        {
            /* Transmit digit */
            UART0_Tx(a[i]);
        }
    }
}


/* UART Float Transmit Function */
void UART0_Float(float f)
{
    /* Variable for integer part */
    int x;

    /* Variable for decimal part */
    float temp;

    /* Extract integer part */
    x = f;

    /* Send integer part */
    UART0_Int(x);

    /* Send decimal point */
    UART0_Tx('.');

    /* Extract first two decimal digits */
    temp = (f-x)*100;

    /* Convert decimal part to integer */
    x = temp;

    /* Send decimal part */
    UART0_Int(x);
}


/* Delay Function */
void DelayS(unsigned int dly)
{
    /* Loop variable */
    unsigned int i;

    /* Outer loop for delay count */
    for(; dly>0; dly--)
    {
        /* Inner loop for actual delay */
        for(i=1200000; i>0; i--);
    }
}
