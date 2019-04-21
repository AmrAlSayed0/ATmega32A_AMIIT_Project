#ifndef AMIT_PROJECT_CTRL_H_
#define AMIT_PROJECT_CTRL_H_
#include "std_types.h"
#include "common.h"
typedef enum _STATUS_FLAG_t
{
    STATUS_FLAG_CARRY = ( uint8_t ) 0 ,
    STATUS_FLAG_ZERO = ( uint8_t ) 1 ,
    STATUS_FLAG_NEGATIVE = ( uint8_t ) 2 ,
    STATUS_FLAG_OVERFLOW = ( uint8_t ) 3 ,
    STATUS_FLAG_SIGN_BIT = ( uint8_t ) 4 ,
    STATUS_FLAG_HALF_CARRY = ( uint8_t ) 5 ,
    STATUS_FLAG_BIT_COPY_STORAGE = ( uint8_t ) 6 ,
    STATUS_FLAG_GLOBAL_INTERRUPT = ( uint8_t ) 7
} STATUS_FLAG_t;
typedef enum _CTRL_STD_ERR_t
{
    CTRL_OK = ( uint8_t ) 0 ,
    CTRL_ERR_INTERRUPT = ( uint8_t ) 1 ,
    CTRL_ERR_STATUS_FLAG = ( uint8_t ) 2 ,
    CTRL_ERR_FLAG_STATE = ( uint8_t ) 3 ,
    CTRL_ERR_STACK_POINTER = ( uint8_t ) 4
} CTRL_STD_ERR_t;
INT_STATE_t CTRL_getGlobalInterruptState ( void );
CTRL_STD_ERR_t CTRL_setGlobalInterruptState ( INT_STATE_t interruptState );
CTRL_STD_ERR_t CTRL_getStatusRegisterFlag ( STATUS_FLAG_t statusFlagToRead , FLAG_STATE_t* flagState );
CTRL_STD_ERR_t CTRL_setStatusRegisterFlag ( STATUS_FLAG_t statusFlagToWrite , FLAG_STATE_t flagState );
uint16_t CTRL_getStackPointer ( void );
CTRL_STD_ERR_t CTRL_setStackPointer ( uint16_t stackPointerValue );
#endif
