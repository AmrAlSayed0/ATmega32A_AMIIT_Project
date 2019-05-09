#include <avr/io.h>
#include <util/delay.h>
#include "bit_helpers.h"
#include "io_extras.h"
#include "FreeRTOS.h"
#include "task.h"
#include "semphr.h"
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
#include "RTC.h"
#include "MOTOR.h"
void App_init ( void );
void vTask1 ( void* vParameters );
int main ( void )
{
    App_init ();
    xTaskCreate ( vTask1 , "Task1" , configMINIMAL_STACK_SIZE , ( void* ) 0 , 1 , NULL_PTR );
    vTaskStartScheduler ();
    while ( 1 )
    {
    }
}
void App_init ( void )
{
    WTCHDG_disable ();
    DIO_init ();
    {
        UART_CNF_t uartCng = {
            57600 ,
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
    }
    I2C_masterInit ( 400000 );
    LED_init ();
    LCD_init ( INS_FUNCTION_8_BIT | INS_FUNCTION_2_LINES | INS_FUNCTION_5_7_DOTS , INS_ENTRY_MODE_DECREMENT | INS_ENTRY_MODE_NO_SHIFT , INS_DISPLAY_ON | INS_DISPLAY_CURSOR_OFF | INS_DISPLAY_CURSOR_BLINK_OFF );
    KEYPAD_init ();
    MOTOR_init ();
}
void vTask1 ( void* vParameters )
{
    TickType_t xLastWakeTime = xTaskGetTickCount ();
    ( void ) vParameters;
    uint16_t pressedKeys = KEY_NONE;
    MOTOR_setSpeed ( 0.5 );
    uint8_t i = 0;
    while ( 1 )
    {
        i = 0xFF;
        pressedKeys |= KEYPAD_getPressedKey ();
        if ( pressedKeys != KEY_NONE )
        {
            MOTOR_start ();
            while ( i-- > 0 )
            {
                UART_transmitChar ( '\b' );
            }
            UART_transmitString ( "Started" );
            UART_transmitChar ( '\r' );
        }
        else
        {
            MOTOR_stop ();
            while ( i-- > 0 )
            {
                UART_transmitChar ( '\b' );
            }
            UART_transmitString ( "Stopped" );
            UART_transmitChar ( '\r' );
        }
        pressedKeys = KEY_NONE;
        vTaskDelayUntil ( &xLastWakeTime , 1000 );
    }
}
