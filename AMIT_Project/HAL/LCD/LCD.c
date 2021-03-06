#include <util/delay.h>
#include "bit_helpers.h"
#include "time_helpers.h"
#include "FreeRTOS.h"
#include "task.h"
#include "semphr.h"
#include "DIO.h"
#include "LCD_private.h"
#include "LCD_config.h"
#include "LCD.h"
SemaphoreHandle_t xLCD_mutex = NULL;
#define RW_READ                 PIN_STATE_HIGH
#define RW_WRITE                PIN_STATE_LOW
#define RS_INS                  PIN_STATE_LOW
#define RS_DATA                 PIN_STATE_HIGH
#define INIT_DELAY_FIRST_IN_MS  15
#define INIT_DELAY_SECOND_IN_US 4100
#define INIT_DELAY_THIRD_IN_US  100
#define INIT_DELAY_FINAL_IN_MS  5
#define ENABLE_DELAY_IN_US      1
#define COMMAND_DELAY_IN_MS     5
#define DATA_DELAY_IN_MS        5
#define ASCII_NUMERIC_OFFSET    48
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
void LCD_init ( uint8_t ui8FunctionSetOptions , uint8_t ui8EntryModeSetOptions , uint8_t ui8DisplayOptions )
{
    DIO_setDirection ( LCD_E_PORT , LCD_E_PIN , DIRECTION_OUTPUT );
    DIO_setDirection ( LCD_RW_PORT , LCD_RW_PIN , DIRECTION_OUTPUT );
    DIO_setDirection ( LCD_RS_PORT , LCD_RS_PIN , DIRECTION_OUTPUT );
    DIO_setDirection ( LCD_D0_PORT , LCD_D0_PIN , DIRECTION_OUTPUT );
    DIO_setDirection ( LCD_D1_PORT , LCD_D1_PIN , DIRECTION_OUTPUT );
    DIO_setDirection ( LCD_D2_PORT , LCD_D2_PIN , DIRECTION_OUTPUT );
    DIO_setDirection ( LCD_D3_PORT , LCD_D3_PIN , DIRECTION_OUTPUT );
    DIO_setDirection ( LCD_D4_PORT , LCD_D4_PIN , DIRECTION_OUTPUT );
    DIO_setDirection ( LCD_D5_PORT , LCD_D5_PIN , DIRECTION_OUTPUT );
    DIO_setDirection ( LCD_D6_PORT , LCD_D6_PIN , DIRECTION_OUTPUT );
    DIO_setDirection ( LCD_D7_PORT , LCD_D7_PIN , DIRECTION_OUTPUT );
    DIO_write ( LCD_E_PORT , LCD_E_PIN , PIN_STATE_LOW );
    DIO_write ( LCD_RW_PORT , LCD_RW_PIN , PIN_STATE_LOW );
    DIO_write ( LCD_RS_PORT , LCD_RS_PIN , PIN_STATE_LOW );
    DIO_write ( LCD_D0_PORT , LCD_D0_PIN , PIN_STATE_LOW );
    DIO_write ( LCD_D1_PORT , LCD_D1_PIN , PIN_STATE_LOW );
    DIO_write ( LCD_D2_PORT , LCD_D2_PIN , PIN_STATE_LOW );
    DIO_write ( LCD_D3_PORT , LCD_D3_PIN , PIN_STATE_LOW );
    DIO_write ( LCD_D4_PORT , LCD_D4_PIN , PIN_STATE_LOW );
    DIO_write ( LCD_D5_PORT , LCD_D5_PIN , PIN_STATE_LOW );
    DIO_write ( LCD_D6_PORT , LCD_D6_PIN , PIN_STATE_LOW );
    DIO_write ( LCD_D7_PORT , LCD_D7_PIN , PIN_STATE_LOW );
    // Check if using 8-bit data or 4-bit data
    data8Bit = ( bool ) ( ( ui8FunctionSetOptions & INS_FUNCTION_8_BIT ) == INS_FUNCTION_8_BIT );
    // Some mysterious magic
    _delay_ms ( INIT_DELAY_FIRST_IN_MS );
    LCD_writeCommand ( INS_FUNCTION_BASE | INS_FUNCTION_8_BIT );
    _delay_us ( INIT_DELAY_SECOND_IN_US );
    LCD_writeCommand ( INS_FUNCTION_BASE | INS_FUNCTION_8_BIT );
    _delay_us ( INIT_DELAY_THIRD_IN_US );
    LCD_writeCommand ( INS_FUNCTION_BASE | INS_FUNCTION_8_BIT );
    _delay_ms ( INIT_DELAY_FINAL_IN_MS );
    //waitBusy ();
    if ( !data8Bit )
    {
        LCD_writeCommand ( INS_FUNCTION_BASE | INS_FUNCTION_4_BIT );
        _delay_ms ( INIT_DELAY_FINAL_IN_MS );
        //waitBusy ();
    }

    // Initial setup
    LCD_writeCommand ( INS_FUNCTION_BASE | ui8FunctionSetOptions );
    LCD_writeCommand ( INS_ENTRY_MODE_BASE | ui8EntryModeSetOptions );
    LCD_writeCommand ( INS_DISPLAY_BASE | ui8DisplayOptions );
    LCD_clear ();
    isInitDone = true;
    xLCD_mutex = xSemaphoreCreateBinary ();
}
#pragma GCC diagnostic ignored "-Wunused-function"
static void waitBusy ( void )
{
    DIO_CNF_t d7Config = {
        LCD_D7_PORT ,
        LCD_D7_PIN ,
        DIRECTION_OUTPUT ,
        PIN_STATE_NOT_CARE ,
        RESISTOR_NOT_CARE
    };
    DIO_getConfig ( &d7Config );
    DIO_CNF_t rwConfig = {
        LCD_RW_PORT ,
        LCD_RW_PIN ,
        DIRECTION_OUTPUT ,
        PIN_STATE_NOT_CARE ,
        RESISTOR_NOT_CARE
    };
    DIO_getConfig ( &rwConfig );
    DIO_CNF_t rsConfig = {
        LCD_RS_PORT ,
        LCD_RS_PIN ,
        DIRECTION_OUTPUT ,
        PIN_STATE_NOT_CARE ,
        RESISTOR_NOT_CARE
    };
    DIO_getConfig ( &rsConfig );
    DIO_setDirection ( LCD_D7_PORT , LCD_D7_PIN , DIRECTION_INPUT );
    DIO_setResistor ( LCD_D7_PORT , LCD_D7_PIN , RESISTOR_OPEN );
    DIO_write ( LCD_RW_PORT , LCD_RW_PIN , RW_READ );
    DIO_write ( LCD_RS_PORT , LCD_RS_PIN , RS_INS );
    PIN_STATE_t d7State = PIN_STATE_NOT_CARE;
    while ( DIO_read ( LCD_D7_PORT , LCD_D7_PIN , &d7State ) , d7State == PIN_STATE_HIGH )
    {
    }
    DIO_setConfig ( &d7Config );
    DIO_setConfig ( &rwConfig );
    DIO_setConfig ( &rsConfig );
}
/*
 * Latch data by toggling the Enable pin
 */
