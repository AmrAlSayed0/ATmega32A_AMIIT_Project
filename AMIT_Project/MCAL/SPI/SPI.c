#include <avr/io.h>
#include "io_extras.h"
#include "bit_helpers.h"
#include "common.h"
#include "DIO.h"
#include "SPI_private.h"
#include "SPI_config.h"
#include "SPI.h"
#define SS_PORT     PORT_B
#define SS_PIN      PIN_4
#define MOSI_PORT   PORT_B
#define MOSI_PIN    PIN_5
#define MISO_PORT   PORT_B
#define MISO_PIN    PIN_6
#define SCK_PORT    PORT_B
#define SCK_PIN     PIN_7
void SPI_enable ( void )
{
    SET_BIT ( SPCR , SPE );
}
void SPI_disable ( void )
{
    CLEAR_BIT ( SPCR , SPE );
}
SPI_STD_ERR_t SPI_masterInit ( SPI_CFG_t* config )
{
    SPI_STD_ERR_t opResult = SPI_OK;
    if ( config != NULL_PTR )
    {
        DIO_setDirection ( SS_PORT , SS_PIN , DIRECTION_OUTPUT );
        DIO_setDirection ( MOSI_PORT , MOSI_PIN , DIRECTION_OUTPUT );
        DIO_setDirection ( MISO_PORT , MISO_PIN , DIRECTION_INPUT );
        DIO_setDirection ( SCK_PORT , SCK_PIN , DIRECTION_OUTPUT );
        uint8_t spcrValue = ( uint8_t ) 0;
        uint8_t spsrValue = ( uint8_t ) 0;
        SET_BIT ( spcrValue , MSTR );
        //opResult = SPI_setDataOrder ( config->dataOrder );
        switch ( config->dataOrder )
        {
            case DATA_ORDER_MSB :
            case DATA_ORDER_LSB :
                REPLACE_BITS ( spcrValue , ( ( uint8_t ) config->dataOrder ) << DORD , BIT_MASK ( DORD ) );
                break;
            default:
                opResult = SPI_ERR_DATA_ORDER;
        }
        if ( opResult == SPI_OK )
        {
            //opResult = SPI_setMode ( config->mode );
            switch ( config->mode )
            {
                case SPI_MODE_0 :
                case SPI_MODE_1 :
                case SPI_MODE_2 :
                case SPI_MODE_3 :
                    REPLACE_BITS ( spcrValue , ( ( uint8_t ) config->mode ) << CPHA , BIT_MASK2 ( CPOL , CPHA ) );
                    break;
                default:
                    opResult = SPI_ERR_MODE;
            }
            if ( opResult == SPI_OK )
            {
                //opResult = SPI_setFreq ( config->freq );
                switch ( config->freq )
                {
                    case SPI_FREQ_4 :
                    case SPI_FREQ_16 :
                    case SPI_FREQ_64 :
                    case SPI_FREQ_128 :
                        REPLACE_BITS ( spcrValue , ( ( uint8_t ) config->freq ) << SPR0 , BIT_MASK2 ( SPR1 , SPR0 ) );
                        break;
                    case SPI_FREQ_2X_2 :
                    case SPI_FREQ_2X_8 :
                    case SPI_FREQ_2X_32 :
                    case SPI_FREQ_2X_64 :
                        REPLACE_BITS ( spcrValue , ( ( uint8_t ) config->freq ) << SPR0 , BIT_MASK2 ( SPR1 , SPR0 ) );
                        SET_BIT ( spsrValue , SPI2X );
                        break;
                    default:
                        opResult = SPI_ERR_FREQ;
                }
                if ( opResult == SPI_OK )
                {
                    //SPI_enable ();
                    SET_BIT ( spcrValue , SPE );
                    SPCR = spcrValue;
                    SPSR = spsrValue;
                }
            }
        }
    }
    else
    {
        opResult = SPI_ERR_CONFIG;
    }
    return opResult;
}
void SPI_masterTransmit ( uint8_t data )
{
    DIO_write ( SS_PORT , SS_PIN , PIN_STATE_LOW );
    /* Start transmission */
    SPDR = data;
    /* Wait for transmission complete */
    while ( READ_BIT( SPSR , SPIF ) == BIT_STATE_CLEARED )
    {
    }
    SPI_clearInterruptFlag ();
    DIO_write ( SS_PORT , SS_PIN , PIN_STATE_HIGH );
}
void SPI_masterTransmitData ( void* data , uint32_t size )
{
    DIO_write ( SS_PORT , SS_PIN , PIN_STATE_LOW );
    /* Start transmission */
    uint8_t* tempDataPtr = ( uint8_t* ) data;
    while ( size != 0 )
    {
        SPDR = *tempDataPtr;
        /* Wait for transmission complete */
        while ( READ_BIT( SPSR , SPIF ) == BIT_STATE_CLEARED )
        {
        }
        SPI_clearInterruptFlag ();
        size--;
        tempDataPtr++;
    }
    DIO_write ( SS_PORT , SS_PIN , PIN_STATE_HIGH );
}
SPI_STD_ERR_t SPI_slaveInit ( SPI_CFG_t* config )
{
    SPI_STD_ERR_t opResult = SPI_OK;
    if ( config != NULL_PTR )
    {
        DIO_setDirection ( SS_PORT , SS_PIN , DIRECTION_INPUT );
        DIO_setDirection ( MOSI_PORT , MOSI_PIN , DIRECTION_INPUT );
        DIO_setDirection ( MISO_PORT , MISO_PIN , DIRECTION_OUTPUT );
        DIO_setDirection ( SCK_PORT , SCK_PIN , DIRECTION_INPUT );
        uint8_t spcrValue = ( uint8_t ) 0;
        uint8_t spsrValue = ( uint8_t ) 0;
        CLEAR_BIT ( spcrValue , MSTR );
        //opResult = SPI_setDataOrder ( config->dataOrder );
        switch ( config->dataOrder )
        {
            case DATA_ORDER_MSB :
            case DATA_ORDER_LSB :
                REPLACE_BITS ( spcrValue , ( ( uint8_t ) config->dataOrder ) << DORD , BIT_MASK ( DORD ) );
                break;
            default:
                opResult = SPI_ERR_DATA_ORDER;
        }
        if ( opResult == SPI_OK )
        {
            //opResult = SPI_setMode ( config->mode );
            switch ( config->mode )
            {
                case SPI_MODE_0 :
                case SPI_MODE_1 :
                case SPI_MODE_2 :
                case SPI_MODE_3 :
                    REPLACE_BITS ( spcrValue , ( ( uint8_t ) config->mode ) << CPHA , BIT_MASK2 ( CPOL , CPHA ) );
                    break;
                default:
                    opResult = SPI_ERR_MODE;
            }
            if ( opResult == SPI_OK )
            {
                //opResult = SPI_setFreq ( config->freq );
                switch ( config->freq )
                {
                    case SPI_FREQ_4 :
                    case SPI_FREQ_16 :
                    case SPI_FREQ_64 :
                    case SPI_FREQ_128 :
                        REPLACE_BITS ( spcrValue , ( ( uint8_t ) config->freq ) << SPR0 , BIT_MASK2 ( SPR1 , SPR0 ) );
                        break;
                    case SPI_FREQ_2X_2 :
                    case SPI_FREQ_2X_8 :
                    case SPI_FREQ_2X_32 :
                    case SPI_FREQ_2X_64 :
                        REPLACE_BITS ( spcrValue , ( ( uint8_t ) config->freq ) << SPR0 , BIT_MASK2 ( SPR1 , SPR0 ) );
                        SET_BIT ( spsrValue , SPI2X );
                        break;
                    default:
                        opResult = SPI_ERR_FREQ;
                }
                if ( opResult == SPI_OK )
                {
                    //SPI_enable ();
                    SET_BIT ( spcrValue , SPE );
                    SPCR = spcrValue;
                    SPSR = spsrValue;
                }
            }
        }
    }
    else
    {
        opResult = SPI_ERR_CONFIG;
    }
    return opResult;
}
uint8_t SPI_slaveReceive ( void )
{
    /* Wait for reception complete */
    while ( READ_BIT( SPSR , SPIF ) == BIT_STATE_CLEARED )
    {
    }
    /* Return data register */
    return SPDR;
}
void SPI_setInterruptState ( void )
{
    SET_BIT ( SPCR , SPIE );
}
void SPI_clearInterruptState ( void )
{
    CLEAR_BIT ( SPCR , SPIE );
}
INT_STATE_t SPI_getInterruptState ( void )
{
    return ( INT_STATE_t ) READ_BIT ( SPCR , SPIE );
}
void SPI_clearInterruptFlag ( void )
{
    #pragma GCC diagnostic ignored "-Wunused-variable"
    volatile uint8_t spsrDummy = SPSR;
    #pragma GCC diagnostic ignored "-Wunused-variable"
    volatile uint8_t spdrDummy = SPDR;
}
FLAG_STATE_t SPI_getInterruptFlag ( void )
{
    return ( FLAG_STATE_t ) READ_BIT ( SPSR , SPIF );
}
SPI_STD_ERR_t SPI_setDataOrder ( SPI_DATA_ORDER_t dataOrder )
{
    SPI_STD_ERR_t opResult = SPI_OK;
    switch ( dataOrder )
    {
        case DATA_ORDER_MSB :
        case DATA_ORDER_LSB :
            REPLACE_BITS ( SPCR , ( ( uint8_t ) dataOrder ) << DORD , BIT_MASK ( DORD ) );
            break;
        default:
            opResult = SPI_ERR_DATA_ORDER;
    }
    return opResult;
}
SPI_STD_ERR_t SPI_setMode ( SPI_MODE_t mode )
{
    SPI_STD_ERR_t opResult = SPI_OK;
    switch ( mode )
    {
        case SPI_MODE_0 :
        case SPI_MODE_1 :
        case SPI_MODE_2 :
        case SPI_MODE_3 :
            REPLACE_BITS ( SPCR , ( ( uint8_t ) mode ) << CPHA , BIT_MASK2 ( CPOL , CPHA ) );
            break;
        default:
            opResult = SPI_ERR_MODE;
    }
    return opResult;
}
SPI_STD_ERR_t SPI_setFreq ( SPI_FREQ_t freq )
{
    SPI_STD_ERR_t opResult = SPI_OK;
    switch ( freq )
    {
        case SPI_FREQ_4 :
        case SPI_FREQ_16 :
        case SPI_FREQ_64 :
        case SPI_FREQ_128 :
            REPLACE_BITS ( SPCR , ( ( uint8_t ) freq ) << SPR0 , BIT_MASK2 ( SPR1 , SPR0 ) );
            break;
        case SPI_FREQ_2X_2 :
        case SPI_FREQ_2X_8 :
        case SPI_FREQ_2X_32 :
        case SPI_FREQ_2X_64 :
            REPLACE_BITS ( SPCR , ( ( uint8_t ) freq ) << SPR0 , BIT_MASK2 ( SPR1 , SPR0 ) );
            SET_BIT ( SPSR , SPI2X );
            break;
        default:
            opResult = SPI_ERR_FREQ;
    }
    return opResult;
}
