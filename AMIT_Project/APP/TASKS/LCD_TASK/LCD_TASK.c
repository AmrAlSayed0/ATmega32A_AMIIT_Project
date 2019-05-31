#include "UART.h"
#include "LCD.h"
#include "LCD_TASK.h"
QueueHandle_t xLCD_Queue = NULL_PTR;
void vLCD_TASK ( void* vParameters )
{
    ( void ) vParameters;
    xLCD_Queue = xQueueCreate ( 5 , sizeof ( char ) );
    char message;
    //TickType_t xLastWakeTime = xTaskGetTickCount ();
    while ( 1 )
    {
        //UART_transmitString ( "LCD Task Started!\r" );
        if ( xLCD_Queue != NULL_PTR )
        {
                UART_transmitString ( "LCD Queue Not Null!\r" );
                if ( xQueueReceive ( xLCD_Queue , &message , 0 ) == pdPASS )
                {
                    UART_transmitString ( "LCD Clearing!\r" );
                    UART_transmit ( message );
                    LCD_clear ();
                    LCD_writeChar ( message );
                }
        }
        //UART_transmitString ( "LCD Task Stopped!\r" );
        vTaskDelay ( 50 );
    }
    vTaskDelete ( NULL );
}
