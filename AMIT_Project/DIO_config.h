#ifndef AMIT_PROJECT_DIO_CFG_H
#define AMIT_PROJECT_DIO_CFG_H
#include "Std_Types.h"
typedef enum _DIO_t
{
    DIO_ADC_0 = ( uint8_t ) 0 ,
    DIO_PA_0 = ( uint8_t ) 0 ,
    DIO_ADC_1 = ( uint8_t ) 1 ,
    DIO_PA_1 = ( uint8_t ) 1 ,
    DIO_ADC_2 = ( uint8_t ) 2 ,
    DIO_PA_2 = ( uint8_t ) 2 ,
    DIO_ADC_3 = ( uint8_t ) 3 ,
    DIO_PA_3 = ( uint8_t ) 3 ,
    DIO_ADC_4 = ( uint8_t ) 4 ,
    DIO_PA_4 = ( uint8_t ) 4 ,
    DIO_ADC_5 = ( uint8_t ) 5 ,
    DIO_PA_5 = ( uint8_t ) 5 ,
    DIO_ADC_6 = ( uint8_t ) 6 ,
    DIO_PA_6 = ( uint8_t ) 6 ,
    DIO_ADC_7 = ( uint8_t ) 7 ,
    DIO_PA_7 = ( uint8_t ) 7 ,
    DIO_XCK = ( uint8_t ) 8 ,
    DIO_T_0 = ( uint8_t ) 8 ,
    DIO_PB_0 = ( uint8_t ) 8 ,
    DIO_T_1 = ( uint8_t ) 9 ,
    DIO_PB_1 = ( uint8_t ) 9 ,
    DIO_INT_2 = ( uint8_t ) 10 ,
    DIO_AIN_0 = ( uint8_t ) 10 ,
    DIO_PB_2 = ( uint8_t ) 10 ,
    DIO_OC_0 = ( uint8_t ) 11 ,
    DIO_AIN_1 = ( uint8_t ) 11 ,
    DIO_PB_3 = ( uint8_t ) 11 ,
    DIO_SS = ( uint8_t ) 12 ,
    DIO_PB_4 = ( uint8_t ) 12 ,
    DIO_MOSI = ( uint8_t ) 13 ,
    DIO_PB_5 = ( uint8_t ) 13 ,
    DIO_MISO = ( uint8_t ) 14 ,
    DIO_PB_6 = ( uint8_t ) 14 ,
    DIO_SCK = ( uint8_t ) 15 ,
    DIO_PB_7 = ( uint8_t ) 15 ,
    DIO_SCL = ( uint8_t ) 16 ,
    DIO_PC_0 = ( uint8_t ) 16 ,
    DIO_SDA = ( uint8_t ) 17 ,
    DIO_PC_1 = ( uint8_t ) 17 ,
    DIO_TCK = ( uint8_t ) 18 ,
    DIO_PC_2 = ( uint8_t ) 18 ,
    DIO_TMS = ( uint8_t ) 19 ,
    DIO_PC_3 = ( uint8_t ) 19 ,
    DIO_TDO = ( uint8_t ) 20 ,
    DIO_PC_4 = ( uint8_t ) 20 ,
    DIO_TDI = ( uint8_t ) 21 ,
    DIO_PC_5 = ( uint8_t ) 21 ,
    DIO_TOSC_1 = ( uint8_t ) 22 ,
    DIO_PC_6 = ( uint8_t ) 22 ,
    DIO_TOSC_2 = ( uint8_t ) 23 ,
    DIO_PC_7 = ( uint8_t ) 23 ,
    DIO_RXD = ( uint8_t ) 24 ,
    DIO_PD_0 = ( uint8_t ) 24 ,
    DIO_TXD = ( uint8_t ) 25 ,
    DIO_PD_1 = ( uint8_t ) 25 ,
    DIO_INT_0 = ( uint8_t ) 26 ,
    DIO_PD_2 = ( uint8_t ) 26 ,
    DIO_INT_1 = ( uint8_t ) 27 ,
    DIO_PD_3 = ( uint8_t ) 27 ,
    DIO_OC_1B = ( uint8_t ) 28 ,
    DIO_PD_4 = ( uint8_t ) 28 ,
    DIO_OC_1A = ( uint8_t ) 29 ,
    DIO_PD_5 = ( uint8_t ) 29 ,
    DIO_ICP_1 = ( uint8_t ) 30 ,
    DIO_PD_6 = ( uint8_t ) 30 ,
    DIO_OC_2 = ( uint8_t ) 31 ,
    DIO_PD_7 = ( uint8_t ) 31 ,
    NUM_OF_PINS
} DIO_t;
typedef enum _PORT_t
{
    PORT_A = ( uint8_t ) 0 ,
    PORT_B = ( uint8_t ) 1 ,
    PORT_C = ( uint8_t ) 2 ,
    PORT_D = ( uint8_t ) 3
} PORT_t;
typedef enum _PIN_t
{
    PIN_0 = ( uint8_t ) 0 ,
    PIN_1 = ( uint8_t ) 1 ,
    PIN_2 = ( uint8_t ) 2 ,
    PIN_3 = ( uint8_t ) 3 ,
    PIN_4 = ( uint8_t ) 4 ,
    PIN_5 = ( uint8_t ) 5 ,
    PIN_6 = ( uint8_t ) 6 ,
    PIN_7 = ( uint8_t ) 7 ,
    NUM_OF_PINS_PER_PORT
} PIN_t;
typedef enum _DIRECTION_t
{
    DIRECTION_INPUT = ( uint8_t ) 0 ,
    DIRECTION_OUTPUT = ( uint8_t ) 1
} DIRECTION_t;
typedef enum _PIN_STATE_t
{
    PIN_STATE_LOW = ( uint8_t ) 0 ,
    PIN_STATE_HIGH = ( uint8_t ) 1 ,
    PIN_STATE_NOT_CARE = ( uint8_t ) 2
} PIN_STATE_t;
typedef enum _RESISTOR_t
{
    RESISTOR_OPEN = ( uint8_t ) 0 ,
    RESISTOR_PULL_UP = ( uint8_t ) 1 ,
    RESISTOR_NOT_CARE = ( uint8_t ) 2
} RESISTOR_t;
typedef struct _DIO_CNF_t
{
    PORT_t port;
    PIN_t pin;
    DIRECTION_t dir;
    PIN_STATE_t initial;
    RESISTOR_t res;
} DIO_CNF_t;
extern DIO_CNF_t DIO_inital_cfg_arr[( uint8_t ) NUM_OF_PINS];
#endif
