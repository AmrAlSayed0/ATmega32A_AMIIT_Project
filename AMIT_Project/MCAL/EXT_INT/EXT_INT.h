#ifndef AMIT_PROJECT_EXT_INT_H_
#define AMIT_PROJECT_EXT_INT_H_
#include "common.h"
typedef enum _EXT_INT_t
{
    EXT_INT_0 = ( uint8_t ) 0 ,
    EXT_INT_1 = ( uint8_t ) 1 ,
    EXT_INT_2 = ( uint8_t ) 2
} EXT_INT_t;
typedef enum _INT_SENSE_t
{
    INT_SENSE_LOW = ( uint8_t ) 0 ,
    INT_SENSE_CHANGE = ( uint8_t ) 1 ,
    INT_SENSE_FAILING = ( uint8_t ) 2 ,
    INT_SENSE_RISING = ( uint8_t ) 3
} INT_SENSE_t;
typedef enum _EXT_INT_STD_ERR_t
{
    EXT_INT_OK = ( uint8_t ) 0 ,
    EXT_INT_ERR_INT = ( uint8_t ) 1 ,
    EXT_INT_ERR_SENSE = ( uint8_t ) 2
} EXT_INT_STD_ERR_t;
EXT_INT_STD_ERR_t EXT_INT_setSense ( EXT_INT_t intToSet , INT_SENSE_t senseToSet );
EXT_INT_STD_ERR_t EXT_INT_getSense ( EXT_INT_t intToGet , INT_SENSE_t* outputSense );
EXT_INT_STD_ERR_t EXT_INT_setState ( EXT_INT_t intToSet );
EXT_INT_STD_ERR_t EXT_INT_clearState ( EXT_INT_t intToSet );
EXT_INT_STD_ERR_t EXT_INT_getState ( EXT_INT_t intToSet , INT_STATE_t* outputState );
EXT_INT_STD_ERR_t EXT_INT_clearFlag ( EXT_INT_t intToSet );
EXT_INT_STD_ERR_t EXT_INT_getFlag ( EXT_INT_t intToSet , FLAG_STATE_t* outputFlagState );
EXT_INT_STD_ERR_t EXT_INT_getInterruptFunction ( EXT_INT_t intToSet , interuptFunc* functionToExcute );
EXT_INT_STD_ERR_t EXT_INT_setInterruptFunction ( EXT_INT_t intToSet , interuptFunc functionToExcute );
#endif
