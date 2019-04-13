#include <avr/io.h>
#include <util/delay.h>
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
int main ( void )
{
    WTCHDG_disable ();
    //EEPROM_fill ( 0 , 1024 , 0xFF );
    DIO_init ();
    UART_CNF_t uartCng = {
        .baudRate = 9600 , .transmissionSpeedMode = NORMAL_SPEED , .multiProcessorMode = SINGLE , .transmissionMode = ASYNC , .transmitterState = COM_ENABLED , .receiverState = COM_ENABLED , .dataFrameSize = BIT_8_SIZE , .parity = ODD_PARITY , .stopFrameSize = BIT_1_SIZE , .clckPolarity = RISING_FALLING
    };
    UART_init ( &uartCng );
    SPI_CFG_t spiCng = { .dataOrder = DATA_ORDER_LSB , .freq=SPI_FREQ_128 , .mode=SPI_MODE_0 };
    SPI_masterInit ( &spiCng );
    LCD_init ( INS_FUNCTION_SET_4_BIT | INS_FUNCTION_SET_2_LINES | INS_FUNCTION_SET_5_7_DOTS , INS_ENTRY_MODE_SET_DECREMENT | INS_ENTRY_MODE_SET_NO_SHIFT , INS_DISPLAY_ON | INS_DISPLAY_CURSOR_OFF | INS_DISPLAY_CURSOR_BLINK_OFF );
    while ( 1 )
    {
        UART_transmitString ( "ABC" );
        SPI_masterTransmit ( 1 );
        LCD_clearAndWriteString ( "ABC" );
        _delay_ms ( 1000 );
    }
}

