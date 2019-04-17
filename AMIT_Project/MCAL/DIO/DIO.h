#ifndef AMIT_PROJECT_DIO_H_
#define AMIT_PROJECT_DIO_H_
#include "DIO_config.h"
#define MAX_NUM_OF_PINS ( ( uint8_t ) 32 )
typedef enum _DIO_STD_ERR_t
{
    DIO_OK = ( uint8_t ) 0 ,
    DIO_ERR_PORT = ( uint8_t ) 1 ,
    DIO_ERR_NUM_OF_PINS = ( uint8_t ) 2 ,
    DIO_ERR_PIN_NUM = ( uint8_t ) 3 ,
    DIO_ERR_STATE = ( uint8_t ) 4 ,
    DIO_ERR_RES = ( uint8_t ) 5 ,
    DIO_ERR_DIR = ( uint8_t ) 6
} DIO_STD_ERR_t;
DIO_STD_ERR_t DIO_init ( void );
DIO_STD_ERR_t DIO_getConfig ( DIO_CNF_t* cnfg );
DIO_STD_ERR_t DIO_setConfig ( DIO_CNF_t* cnfg );
DIO_STD_ERR_t DIO_getDirection ( PORT_t port , PIN_t pin , DIRECTION_t* dir );
DIO_STD_ERR_t DIO_setDirection ( PORT_t port , PIN_t pin , DIRECTION_t dir );
DIO_STD_ERR_t DIO_getResistor ( PORT_t port , PIN_t pin , RESISTOR_t* resistor );
DIO_STD_ERR_t DIO_setResistor ( PORT_t port , PIN_t pin , RESISTOR_t resistor );
DIO_STD_ERR_t DIO_write ( PORT_t port , PIN_t pin , PIN_STATE_t value );
DIO_STD_ERR_t DIO_read ( PORT_t port , PIN_t pin , PIN_STATE_t* readState );
void DIO_disableAllPullUpResistors ( void );
#endif
