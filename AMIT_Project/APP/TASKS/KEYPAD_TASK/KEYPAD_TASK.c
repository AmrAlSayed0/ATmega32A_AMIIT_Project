#include "UART.h"
#include "KEYPAD.h"
#include "KEYPAD_TASK.h"
QueueHandle_t xKEYPAD_Queue = NULL_PTR;
void vKEYPAD_TASK ( void* vParameters )
{
    ( void ) vParameters;
    xKEYPAD_Queue = xQueueCreate ( 5 , sizeof ( uint16_t ) );
    uint16_t firstRead;
    uint16_t secondRead;
    uint16_t combinedReading;
    //TickType_t xLastWakeTime = xTaskGetTickCount ();
    while ( 1 )
    {
        //UART_transmitString ( "Keypad Task Started!\r" );
        firstRead = KEYPAD_getPressedKeys ();
        vTaskDelay ( 50 );
        secondRead = KEYPAD_getPressedKeys ();
        combinedReading = firstRead & secondRead;
        if ( xKEYPAD_Queue != NULL_PTR )
        {
            if ( combinedReading != KEY_NONE )
            {
                //UART_transmitString ( "Keypad Task Keypad Queue Not Null!\r" );
                xQueueSend ( xKEYPAD_Queue , &combinedReading , 0 );
                combinedReading = KEY_NONE;
            }
        }
        //UART_transmitString ( "Keypad Task Stopped!\r" );
        vTaskDelay ( 1000 );
    }
}