static void enable ( void )
{
    DIO_write ( LCD_E_PORT , LCD_E_PIN , PIN_STATE_HIGH );
#if ( USE_FREE_RTOS_TASK_DELAY == 1 )
    if ( isInitDone )
    {
        vTaskDelay ( calcTicksFromTimeMs ( ( ( double ) ENABLE_DELAY_IN_US ) / ( ( double ) 1000 ) ) );
    }
    else
    {
        _delay_us ( ENABLE_DELAY_IN_US );
    }        
#elif
    _delay_us ( ENABLE_DELAY_IN_US );
#endif
    DIO_write ( LCD_E_PORT , LCD_E_PIN , PIN_STATE_LOW );
#if ( USE_FREE_RTOS_TASK_DELAY == 1 )
    if ( isInitDone )
    {
        vTaskDelay ( calcTicksFromTimeMs ( ( ( double ) ENABLE_DELAY_IN_US ) / ( ( double ) 1000 ) ) );
    }
    else
    {
        _delay_us ( ENABLE_DELAY_IN_US );
    }
#elif
    _delay_us ( ENABLE_DELAY_IN_US );
#endif
}
/*
 * Write data to Data pins. Written data might be 4-bit or 8-bit
 * according to data8Bit variable
 */
void LCD_writeData ( uint8_t ui8Data )
{
    uint8_t i;
    if ( data8Bit )
    {
        for ( i = ( uint8_t ) 0; i < ( uint8_t ) 8; i++ )
        {
            switch ( i )
            {
                case 0 :
                    DIO_write ( LCD_D0_PORT , LCD_D0_PIN , READ_BIT ( ui8Data , 0 ) == 1 ?
                                                           PIN_STATE_HIGH :
                                                           PIN_STATE_LOW );
                    break;
                case 1 :
                    DIO_write ( LCD_D1_PORT , LCD_D1_PIN , READ_BIT ( ui8Data , 1 ) == 1 ?
                                                           PIN_STATE_HIGH :
                                                           PIN_STATE_LOW );
                    break;
                case 2 :
                    DIO_write ( LCD_D2_PORT , LCD_D2_PIN , READ_BIT ( ui8Data , 2 ) == 1 ?
                                                           PIN_STATE_HIGH :
                                                           PIN_STATE_LOW );
                    break;
                case 3 :
                    DIO_write ( LCD_D3_PORT , LCD_D3_PIN , READ_BIT ( ui8Data , 3 ) == 1 ?
                                                           PIN_STATE_HIGH :
                                                           PIN_STATE_LOW );
                    break;
                case 4 :
                    DIO_write ( LCD_D4_PORT , LCD_D4_PIN , READ_BIT ( ui8Data , 4 ) == 1 ?
                                                           PIN_STATE_HIGH :
                                                           PIN_STATE_LOW );
                    break;
                case 5 :
                    DIO_write ( LCD_D5_PORT , LCD_D5_PIN , READ_BIT ( ui8Data , 5 ) == 1 ?
                                                           PIN_STATE_HIGH :
                                                           PIN_STATE_LOW );
                    break;
                case 6 :
                    DIO_write ( LCD_D6_PORT , LCD_D6_PIN , READ_BIT ( ui8Data , 6 ) == 1 ?
                                                           PIN_STATE_HIGH :
                                                           PIN_STATE_LOW );
                    break;
                case 7 :
                    DIO_write ( LCD_D7_PORT , LCD_D7_PIN , READ_BIT ( ui8Data , 7 ) == 1 ?
                                                           PIN_STATE_HIGH :
                                                           PIN_STATE_LOW );
                    break;
                default:
                    break;
            }
        }
        enable ();
    }
    else
    {
        for ( i = ( uint8_t ) 0; i < ( uint8_t ) 4; i++ )
        {
            switch ( i )
            {
                case 0 :
                    DIO_write ( LCD_D4_PORT , LCD_D4_PIN , READ_BIT ( ui8Data , 4 ) == 1 ?
                                                           PIN_STATE_HIGH :
                                                           PIN_STATE_LOW );
                    break;
                case 1 :
                    DIO_write ( LCD_D5_PORT , LCD_D5_PIN , READ_BIT ( ui8Data , 5 ) == 1 ?
                                                           PIN_STATE_HIGH :
                                                           PIN_STATE_LOW );
                    break;
                case 2 :
                    DIO_write ( LCD_D6_PORT , LCD_D6_PIN , READ_BIT ( ui8Data , 6 ) == 1 ?
                                                           PIN_STATE_HIGH :
                                                           PIN_STATE_LOW );
                    break;
                case 3 :
                    DIO_write ( LCD_D7_PORT , LCD_D7_PIN , READ_BIT ( ui8Data , 7 ) == 1 ?
                                                           PIN_STATE_HIGH :
                                                           PIN_STATE_LOW );
                    break;
                default:
                    break;
            }
        }
        enable ();
        for ( i = ( uint8_t ) 0; i < ( uint8_t ) 4; i++ )
        {
            switch ( i )
            {
                case 0 :
                    DIO_write ( LCD_D4_PORT , LCD_D4_PIN , READ_BIT ( ui8Data , 0 ) == 1 ?
                                                           PIN_STATE_HIGH :
                                                           PIN_STATE_LOW );
                    break;
                case 1 :
                    DIO_write ( LCD_D5_PORT , LCD_D5_PIN , READ_BIT ( ui8Data , 1 ) == 1 ?
                                                           PIN_STATE_HIGH :
                                                           PIN_STATE_LOW );
                    break;
                case 2 :
                    DIO_write ( LCD_D6_PORT , LCD_D6_PIN , READ_BIT ( ui8Data , 2 ) == 1 ?
                                                           PIN_STATE_HIGH :
                                                           PIN_STATE_LOW );
                    break;
                case 3 :
                    DIO_write ( LCD_D7_PORT , LCD_D7_PIN , READ_BIT ( ui8Data , 3 ) == 1 ?
                                                           PIN_STATE_HIGH :
                                                           PIN_STATE_LOW );
                    break;
                default:
                    break;
            }
        }
        enable ();
    }
}
/*
 * Send command to the LCD
 */
