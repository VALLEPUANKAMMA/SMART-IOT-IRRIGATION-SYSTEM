/* Function declaration to send command to LCD */
void Write_CMD_LCD(char);

/* Function declaration to send data (character) to LCD */
void Write_DAT_LCD(char);

/* Function declaration to write a single character to LCD */
void Write_LCD(char);

/* Function declaration to initialize LCD */
void LCD_Init(void);

/* Function declaration to write a string to LCD */
void Write_str_LCD(char *);

/* Function declaration to display signed integer on LCD */
/* signed int (2 bytes) range: -32768 to 32767 */
void Write_int_LCD(signed int);

/* Function declaration to display floating point number on LCD */
/* Second argument specifies number of digits after decimal point */
void Write_float_LCD(float f, char);
