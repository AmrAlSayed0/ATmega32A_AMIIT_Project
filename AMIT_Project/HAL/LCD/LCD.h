#ifndef AMIT_PROJECT_LCD_H_
#define AMIT_PROJECT_LCD_H_
#include "std_types.h"
//*****************************************************************************
//
// The following are defines for the commands that can be given to the LCD
// screen.
//
//*****************************************************************************
#define INS_CLEAR_DISPLAY               0x01
#define INS_RETURN_HOME                 0x02
#define INS_FUNCTION_BASE               0x20
#define INS_FUNCTION_4_BIT              0x00 // 4-bit display by default
#define INS_FUNCTION_8_BIT              0x10 // 4-bit display by default
#define INS_FUNCTION_1_LINES            0x00 // 1 line by default
#define INS_FUNCTION_2_LINES            0x08 // 1 line by default
#define INS_FUNCTION_5_7_DOTS           0x00 // 5x7 dots by default
#define INS_FUNCTION_5_10_DOTS          0x04 // 5x7 dots by default
#define INS_ENTRY_MODE_BASE             0x04
#define INS_ENTRY_MODE_DECREMENT        0x00 // Decrement cursor position by default
#define INS_ENTRY_MODE_INCREMENT        0x02 // Decrement cursor position by default
#define INS_ENTRY_MODE_NO_SHIFT         0x00 // No display shift by default
#define INS_ENTRY_MODE_SHIFT            0x01 // No display shift by default
#define INS_DISPLAY_BASE                0x08
#define INS_DISPLAY_OFF                 0x00
#define INS_DISPLAY_ON                  0x04
#define INS_DISPLAY_CURSOR_OFF          0x00
#define INS_DISPLAY_CURSOR_ON           0x02
#define INS_DISPLAY_CURSOR_BLINK_OFF    0x00
#define INS_DISPLAY_CURSOR_BLINK_ON     0x01
#define INS_SHIFT_BASE                  0x10
#define INS_SHIFT_CURSOR                0x00 // cursor move by default
#define INS_SHIFT_DISPLAY               0x08 // cursor move by default
#define INS_SHIFT_LEFT                  0x00 // shift to the left by default
#define INS_SHIFT_RIGHT                 0x04 // shift to the left by default
#define CGRAM_ADDR( addr )              ( ( ( uint8_t ) ( 0x01 << 6 ) ) | addr )
#define DDRAM_ADDR( addr )              ( ( ( uint8_t ) ( 0x01 << 7 ) ) | addr )
/*
 * LCD initialization function
 * Things to consider when initialize a characters LCD:
 *  _Function set:
 * 		+ Interface data: 4-bit (0) or 8-bit (1)
 * 		+ Number of line: 1 line (0) or 2 lines (1)
 * 		+ Character font: 5x7 dots (0) or 5x10 dots (1)
 *  _Display on/off control:
 *  	+ Display: off (0) or on (1)
 *  	+ Cursor: off (0) or on (1)
 *  	+ Cursor blink: off (0) or on (1)
 *  _Entry mode set:
 *  	+ Cursor move direction: decrement (0) or increment (1)
 *  	+ Accompanies display shift: off (0) or on (1)
 */

void LCD_init ( uint8_t functionSetOptions , uint8_t entryModeSetOptions , uint8_t displayOptions );
/*
 * Write data to Data pins. Written data might be 4-bit or 8-bit
 * according to data8Bit variable
 */
void LCD_writeData ( uint8_t data );
/*
 * Send command to the LCD
 */
void LCD_writeCommand ( uint8_t com );
/*
 * Write a char to the LCD at the current string
 */
void LCD_writeChar ( char ch );
/*
 * Write a string to the LCD
 */
void LCD_writeString ( char* s );
/*
 * Write a number to the LCD
 */
void LCD_writeNumber ( uint16_t data );
/*
 * Clear the display
 */
void LCD_clear ( void );
/*
 * Clear the display then write the string
 */
void LCD_clearAndWriteString ( char* s );
/*
 * Set cursor at the specified coordinate in which x is the column and y is the row
 */
void LCD_goToXY ( uint8_t x , uint8_t y );
#endif