void LCD_writeCommand ( uint8_t ui8Com )
{
    xSemaphoreTake ( xLCD_mutex , 0 );
    DIO_write ( LCD_E_PORT , LCD_E_PIN , PIN_STATE_LOW );
    DIO_write ( LCD_RS_PORT , LCD_RS_PIN , RS_INS );
    LCD_writeData ( ui8Com );
#if ( USE_FREE_RTOS_TASK_DELAY == 1 )
    if ( isInitDone )
    {
        vTaskDelay ( calcTicksFromTimeMs ( COMMAND_DELAY_IN_MS ) );
    }
    else
    {
        _delay_ms ( COMMAND_DELAY_IN_MS );
    }
#elif
    _delay_ms ( COMMAND_DELAY_IN_MS );
#endif
    xSemaphoreGive ( xLCD_mutex );
}
/*
 * Write a char to the LCD at the cursor
 */
void LCD_writeChar ( char cChar )
{
    xSemaphoreTake ( xLCD_mutex , 0 );
    DIO_write ( LCD_E_PORT , LCD_E_PIN , PIN_STATE_LOW );
    DIO_write ( LCD_RS_PORT , LCD_RS_PIN , RS_DATA );
    LCD_writeData ( cChar );
#if ( USE_FREE_RTOS_TASK_DELAY == 1 )
    if ( isInitDone )
    {
        vTaskDelay ( calcTicksFromTimeMs ( DATA_DELAY_IN_MS ) );
    }
    else
    {
        _delay_ms ( DATA_DELAY_IN_MS );
    }
#elif
    _delay_ms ( DATA_DELAY_IN_MS );
#endif
    xSemaphoreGive ( xLCD_mutex );
}
/*
 * Write a string to the LCD
 */
