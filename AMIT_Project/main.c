#include <avr/io.h>
#include <util/delay.h>
#include "io_extras.h"
#include "FreeRTOS.h"
#include "task.h"
#include "EEPROM.h"
#include "WTCHDG.h"
#include "DIO.h"
#include "TIMER.h"
#include "SPI.h"
#include "I2C.h"
#include "LCD.h"
#include "UART.h"
#include "KEYPAD.h"
#include "LED.h"
#include "EXT_EEPROM.h"
int main ( void )
{
    WTCHDG_disable ();
    DIO_init ();
    UART_CNF_t uartCng = {
        9600 ,
        UART_NORMAL_SPEED ,
        UART_PROC_MODE_SINGLE ,
        UART_TRANS_ASYNC ,
        UART_COM_ENABLED ,
        UART_COM_ENABLED ,
        UART_DATA_SIZE_8_BIT ,
        UART_PARITY_ODD ,
        UART_STP_SIZE_1_BIT ,
        UART_CLCK_POLARITY_NOT_CARE
    };
    UART_init ( &uartCng );
    I2C_masterInit ( 400000 );
    LED_init ();
    LCD_init ( INS_FUNCTION_8_BIT | INS_FUNCTION_2_LINES | INS_FUNCTION_5_7_DOTS , INS_ENTRY_MODE_DECREMENT | INS_ENTRY_MODE_NO_SHIFT , INS_DISPLAY_ON | INS_DISPLAY_CURSOR_OFF | INS_DISPLAY_CURSOR_BLINK_OFF );
    KEYPAD_init ();
    EXT_EEPROM_move ( 0 , 1000 , 1000 );
    while ( 1 )
    {
        uint16_t pressedKeys = KEYPAD_getPressedKey ();
        if ( ( pressedKeys & KEY_0 ) == KEY_0 )
        {
            UART_transmitString ( "0" );
        }
        if ( ( pressedKeys & KEY_1 ) == KEY_1 )
        {
            UART_transmitString ( "1" );
        }
        if ( ( pressedKeys & KEY_2 ) == KEY_2 )
        {
            UART_transmitString ( "2" );
        }
        if ( ( pressedKeys & KEY_3 ) == KEY_3 )
        {
            UART_transmitString ( "3" );
        }
        if ( ( pressedKeys & KEY_4 ) == KEY_4 )
        {
            UART_transmitString ( "4" );
        }
        if ( ( pressedKeys & KEY_5 ) == KEY_5 )
        {
            UART_transmitString ( "5" );
        }
        if ( ( pressedKeys & KEY_6 ) == KEY_6 )
        {
            UART_transmitString ( "6" );
        }
        if ( ( pressedKeys & KEY_7 ) == KEY_7 )
        {
            UART_transmitString ( "7" );
        }
        if ( ( pressedKeys & KEY_8 ) == KEY_8 )
        {
            UART_transmitString ( "8" );
        }
        if ( ( pressedKeys & KEY_9 ) == KEY_9 )
        {
            UART_transmitString ( "9" );
        }
        if ( ( pressedKeys & KEY_C ) == KEY_C )
        {
            UART_transmitString ( "C" );
        }
        if ( ( pressedKeys & KEY_EQ ) == KEY_EQ )
        {
            UART_transmitString ( "=" );
        }
        if ( ( pressedKeys & KEY_PLUS ) == KEY_PLUS )
        {
            UART_transmitString ( "+" );
        }
        if ( ( pressedKeys & KEY_NEG ) == KEY_NEG )
        {
            UART_transmitString ( "-" );
        }
        if ( ( pressedKeys & KEY_MULT ) == KEY_MULT )
        {
            UART_transmitString ( "x" );
        }
        if ( ( pressedKeys & KEY_DIV ) == KEY_DIV )
        {
            UART_transmitString ( "/" );
        }
        LCD_clearAndWriteString ( "ABC" );
        _delay_ms ( 50 );
    }
}

