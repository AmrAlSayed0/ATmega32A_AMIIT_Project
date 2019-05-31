#include "UART.h"
#include "LCD_TASK.h"
#include "KEYPAD_TASK.h"
#include "KEYPAD.h"
#include "APP_TASK.h"
void vAPP_TASK ( void* vParameters )
{
    ( void ) vParameters;
    uint16_t keysPressed;
    //TickType_t xLastWakeTime = xTaskGetTickCount ();
    while ( 1 )
    {
        //UART_transmitString ( "App Task Started!\r" );
        if ( xKEYPAD_Queue != NULL_PTR )
        {
            //UART_transmitString ( "App Task Keypad Queue Not Null!\r" );
            if ( xQueueReceive ( xKEYPAD_Queue , &keysPressed , 0 ) == pdPASS )
            {
                //UART_transmitString ( "App Task Keypad Key Received!" );
                if ( xLCD_Queue != NULL_PTR )
                {
                    char charToSend = ( char ) 0;
                    switch ( keysPressed )
                    {
                        case KEY_NONE :
                            break;
                        case KEY_0    :
                            charToSend = '0';
                            break;
                        case KEY_1    :
                            charToSend = '1';
                            break;
                        case KEY_2    :
                            charToSend = '2';
                            break;
                        case KEY_3    :
                            charToSend = '3';
                            break;
                        case KEY_4    :
                            charToSend = '4';
                            break;
                        case KEY_5    :
                            charToSend = '5';
                            break;
                        case KEY_6    :
                            charToSend = '6';
                            break;
                        case KEY_7    :
                            charToSend = '7';
                            break;
                        case KEY_8    :
                            charToSend = '8';
                            break;
                        case KEY_9    :
                            charToSend = '9';
                        case KEY_C    :
                            charToSend = 'C';
                            break;
                        case KEY_EQ   :
                            charToSend = '=';
                            break;
                        case KEY_PLUS :
                            charToSend = '+';
                            break;
                        case KEY_NEG  :
                            charToSend = '-';
                            break;
                        case KEY_MULT :
                            charToSend = 'x';
                            break;
                        case KEY_DIV  :
                            charToSend = '/';
                            break;
                    }
                    //UART_transmitString ( "App Task LCD Queue Not Null!" );
                    xQueueSend ( xLCD_Queue , &charToSend , 0 );
                }
            }
        }
        //UART_transmitString ( "App Task Stopped!\r" );
        vTaskDelay ( 10 );
    }
}
