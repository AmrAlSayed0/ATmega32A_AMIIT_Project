#ifndef AMIT_PROJECT_SPI_H_
#define AMIT_PROJECT_SPI_H_
#include "Std_Types.h"
#include "common.h"
typedef enum _SPI_DATA_ORDER_t
{
    DATA_ORDER_MSB = ( uint8_t ) 0 ,
    DATA_ORDER_LSB = ( uint8_t ) 1
} SPI_DATA_ORDER_t;
typedef enum _SPI_MODE_t
{
    SPI_MODE_0 = ( uint8_t ) 0 ,
    SPI_MODE_1 = ( uint8_t ) 1 ,
    SPI_MODE_2 = ( uint8_t ) 2 ,
    SPI_MODE_3 = ( uint8_t ) 3
} SPI_MODE_t;
typedef enum _SPI_FREQ_t
{
    SPI_FREQ_4 = ( uint8_t ) 0 ,
    SPI_FREQ_16 = ( uint8_t ) 1 ,
    SPI_FREQ_64 = ( uint8_t ) 2 ,
    SPI_FREQ_128 = ( uint8_t ) 3 ,
    SPI_FREQ_2X_2 = ( uint8_t ) 4 ,
    SPI_FREQ_2X_8 = ( uint8_t ) 5 ,
    SPI_FREQ_2X_32 = ( uint8_t ) 6 ,
    SPI_FREQ_2X_64 = ( uint8_t ) 7
} SPI_FREQ_t;
typedef enum _SPI_STD_ERR_t
{
    SPI_OK = ( uint8_t ) 0 ,
    SPI_ERR_MODE = ( uint8_t ) 1 ,
    SPI_ERR_FREQ = ( uint8_t ) 2 ,
    SPI_ERR_DATA_ORDER = ( uint8_t ) 3 ,
    SPI_ERR_CONFIG = ( uint8_t ) 4
} SPI_STD_ERR_t;
typedef struct _SPI_CFG_t
{
    SPI_DATA_ORDER_t dataOrder;
    SPI_MODE_t mode;
    SPI_FREQ_t freq;
} SPI_CFG_t;
void SPI_enable ();
void SPI_disable ();
SPI_STD_ERR_t SPI_masterInit ( SPI_CFG_t* config );
void SPI_masterTransmit ( uint8_t data );
SPI_STD_ERR_t SPI_slaveInit ( SPI_CFG_t* config );
uint8_t SPI_slaveReceive ();
void SPI_setInterruptState ();
void SPI_clearInterruptState ();
INT_STATE_t SPI_getInterruptState ();
void SPI_clearInterruptFlag ();
FLAG_STATE_t SPI_getInterruptFlag ();
SPI_STD_ERR_t SPI_setDataOrder ( SPI_DATA_ORDER_t dataOrder );
SPI_STD_ERR_t SPI_setMode ( SPI_MODE_t mode );
SPI_STD_ERR_t SPI_setFreq ( SPI_FREQ_t freq );
#endif
