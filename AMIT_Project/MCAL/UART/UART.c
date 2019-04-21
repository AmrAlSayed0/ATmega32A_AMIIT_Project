#include <math.h>
#include <avr/io.h>
#include "io_extras.h"
#include "bit_helpers.h"
#include "common.h"
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
#define XCK_PORT                                PORT_B
#define XCK_PIN                                 PIN_0
static bool is9BitDataFrame = false;
static UART_STD_ERR_t UART_ubbrCalc ( uint32_t baudRate , UART_TRANS_MODE_t transmissionMode , UART_TRANS_SPEED_t transmissionSpeed , uint16_t* ubbrValue )
{
    UART_STD_ERR_t ubbrResult = UART_OK;
    if ( baudRate != ( uint32_t ) 0 )
    {
        switch ( transmissionMode )
        {
            case UART_TRANS_ASYNC :
                switch ( transmissionSpeed )
                {
                    case UART_NORMAL_SPEED :
                        *ubbrValue = ( uint16_t ) round ( UBBR_CALC ( baudRate , 16 ) );
                        break;
                    case UART_DOUBLE_SPEED :
                        *ubbrValue = ( uint16_t ) round ( UBBR_CALC ( baudRate , 8 ) );
                        break;
                    default:
                        ubbrResult = UART_ERR_TRANS_SPEED;
                }
                break;
            case UART_TRANS_SYNC :
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
    uint16_t ubbrValue = ( uint16_t ) 0;
    UART_STD_ERR_t ubbrResult = UART_ubbrCalc ( uartCnfg->baudRate , uartCnfg->transmissionMode , uartCnfg->transmissionSpeedMode , &ubbrValue );
    if ( ubbrResult == UART_OK )
    {
        UBRRH = ( uint8_t ) ( ubbrValue >> 0x08 );
        UBRRL = ( uint8_t ) ubbrValue;
        uint8_t ucsraValue = ( uint8_t ) 0;
        uint8_t ucsrbValue = ( uint8_t ) 0;
        uint8_t ucsrcValue = ( uint8_t ) 0;
        switch ( uartCnfg->transmissionMode )
        {
            case UART_TRANS_ASYNC :
                CLEAR_BIT ( ucsrcValue , UMSEL );
                switch ( uartCnfg->transmissionSpeedMode )
                {
                    case UART_NORMAL_SPEED :
                        CLEAR_BIT ( ucsraValue , U2X );
                        break;
                    case UART_DOUBLE_SPEED :
                        SET_BIT ( ucsraValue , U2X );
                        break;
                    case UART_NOT_CARE_SPEED :
                        break;
                    default:
                        initResult = UART_ERR_TRANS_SPEED;
                }
                break;
            case UART_TRANS_SYNC :
                CLEAR_BIT ( ucsraValue , U2X );
                SET_BIT ( ucsrcValue , UMSEL );
                switch ( uartCnfg->clckPolarity )
                {
                    case UART_CLCK_POLARITY_RISING_FALLING :
                        CLEAR_BIT ( ucsrcValue , UCPOL );
                        break;
                    case UART_CLCK_POLARITY_FALLING_RISING :
                        SET_BIT ( ucsrcValue , UCPOL );
                        break;
                    case UART_CLCK_POLARITY_NOT_CARE :
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
                case UART_COM_ENABLED :
                    SET_BIT ( ucsrbValue , TXEN );
                    break;
                case UART_COM_DISABLED :
                    CLEAR_BIT ( ucsrbValue , TXEN );
                    break;
                default:
                    initResult = UART_ERR_TRANS;
            }
            if ( initResult == UART_OK )
            {
                switch ( uartCnfg->receiverState )
                {
                    case UART_COM_ENABLED :
                        SET_BIT ( ucsrbValue , RXEN );
                        break;
                    case UART_COM_DISABLED :
                        CLEAR_BIT ( ucsrbValue , RXEN );
                        break;
                    default:
                        initResult = UART_ERR_RECV;
                }
                if ( initResult == UART_OK )
                {
                    switch ( uartCnfg->dataFrameSize )
                    {
                        case UART_DATA_SIZE_5_BIT :
                            REPLACE_BITS ( ucsrcValue , ( 0x00 << UCSZ1 ) | ( 0x00 << UCSZ0 ) , BIT_MASK ( UCSZ1 ) | BIT_MASK ( UCSZ0 ) );
                            CLEAR_BIT ( ucsrbValue , UCSZ2 );
                            break;
                        case UART_DATA_SIZE_6_BIT :
                            REPLACE_BITS ( ucsrcValue , ( 0x00 << UCSZ1 ) | ( 0x01 << UCSZ0 ) , BIT_MASK ( UCSZ1 ) | BIT_MASK ( UCSZ0 ) );
                            CLEAR_BIT ( ucsrbValue , UCSZ2 );
                            break;
                        case UART_DATA_SIZE_7_BIT :
                            REPLACE_BITS ( ucsrcValue , ( 0x01 << UCSZ1 ) | ( 0x00 << UCSZ0 ) , BIT_MASK ( UCSZ1 ) | BIT_MASK ( UCSZ0 ) );
                            CLEAR_BIT ( ucsrbValue , UCSZ2 );
                            break;
                        case UART_DATA_SIZE_8_BIT :
                            REPLACE_BITS ( ucsrcValue , ( 0x01 << UCSZ1 ) | ( 0x01 << UCSZ0 ) , BIT_MASK ( UCSZ1 ) | BIT_MASK ( UCSZ0 ) );
                            CLEAR_BIT ( ucsrbValue , UCSZ2 );
                            break;
                        case UART_DATA_SIZE_9_BIT :
                            REPLACE_BITS ( ucsrcValue , ( 0x01 << UCSZ1 ) | ( 0x01 << UCSZ0 ) , BIT_MASK ( UCSZ1 ) | BIT_MASK ( UCSZ0 ) );
                            SET_BIT ( ucsrbValue , UCSZ2 );
                            is9BitDataFrame = true;
                            break;
                        default:
                            initResult = UART_ERR_DATA_FRAME_SIZE;
                    }
                    if ( initResult == UART_OK )
                    {
                        switch ( uartCnfg->parity )
                        {
                            case UART_PARITY_NO :
                                REPLACE_BITS ( ucsrcValue , ( 0x00 << UPM1 ) | ( 0x00 << UPM0 ) , BIT_MASK ( UPM1 ) | BIT_MASK ( UPM0 ) );
                                break;
                            case UART_PARITY_EVEN :
                                REPLACE_BITS ( ucsrcValue , ( 0x01 << UPM1 ) | ( 0x00 << UPM0 ) , BIT_MASK ( UPM1 ) | BIT_MASK ( UPM0 ) );
                                break;
                            case UART_PARITY_ODD :
                                REPLACE_BITS ( ucsrcValue , ( 0x01 << UPM1 ) | ( 0x01 << UPM0 ) , BIT_MASK ( UPM1 ) | BIT_MASK ( UPM0 ) );
                                break;
                            default:
                                initResult = UART_ERR_PARITY;
                        }
                        if ( initResult == UART_OK )
                        {
                            switch ( uartCnfg->stopFrameSize )
                            {
                                case UART_STP_SIZE_1_BIT :
                                    CLEAR_BIT ( ucsrcValue , USBS );
                                    break;
                                case UART_STP_SIZE_2_BIT :
                                    SET_BIT ( ucsrcValue , USBS );
                                    break;
                                default:
                                    initResult = UART_ERR_STP;
                            }
                            if ( initResult == UART_OK )
                            {
                                switch ( uartCnfg->multiProcessorMode )
                                {
                                    case UART_PROC_MODE_SINGLE :
                                        CLEAR_BIT ( ucsraValue , MPCM );
                                        break;
                                    case UART_PROC_MODE_MULTI :
                                        SET_BIT ( ucsraValue , MPCM );
                                        break;
                                    default:
                                        initResult = UART_ERR_MULTI;
                                }
                                DIO_setDirection ( RX_PORT , RX_PIN , DIRECTION_INPUT );
                                DIO_setDirection ( TX_PORT , TX_PIN , DIRECTION_OUTPUT );
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
        case UART_FLAG_EMPTY :
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
        case UART_FLAG_EMPTY :
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
        case UART_FLAG_EMPTY :
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
        case UART_FLAG_EMPTY :
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
        case UART_FLAG_EMPTY :
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
        case UART_ERR_FLAG_PARITY :
            *outputFlagState = ( FLAG_STATE_t ) READ_BIT ( UCSRA , UPE );
            break;
        default:
            opResult = UART_ERR_ERR_TYPE;
    }
    return opResult;
}
UART_STD_ERR_t UART_setUbbr ( uint16_t ubbrValue )
{
    UART_STD_ERR_t opResult = UART_OK;
    CLEAR_BIT ( ubbrValue , 15 );
    if ( ubbrValue <= MAX_UBBR_VALUE )
    {
        UBRRH = ( uint8_t ) ( ubbrValue >> 0x08 );
        UBRRL = ( uint8_t ) ubbrValue;
    }
    else
    {
        opResult = UART_ERR_UBBR;
    }
    return opResult;
}
UART_STD_ERR_t UART_setTransmissionMode ( UART_TRANS_MODE_t transmissionMode )
{
    UART_STD_ERR_t opResult = UART_OK;
    uint8_t ucsrcValue;
    switch ( transmissionMode )
    {
        case UART_TRANS_ASYNC :
            ucsrcValue = UBRRH;
            ucsrcValue = UCSRC;
            REPLACE_BITS ( ucsrcValue , ( 0x01 << URSEL ) | ( 0x00 << UMSEL ) , BIT_MASK ( URSEL ) | BIT_MASK ( UMSEL ) );
            UCSRC = ucsrcValue;
            break;
        case UART_TRANS_SYNC :
            ucsrcValue = UBRRH;
            ucsrcValue = UCSRC;
            REPLACE_BITS ( UCSRC , ( 0x01 << URSEL ) | ( 0x01 << UMSEL ) , BIT_MASK ( URSEL ) | BIT_MASK ( UMSEL ) );
            UCSRC = ucsrcValue;
            break;
        default:
            opResult = UART_ERR_TRANS_MODE;
    }
    return opResult;
}
UART_STD_ERR_t UART_setTransmissionSpeedMode ( UART_TRANS_SPEED_t transmissionSpeedMode )
{
    UART_STD_ERR_t opResult = UART_OK;
    switch ( transmissionSpeedMode )
    {
        case UART_NORMAL_SPEED :
            CLEAR_BIT ( UCSRA , U2X );
            break;
        case UART_DOUBLE_SPEED :
            SET_BIT ( UCSRA , U2X );
            break;
        case UART_NOT_CARE_SPEED :
            break;
        default:
            opResult = UART_ERR_TRANS_SPEED;
    }
    return opResult;
}
UART_STD_ERR_t UART_setClckPolarity ( UART_CLCK_POLARITY_t clckPolarity )
{
    UART_STD_ERR_t opResult = UART_OK;
    uint8_t ucsrcValue;
    switch ( clckPolarity )
    {
        case UART_CLCK_POLARITY_RISING_FALLING :
            ucsrcValue = UBRRH;
            ucsrcValue = UCSRC;
            REPLACE_BITS ( UCSRC , ( 0x01 << URSEL ) | ( 0x00 << UCPOL ) , BIT_MASK ( URSEL ) | BIT_MASK ( UCPOL ) );
            UCSRC = ucsrcValue;
            break;
        case UART_CLCK_POLARITY_FALLING_RISING :
            ucsrcValue = UBRRH;
            ucsrcValue = UCSRC;
            REPLACE_BITS ( UCSRC , ( 0x01 << URSEL ) | ( 0x01 << UCPOL ) , BIT_MASK ( URSEL ) | BIT_MASK ( UCPOL ) );
            UCSRC = ucsrcValue;
            break;
        case UART_CLCK_POLARITY_NOT_CARE :
            break;
        default:
            opResult = UART_ERR_POLARITY;
    }
    return opResult;
}
UART_STD_ERR_t UART_setDataFrameSize ( UART_DATA_SIZE_t dataFrameSize )
{
    UART_STD_ERR_t opResult = UART_OK;
    uint8_t ucsrcValue;
    switch ( dataFrameSize )
    {
        case UART_DATA_SIZE_5_BIT :
            CLEAR_BIT ( UCSRB , UCSZ2 );
            ucsrcValue = UBRRH;
            ucsrcValue = UCSRC;
            REPLACE_BITS ( UCSRC , ( 0x01 << URSEL ) | ( 0x00 << UCSZ1 ) | ( 0x00 << UCSZ0 ) , BIT_MASK ( URSEL ) | BIT_MASK ( UCSZ1 ) | BIT_MASK ( UCSZ0 ) );
            UCSRC = ucsrcValue;
            break;
        case UART_DATA_SIZE_6_BIT :
            CLEAR_BIT ( UCSRB , UCSZ2 );
            ucsrcValue = UBRRH;
            ucsrcValue = UCSRC;
            REPLACE_BITS ( UCSRC , ( 0x01 << URSEL ) | ( 0x00 << UCSZ1 ) | ( 0x01 << UCSZ0 ) , BIT_MASK ( URSEL ) | BIT_MASK ( UCSZ1 ) | BIT_MASK ( UCSZ0 ) );
            UCSRC = ucsrcValue;
            break;
        case UART_DATA_SIZE_7_BIT :
            CLEAR_BIT ( UCSRB , UCSZ2 );
            ucsrcValue = UBRRH;
            ucsrcValue = UCSRC;
            REPLACE_BITS ( UCSRC , ( 0x01 << URSEL ) | ( 0x01 << UCSZ1 ) | ( 0x00 << UCSZ0 ) , BIT_MASK ( URSEL ) | BIT_MASK ( UCSZ1 ) | BIT_MASK ( UCSZ0 ) );
            UCSRC = ucsrcValue;
            break;
        case UART_DATA_SIZE_8_BIT :
            CLEAR_BIT ( UCSRB , UCSZ2 );
            ucsrcValue = UBRRH;
            ucsrcValue = UCSRC;
            REPLACE_BITS ( UCSRC , ( 0x01 << URSEL ) | ( 0x01 << UCSZ1 ) | ( 0x01 << UCSZ0 ) , BIT_MASK ( URSEL ) | BIT_MASK ( UCSZ1 ) | BIT_MASK ( UCSZ0 ) );
            UCSRC = ucsrcValue;
            break;
        case UART_DATA_SIZE_9_BIT :
            SET_BIT ( UCSRB , UCSZ2 );
            ucsrcValue = UBRRH;
            ucsrcValue = UCSRC;
            REPLACE_BITS ( UCSRC , ( 0x01 << URSEL ) | ( 0x01 << UCSZ1 ) | ( 0x01 << UCSZ0 ) , BIT_MASK ( URSEL ) | BIT_MASK ( UCSZ1 ) | BIT_MASK ( UCSZ0 ) );
            UCSRC = ucsrcValue;
            is9BitDataFrame = true;
            break;
        default:
            opResult = UART_ERR_DATA_FRAME_SIZE;
    }
    return opResult;
}
UART_STD_ERR_t UART_setParitySize ( UART_PARITY_t parity )
{
    UART_STD_ERR_t opResult = UART_OK;
    uint8_t ucsrcValue;
    switch ( parity )
    {
        case UART_PARITY_NO :
            ucsrcValue = UBRRH;
            ucsrcValue = UCSRC;
            REPLACE_BITS ( UCSRC , ( 0x01 << URSEL ) | ( 0x00 << UPM1 ) | ( 0x00 << UPM0 ) , BIT_MASK ( URSEL ) | BIT_MASK ( UPM1 ) | BIT_MASK ( UPM0 ) );
            UCSRC = ucsrcValue;
            break;
        case UART_PARITY_EVEN :
            ucsrcValue = UBRRH;
            ucsrcValue = UCSRC;
            REPLACE_BITS ( UCSRC , ( 0x01 << URSEL ) | ( 0x01 << UPM1 ) | ( 0x00 << UPM0 ) , BIT_MASK ( URSEL ) | BIT_MASK ( UPM1 ) | BIT_MASK ( UPM0 ) );
            UCSRC = ucsrcValue;
            break;
        case UART_PARITY_ODD :
            ucsrcValue = UBRRH;
            ucsrcValue = UCSRC;
            REPLACE_BITS ( UCSRC , ( 0x01 << URSEL ) | ( 0x01 << UPM1 ) | ( 0x01 << UPM0 ) , BIT_MASK ( URSEL ) | BIT_MASK ( UPM1 ) | BIT_MASK ( UPM0 ) );
            UCSRC = ucsrcValue;
            break;
        default:
            opResult = UART_ERR_PARITY;
    }
    return opResult;
}
UART_STD_ERR_t UART_setStopSize ( UART_STP_SIZE_t stopFrameSize )
{
    UART_STD_ERR_t opResult = UART_OK;
    uint8_t ucsrcValue;
    switch ( stopFrameSize )
    {
        case UART_STP_SIZE_1_BIT :
            ucsrcValue = UBRRH;
            ucsrcValue = UCSRC;
            CLEAR_BIT ( ucsrcValue , USBS );
            UCSRC = ucsrcValue;
            break;
        case UART_STP_SIZE_2_BIT :
            ucsrcValue = UBRRH;
            ucsrcValue = UCSRC;
            SET_BIT ( ucsrcValue , USBS );
            UCSRC = ucsrcValue;
            break;
        default:
            opResult = UART_ERR_STP;
    }
    return opResult;
}
UART_STD_ERR_t UART_setProcessorMode ( UART_PROCESS_MODE_t multiProcessorMode )
{
    UART_STD_ERR_t opResult = UART_OK;
    switch ( multiProcessorMode )
    {
        case UART_PROC_MODE_SINGLE :
            CLEAR_BIT ( UCSRA , MPCM );
            break;
        case UART_PROC_MODE_MULTI :
            SET_BIT ( UCSRA , MPCM );
            break;
        default:
            opResult = UART_ERR_MULTI;
    }
    return opResult;
}
void UART_transmit ( uint16_t data )
{
    /* Wait for empty transmit buffer */
    while ( READ_BIT ( UCSRA , UDRE ) == BIT_STATE_CLEARED )
    {
    }
    /* Put data into buffer, sends the data */
    /* It should be better to cache this result after the initialization in a static global variable so that we don't have to check 3 bits every time */
    if ( is9BitDataFrame )
    {
        if ( READ_BIT ( data , 8 ) == BIT_STATE_SET )
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
    while ( READ_BIT ( UCSRA , RXC ) == BIT_STATE_CLEARED )
    {
    }
    /* Get and return received data from buffer */
    /* It should be better to cache this result after the initialization in a static global variable so that we don't have to check 3 bits every time */
    if ( is9BitDataFrame )
    {
        return ( uint16_t ) ( ( ( uint16_t ) READ_BIT ( UCSRB , TXB8 ) << 0x08 ) | ( uint16_t ) UDR );
    }
    return ( uint16_t ) UDR;
}
void UART_flush ( void )
{
    #pragma GCC diagnostic ignored "-Wunused-but-set-variable"
    volatile uint8_t dummy;
    while ( READ_BIT ( UCSRA , RXC ) == BIT_STATE_SET )
    {
        dummy = UDR;
    }
}
void UART_transmitByteArray ( uint8_t* arr , uint32_t size )
{
    uint32_t i;
    for ( i = 0; i < size; i++ )
    {
        UART_transmit ( *arr );
        arr++;
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