void LCD_writeString ( char* s )
{
    while ( *s != '\0' )
    {
        LCD_writeChar ( *s );
        s++;
    }
}
void LCD_writeNumber ( uint16_t data )
{
    intToString ( data );
    LCD_writeString ( numericString );
}
static void intToString ( uint16_t number )
{
    if ( number < 10 )
    {
        numericString[ 0 ] = number % 10 + ASCII_NUMERIC_OFFSET;
        numericString[ 1 ] = '\0';
    }
    else if ( number < 100 )
    {
        numericString[ 0 ] = number / 10 + ASCII_NUMERIC_OFFSET;
        numericString[ 1 ] = number % 10 + ASCII_NUMERIC_OFFSET;
        numericString[ 2 ] = '\0';
    }
    else if ( number < 1000 )
    {
        numericString[ 0 ] = number / 100 + ASCII_NUMERIC_OFFSET;
        number = number % 100;
        numericString[ 1 ] = number / 10 + ASCII_NUMERIC_OFFSET;
        numericString[ 2 ] = number % 10 + ASCII_NUMERIC_OFFSET;
        numericString[ 3 ] = '\0';
    }
    else if ( number < 10000 )
    {
        numericString[ 0 ] = number / 1000 + ASCII_NUMERIC_OFFSET;
        number = number % 1000;
        numericString[ 1 ] = number / 100 + ASCII_NUMERIC_OFFSET;
        number = number % 100;
        numericString[ 2 ] = number / 10 + ASCII_NUMERIC_OFFSET;
        numericString[ 3 ] = number % 10 + ASCII_NUMERIC_OFFSET;
        numericString[ 4 ] = '\0';
    }
    else
    {
        numericString[ 0 ] = number / 10000 + ASCII_NUMERIC_OFFSET;
        number = number % 10000;
        numericString[ 1 ] = number / 1000 + ASCII_NUMERIC_OFFSET;
        number = number % 1000;
        numericString[ 2 ] = number / 100 + ASCII_NUMERIC_OFFSET;
        number = number % 100;
        numericString[ 3 ] = number / 10 + ASCII_NUMERIC_OFFSET;
        numericString[ 4 ] = number % 10 + ASCII_NUMERIC_OFFSET;
        numericString[ 5 ] = '\0';
    }
}
/*
 * Clear display
 */
void LCD_clear ( void )
{
    LCD_writeCommand ( INS_CLEAR_DISPLAY );
}
/*
 * Clear display and write a string
 */
void LCD_clearAndWriteString ( char* s )
{
    LCD_clear ();
    LCD_writeString ( s );
}
/*
 * Set cursor at the specified coordinate in which x is the column and y is the row
 */
void LCD_goToXY ( uint8_t ui8X , uint8_t ui8Y )
{
    uint8_t ui8Address;
    // Specify the address
    if ( ui8Y == 0 )
    {
        ui8Address = 0x00 + ui8X;
    }
    else
    {
        ui8Address = 0x40 + ui8X;
    }
    // Set the bit for cursor moving command
    ui8Address |= 0x80;
    LCD_writeCommand ( ui8Address );
}
