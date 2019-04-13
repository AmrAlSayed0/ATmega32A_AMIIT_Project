#include <avr/io.h>
#include <math.h>
#include "BitHelpers.h"
#include "DIO.h"
#include "UART_private.h"
#include "UART_config.h"
#include "UART.h"
#define MAX_UBBR_VALUE                          ( ( uint16_t ) 0x7FF )
#define BIT_9_SIZE_VALUE                        ( ( uint8_t ) 0x7 )
#define UCSZ_VALUE                              ( ( READ_BIT ( UCSRB , UCSZ2 ) << 2 ) | ( READ_BIT ( UCSRC , UCSZ1 ) << 1 ) | ( READ_BIT ( UCSRC , UCSZ0 ) << 0 ) )
#define TX_PORT                                 PORT_D
#define TX_PIN                                  PIN_0
#define RX_PORT                                 PORT_C
#define RX_PIN                                  PIN_7
static UART_STD_ERR_t UART_UBBR_calc ( uint32_t baudRate , UART_TRANS_MODE_t transmissionMode , UART_TRANS_SPEED_t transmissionSpeed , uint16_t* ubbrValue )
{
    UART_STD_ERR_t ubbrResult = UART_OK;
    if ( baudRate != ( uint32_t ) 0 )
    {
        switch ( transmissionMode )
        {
            case ASYNC:
                switch ( transmissionSpeed )
                {
                    case NORMAL_SPEED:
                        *ubbrValue = ( uint16_t ) round ( UBBR_CALC ( baudRate , 16 ) );
                        break;
                    case DOUBLE_SPEED:
                        *ubbrValue = ( uint16_t ) round ( UBBR_CALC ( baudRate , 8 ) );
                        break;
                    default:
                        ubbrResult = UART_ERR_TRANS_SPEED;
                }
                break;
            case SYNC:
                *ubbrValue = ( uint16_t ) round ( UBBR_CALC ( baudRate , 2 ) );
                break;
            default:
                ubbrResult = UART_ERR_TRANS_MODE;
        }
        if ( ubbrResult == UART_OK && *ubbrValue > MAX_UBBR_VALUE )
        {
            ubbrResult = UART_ERR_UBBR;
        }
    }
    else
    {
        ubbrResult = UART_ERR_BAUD_RATE;
    }
    return ubbrResult;
}
UART_STD_ERR_t UART_init ( UART_CNF_t* uartCnfg )
{
    UART_STD_ERR_t initResult = UART_OK;
    uint16_t ubbrValue = 0;
    UART_STD_ERR_t ubbrResult = UART_UBBR_calc ( uartCnfg->baudRate , uartCnfg->transmissionMode , uartCnfg->transmissionSpeedMode , &ubbrValue );
    if ( ubbrResult == UART_OK )
    {
        UBRRH = ( uint8_t ) ( ubbrValue >> 8 );
        UBRRL = ( uint8_t ) ubbrValue;
        uint8_t ucsraValue = ( uint8_t ) 0;
        uint8_t ucsrbValue = ( uint8_t ) 0;
        uint8_t ucsrcValue = ( uint8_t ) 0;
        switch ( uartCnfg->transmissionMode )
        {
            case ASYNC:
                CLEAR_BIT ( ucsrcValue , UMSEL );
                switch ( uartCnfg->transmissionSpeedMode )
                {
                    case NORMAL_SPEED:
                        CLEAR_BIT ( ucsraValue , U2X );
                        break;
                    case DOUBLE_SPEED:
                        SET_BIT ( ucsraValue , U2X );
                        break;
                    case NC_SPEED:
                        break;
                    default:
                        initResult = UART_ERR_TRANS_SPEED;
                }
                break;
            case SYNC:
                CLEAR_BIT ( ucsraValue , U2X );
                SET_BIT ( ucsrcValue , UMSEL );
                switch ( uartCnfg->clckPolarity )
                {
                    case RISING_FALLING:
                        CLEAR_BIT ( ucsrcValue , UCPOL );
                        break;
                    case FALLING_RISING:
                        SET_BIT ( ucsrcValue , UCPOL );
                        break;
                    case NC_POLARITY:
                        break;
                    default:
                        initResult = UART_ERR_POLARITY;
                }
                break;
            default:
                initResult = UART_ERR_TRANS_MODE;
        }
        if ( initResult == UART_OK )
        {
            switch ( uartCnfg->transmitterState )
            {
                case COM_ENABLED:
                    SET_BIT ( ucsrbValue , TXEN );
                    break;
                case COM_DISABLED:
                    CLEAR_BIT ( ucsrbValue , TXEN );
                    break;
                default:
                    initResult = UART_ERR_TRANS;
            }
            if ( initResult == UART_OK )
            {
                switch ( uartCnfg->receiverState )
                {
                    case COM_ENABLED:
                        SET_BIT ( ucsrbValue , RXEN );
                        break;
                    case COM_DISABLED:
                        CLEAR_BIT ( ucsrbValue , RXEN );
                        break;
                    default:
                        initResult = UART_ERR_RECV;
                }
                if ( initResult == UART_OK )
                {
                    switch ( uartCnfg->dataFrameSize )
                    {
                        case BIT_5_SIZE:
                            REPLACE_BITS ( ucsrcValue , ( 0 << UCSZ1 ) | ( 0 << UCSZ0 ) , BIT_MASK ( UCSZ1 ) | BIT_MASK ( UCSZ0 ) );
                            CLEAR_BIT ( ucsrbValue , UCSZ2 );
                            //CLEAR_BIT ( ucsrcValue , UCSZ1 );
                            //CLEAR_BIT ( ucsrcValue , UCSZ0 );
                            break;
                        case BIT_6_SIZE:
                            REPLACE_BITS ( ucsrcValue , ( 0 << UCSZ1 ) | ( 1 << UCSZ0 ) , BIT_MASK ( UCSZ1 ) | BIT_MASK ( UCSZ0 ) );
                            CLEAR_BIT ( ucsrbValue , UCSZ2 );
                            //CLEAR_BIT ( ucsrcValue , UCSZ1 );
                            //SET_BIT ( ucsrcValue , UCSZ0 );
                            break;
                        case BIT_7_SIZE:
                            REPLACE_BITS ( ucsrcValue , ( 1 << UCSZ1 ) | ( 0 << UCSZ0 ) , BIT_MASK ( UCSZ1 ) | BIT_MASK ( UCSZ0 ) );
                            CLEAR_BIT ( ucsrbValue , UCSZ2 );
                            //SET_BIT ( ucsrcValue , UCSZ1 );
                            //CLEAR_BIT ( ucsrcValue , UCSZ0 );
                            break;
                        case BIT_8_SIZE:
                            REPLACE_BITS ( ucsrcValue , ( 1 << UCSZ1 ) | ( 1 << UCSZ0 ) , BIT_MASK ( UCSZ1 ) | BIT_MASK ( UCSZ0 ) );
                            CLEAR_BIT ( ucsrbValue , UCSZ2 );
                            //SET_BIT ( ucsrcValue , UCSZ1 );
                            //SET_BIT ( ucsrcValue , UCSZ0 );
                            break;
                        case BIT_9_SIZE:
                            REPLACE_BITS ( ucsrcValue , ( 1 << UCSZ1 ) | ( 1 << UCSZ0 ) , BIT_MASK ( UCSZ1 ) | BIT_MASK ( UCSZ0 ) );
                            SET_BIT ( ucsrbValue , UCSZ2 );
                            //SET_BIT ( ucsrcValue , UCSZ1 );
                            //SET_BIT ( ucsrcValue , UCSZ0 );
                            break;
                        default:
                            initResult = UART_ERR_DATA_FRAME_SIZE;
                    }
                    if ( initResult == UART_OK )
                    {
                        switch ( uartCnfg->parity )
                        {
                            case NO_PARITY:
                                REPLACE_BITS ( ucsrcValue , ( 0 << UPM1 ) | ( 0 << UPM0 ) , BIT_MASK ( UPM1 ) | BIT_MASK ( UPM0 ) );
                                //CLEAR_BIT ( ucsrcValue , UPM1 );
                                //CLEAR_BIT ( ucsrcValue , UPM0 );
                                break;
                            case EVEN_PARITY:
                                REPLACE_BITS ( ucsrcValue , ( 1 << UPM1 ) | ( 0 << UPM0 ) , BIT_MASK ( UPM1 ) | BIT_MASK ( UPM0 ) );
                                //SET_BIT ( ucsrcValue , UPM1 );
                                //CLEAR_BIT ( ucsrcValue , UPM0 );
                                break;
                            case ODD_PARITY:
                                REPLACE_BITS ( ucsrcValue , ( 1 << UPM1 ) | ( 1 << UPM0 ) , BIT_MASK ( UPM1 ) | BIT_MASK ( UPM0 ) );
                                //SET_BIT ( ucsrcValue , UPM1 );
                                //SET_BIT ( ucsrcValue , UPM0 );
                                break;
                            default:
                                initResult = UART_ERR_PARITY;
                        }
                        if ( initResult == UART_OK )
                        {
                            switch ( uartCnfg->stopFrameSize )
                            {
                                case BIT_1_SIZE:
                                    CLEAR_BIT ( ucsrcValue , USBS );
                                    break;
                                case BIT_2_SIZE:
                                    SET_BIT ( ucsrcValue , USBS );
                                    break;
                                default:
                                    initResult = UART_ERR_STP;
                            }
                            if ( initResult == UART_OK )
                            {
                                switch ( uartCnfg->multiProcessorMode )
                                {
                                    case SINGLE:
                                        CLEAR_BIT ( ucsraValue , MPCM );
                                        break;
                                    case MULTI:
                                        SET_BIT ( ucsraValue , MPCM );
                                        break;
                                    default:
                                        initResult = UART_ERR_MULTI;
                                }
                                DIO_direction ( RX_PORT , RX_PIN , DIRECTION_INPUT );
                                DIO_direction ( TX_PORT , TX_PIN , DIRECTION_OUTPUT );
                                UCSRA = ucsraValue;
                                UCSRB = ucsrbValue;
                                SET_BIT ( ucsrcValue , URSEL );
                                UCSRC = ucsrcValue;
                            }
                        }
                    }
                }
            }
        }
    }
    else
    {
        initResult = ubbrResult;
    }
    return initResult;
}
UART_STD_ERR_t UART_setInterruptState ( UART_INT_FLAG_t flagType )
{
    UART_STD_ERR_t opResult = UART_OK;
    switch ( flagType )
    {
        case UART_FLAG_REC_COMP :
            SET_BIT ( UCSRB , RXCIE );
            break;
        case UART_FLAG_TRANS_COMP :
            SET_BIT ( UCSRB , TXCIE );
            break;
        case UART_FLAG_EMPTY:
            SET_BIT ( UCSRB , UDRIE );
            break;
        default:
            opResult = UART_ERR_INT_TYPE;
    }
    return opResult;
}
UART_STD_ERR_t UART_clearInterruptState ( UART_INT_FLAG_t flagType )
{
    UART_STD_ERR_t opResult = UART_OK;
    switch ( flagType )
    {
        case UART_FLAG_REC_COMP :
            CLEAR_BIT ( UCSRB , RXCIE );
            break;
        case UART_FLAG_TRANS_COMP :
            CLEAR_BIT ( UCSRB , TXCIE );
            break;
        case UART_FLAG_EMPTY:
            CLEAR_BIT ( UCSRB , UDRIE );
            break;
        default:
            opResult = UART_ERR_INT_TYPE;
    }
    return opResult;
}
UART_STD_ERR_t UART_getInterruptState ( UART_INT_FLAG_t flagType , INT_STATE_t* outputState )
{
    UART_STD_ERR_t opResult = UART_OK;
    switch ( flagType )
    {
        case UART_FLAG_REC_COMP :
            *outputState = ( INT_STATE_t ) READ_BIT ( UCSRB , RXCIE );
            break;
        case UART_FLAG_TRANS_COMP :
            *outputState = ( INT_STATE_t ) READ_BIT ( UCSRB , TXCIE );
            break;
        case UART_FLAG_EMPTY:
            *outputState = ( INT_STATE_t ) READ_BIT ( UCSRB , UDRIE );
            break;
        default:
            opResult = UART_ERR_INT_TYPE;
    }
    return opResult;
}
UART_STD_ERR_t UART_clearInterruptFlag ( UART_INT_FLAG_t flagType )
{
    UART_STD_ERR_t opResult = UART_OK;
    switch ( flagType )
    {
        case UART_FLAG_REC_COMP :
            SET_BIT ( UCSRA , RXC );
            break;
        case UART_FLAG_TRANS_COMP :
            SET_BIT ( UCSRA , TXC );
            break;
        case UART_FLAG_EMPTY:
            SET_BIT ( UCSRA , UDRE );
            break;
        default:
            opResult = UART_ERR_INT_TYPE;
    }
    return opResult;
}
UART_STD_ERR_t UART_getInterruptFlag ( UART_INT_FLAG_t flagType , FLAG_STATE_t* outputFlagState )
{
    UART_STD_ERR_t opResult = UART_OK;
    switch ( flagType )
    {
        case UART_FLAG_REC_COMP :
            *outputFlagState = ( FLAG_STATE_t ) READ_BIT ( UCSRA , RXC );
            break;
        case UART_FLAG_TRANS_COMP :
            *outputFlagState = ( FLAG_STATE_t ) READ_BIT ( UCSRA , TXC );
            break;
        case UART_FLAG_EMPTY:
            *outputFlagState = ( FLAG_STATE_t ) READ_BIT ( UCSRA , UDRE );
            break;
        default:
            opResult = UART_ERR_INT_TYPE;
    }
    return opResult;
}
UART_STD_ERR_t UART_getErrorFlag ( UART_ERR_FLAG_t errorFlagType , FLAG_STATE_t* outputFlagState )
{
    UART_STD_ERR_t opResult = UART_OK;
    switch ( errorFlagType )
    {
        case UART_ERR_FLAG_FRAME :
            *outputFlagState = ( FLAG_STATE_t ) READ_BIT ( UCSRA , FE );
            break;
        case UART_ERR_FLAG_OVERRUN :
            *outputFlagState = ( FLAG_STATE_t ) READ_BIT ( UCSRA , DOR );
            break;
        case UART_ERR_FLAG_PARITY:
            *outputFlagState = ( FLAG_STATE_t ) READ_BIT ( UCSRA , UPE );
            break;
        default:
            opResult = UART_ERR_ERR_TYPE;
    }
    return opResult;
}
UART_STD_ERR_t UART_setTransmissionMode ( UART_TRANS_MODE_t transmissionMode )
{
    UART_STD_ERR_t opResult = UART_OK;
    switch ( transmissionMode )
    {
        case ASYNC:
            REPLACE_BITS ( UCSRC , ( 1 << URSEL ) | ( 0 << UMSEL ) , BIT_MASK ( URSEL ) | BIT_MASK ( UMSEL ) );
            break;
        case SYNC:
            REPLACE_BITS ( UCSRC , ( 1 << URSEL ) | ( 1 << UMSEL ) , BIT_MASK ( URSEL ) | BIT_MASK ( UMSEL ) );
            break;
        default:
            opResult = UART_ERR_TRANS_MODE;
    }
    return opResult;
}
UART_STD_ERR_t UART_setTransmissionSpeed ( UART_TRANS_SPEED_t transmissionSpeedMode )
{
    UART_STD_ERR_t opResult = UART_OK;
    switch ( transmissionSpeedMode )
    {
        case NORMAL_SPEED:
            CLEAR_BIT ( UCSRA , U2X );
            break;
        case DOUBLE_SPEED:
            SET_BIT ( UCSRA , U2X );
            break;
        case NC_SPEED:
            break;
        default:
            opResult = UART_ERR_TRANS_SPEED;
    }
    return opResult;
}
UART_STD_ERR_t UART_setClckPolarity ( UART_CLCK_POLARITY_t clckPolarity )
{
    UART_STD_ERR_t opResult = UART_OK;
    switch ( clckPolarity )
    {
        case RISING_FALLING:
            REPLACE_BITS ( UCSRC , ( 1 << URSEL ) | ( 0 << UCPOL ) , BIT_MASK ( URSEL ) | BIT_MASK ( UCPOL ) );
            break;
        case FALLING_RISING:
            REPLACE_BITS ( UCSRC , ( 1 << URSEL ) | ( 1 << UCPOL ) , BIT_MASK ( URSEL ) | BIT_MASK ( UCPOL ) );
            break;
        case NC_POLARITY:
            break;
        default:
            opResult = UART_ERR_POLARITY;
    }
    return opResult;
}
UART_STD_ERR_t UART_setDataFrameSize ( UART_DATA_SIZE_t dataFrameSize )
{
    UART_STD_ERR_t opResult = UART_OK;
    switch ( dataFrameSize )
    {
        case BIT_5_SIZE:
            CLEAR_BIT ( UCSRB , UCSZ2 );
            REPLACE_BITS ( UCSRC , ( 0 << UCSZ1 ) | ( 0 << UCSZ0 ) , BIT_MASK ( UCSZ1 ) | BIT_MASK ( UCSZ0 ) );
            break;
        case BIT_6_SIZE:
            CLEAR_BIT ( UCSRB , UCSZ2 );
            REPLACE_BITS ( UCSRC , ( 0 << UCSZ1 ) | ( 1 << UCSZ0 ) , BIT_MASK ( UCSZ1 ) | BIT_MASK ( UCSZ0 ) );
            break;
        case BIT_7_SIZE:
            CLEAR_BIT ( UCSRB , UCSZ2 );
            REPLACE_BITS ( UCSRC , ( 1 << UCSZ1 ) | ( 0 << UCSZ0 ) , BIT_MASK ( UCSZ1 ) | BIT_MASK ( UCSZ0 ) );
            break;
        case BIT_8_SIZE:
            CLEAR_BIT ( UCSRB , UCSZ2 );
            REPLACE_BITS ( UCSRC , ( 1 << UCSZ1 ) | ( 1 << UCSZ0 ) , BIT_MASK ( UCSZ1 ) | BIT_MASK ( UCSZ0 ) );
            break;
        case BIT_9_SIZE:
            SET_BIT ( UCSRB , UCSZ2 );
            REPLACE_BITS ( UCSRC , ( 1 << UCSZ1 ) | ( 1 << UCSZ0 ) , BIT_MASK ( UCSZ1 ) | BIT_MASK ( UCSZ0 ) );
            break;
        default:
            opResult = UART_ERR_DATA_FRAME_SIZE;
    }
    return opResult;
}
UART_STD_ERR_t UART_setUbbr ( uint16_t ubbrValue )
{
    UART_STD_ERR_t opResult = UART_OK;
    CLEAR_BIT ( ubbrValue , 15 );
    if ( ubbrValue <= MAX_UBBR_VALUE )
    {
        UBRRH = ( uint8_t ) ( ( uint8_t ) ubbrValue >> ( uint8_t ) 8 );
        UBRRL = ( uint8_t ) ubbrValue;
    }
    else
    {
        opResult = UART_ERR_UBBR;
    }
    return opResult;
}
void UART_transmit ( uint16_t data )
{
    /* Wait for empty transmit buffer */
    while ( READ_BIT ( UCSRA , UDRE ) == 0 )
    {
    }
    /* Put data into buffer, sends the data */
    /* It should be better to cache this result after the initialization in a static global variable so that we don't have to check 3 bits every time */
    if ( UCSZ_VALUE == BIT_9_SIZE_VALUE )
    {
        if ( READ_BIT ( data , 8 ) == 1 )
        {
            SET_BIT ( UCSRB , TXB8 );
        }
        else
        {
            CLEAR_BIT ( UCSRB , TXB8 );
        }
    }
    UDR = ( uint8_t ) data;
}
uint16_t UART_receive ( void )
{
    /* Wait for data to be received */
    while ( READ_BIT ( UCSRA , RXC ) == 0 )
    {
    }
    /* Get and return received data from buffer */
    /* It should be better to cache this result after the initialization in a static global variable so that we don't have to check 3 bits every time */
    if ( UCSZ_VALUE == BIT_9_SIZE_VALUE )
    {
        return ( uint16_t ) ( ( ( uint16_t ) READ_BIT ( UCSRB , TXB8 ) << ( uint8_t ) 8 ) | ( uint16_t ) UDR );
    }
    return ( uint16_t ) UDR;
}
void UART_flush ( void )
{
    #pragma GCC diagnostic ignored "-Wunused-but-set-variable"
    volatile uint8_t dummy;
    while ( READ_BIT ( UCSRA , RXC ) == 1 )
    {
        dummy = UDR;
    }
}
void UART_transmitChar ( char charToTransmit )
{
    UART_transmit ( ( uint8_t ) charToTransmit );
}
void UART_transmitString ( char* stringToTransmit )
{
    while ( *stringToTransmit != '\0' )
    {
        UART_transmitChar ( *stringToTransmit );
        stringToTransmit++;
    }
}
