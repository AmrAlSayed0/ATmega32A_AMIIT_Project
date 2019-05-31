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
#include "APP_TASK.h"
#include "LCD_TASK.h"
#include "KEYPAD_TASK.h"
void App_init ( void );
int main ( void )
{
    App_init ();
    xTaskCreate ( vLCD_TASK , "LCD_TASK" , configMINIMAL_STACK_SIZE , ( void* ) 0 , 1 , NULL_PTR );
    xTaskCreate ( vKEYPAD_TASK , "KEYPAD_TASK" , configMINIMAL_STACK_SIZE , ( void* ) 0 , 1 , NULL_PTR );
    xTaskCreate ( vAPP_TASK , "APP_TASK" , configMINIMAL_STACK_SIZE , ( void* ) 0 , 2 , NULL_PTR );
    vTaskStartScheduler ();
    while ( 1 )
    {
        UART_transmitString ( "w" );
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
void vApplicationIdleHook ( void )
{
    //UART_transmitString ( "Idle!\r" );
}
