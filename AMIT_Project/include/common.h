#ifndef AMIT_PROJECT_COMMON_H_
#define AMIT_PROJECT_COMMON_H_
#include "Std_Types.h"
typedef enum _BIT_STATE_t
{
    BIT_STATE_CLEARED = ( uint8_t ) 0 ,
    BIT_STATE_SET = ( uint8_t ) 1
} BIT_STATE;
typedef enum _LOGIC_STATE_t
{
    LOGIC_STATE_LOW = ( uint8_t ) 0 ,
    LOGIC_STATE_HIGH = ( uint8_t ) 1 ,
} LOGIC_STATE_t;
typedef enum _INT_STATE_t
{
    INT_STATE_DISABLED = ( uint8_t ) 0 ,
    INT_STATE_ENABLED = ( uint8_t ) 1
} INT_STATE_t;
typedef enum _FLAG_STATE_t
{
    FLAG_STATE_CLEARED = ( uint8_t ) 0 ,
    FLAG_STATE_SET = ( uint8_t ) 1
} FLAG_STATE_t;
#endif
