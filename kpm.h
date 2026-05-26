/* Include user-defined typedef header file */
#include "typedef.h"

/* Function declaration to initialize keypad module */
void Initkpm(void);

/* Function declaration to scan keypad columns */
u32 ColScan(void);

/* Function declaration to check keypad rows */
u32 RowCheck(void);

/* Function declaration to check keypad columns */
u32 ColCheck(void);

/* Function declaration to scan and detect pressed key */
u32 keyScan(void);

/* Function declaration to read numeric input from keypad */
u32 ReadNum(void);

/* Function declaration to get a two-digit integer value from character array */
int Get2DigitValue(char *);

/* Function declaration to get a one-digit integer value from character array */
int Get1DigitValue(char *);
