/* LCD_defines.h */

/* Define starting pin for LCD data lines */
#define LCD_DATA 8

/* Define Register Select (RS) pin */
#define RS 16

/* Define Read/Write (RW) pin */
#define RW 17

/* Define Enable (EN) pin */
#define EN 18

/* Command to clear LCD display */
#define CLEAR_LCD 0X01

/* Command to return cursor to home position */
#define RET_CUR_HOME 0x02

/* Command to turn display OFF */
#define DISP_OFF 0x08

/* Command to turn display ON */
#define DISP_ON 0x0C

/* Command to turn display ON with cursor ON */
#define DISP_ON_CUR_ON 0x0E

/* Command to turn display ON with blinking cursor */
#define DISP_ON_CUR_BLINK 0x0F

/* Command to set LCD in 8-bit mode with 1 line */
#define MODE_8BIT_1LINE 0X30

/* Command to set LCD in 8-bit mode with 2 lines */
#define MODE_8BIT_2LINE 0X38

/* Command to set LCD in 4-bit mode with 1 line */
#define MODE_4BIT_1LINE 0X20

/* Command to set LCD in 4-bit mode with 2 lines */
#define MODE_4BIT_2LINE 0X28

/* Command to move cursor to line 1, position 0 */
#define GOTO_LINE1_POS0 0X80

/* Command to move cursor to line 2, position 0 */
#define GOTO_LINE2_POS0 0XC0

/* Command to move cursor to line 3, position 0 */
#define GOTO_LINE3_POS0 0X94

/* Command to move cursor to line 4, position 0 */
#define GOTO_LINE4_POS0 0XD4

/* Command to shift cursor to the right */
#define SHIFT_CUR_RIGHT 0X06

/* Command to shift display to the left */
#define SHIFT_DISP_LEFT 0x10

/* Command to shift display to the right */
#define SHIFT_DISP_RIGHT 0X14

/* Command to access CGRAM for custom character creation */
#define GOTO_CGRAM 0x40
