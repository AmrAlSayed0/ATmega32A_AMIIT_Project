#include <avr/io.h>
#include <avr/interrupt.h>
#include "io_extras.h"
#include "BitHelpers.h"
#include "CTRL_private.h"
#include "CTRL_config.h"
#include "CTRL.h"
#define MAX_STACK_POINTER_VALUE ( ( uint16_t ) 0x7FF )
INT_STATE_t CTRL_getGlobalInterruptState ( void )
{
    return ( INT_STATE_t ) READ_BIT ( SREG , SREG_I );
}
CTRL_STD_ERR_t CTRL_setGlobalInterruptState ( INT_STATE_t interruptState )
{
    CTRL_STD_ERR_t opResult = CTRL_OK;
    switch ( interruptState )
    {
        case INT_STATE_ENABLED :
            sei ();
            break;
        case INT_STATE_DISABLED :
            cli ();
            break;
        default:
            opResult = CTRL_ERR_INTERRUPT;
    }
    return opResult;
}
CTRL_STD_ERR_t CTRL_getStatusRegisterFlag ( STATUS_FLAG_t statusFlagToRead , FLAG_STATE_t* flagState )
{
    CTRL_STD_ERR_t opResult = CTRL_OK;
    switch ( statusFlagToRead )
    {
        case STATUS_FLAG_CARRY :
        case STATUS_FLAG_ZERO :
        case STATUS_FLAG_NEGATIVE :
        case STATUS_FLAG_OVERFLOW :
        case STATUS_FLAG_SIGN_BIT :
        case STATUS_FLAG_HALF_CARRY :
        case STATUS_FLAG_BIT_COPY_STORAGE :
        case STATUS_FLAG_GLOBAL_INTERRUPT :
            *flagState = ( FLAG_STATE_t ) READ_BIT ( SREG , ( uint8_t ) statusFlagToRead );
            break;
        default:
            opResult = CTRL_ERR_STATUS_FLAG;
    }
    return opResult;
}
CTRL_STD_ERR_t CTRL_setStatusRegisterFlag ( STATUS_FLAG_t statusFlagToWrite , FLAG_STATE_t flagState )
{
    CTRL_STD_ERR_t opResult = CTRL_OK;
    switch ( statusFlagToWrite )
    {
        case STATUS_FLAG_CARRY :
        case STATUS_FLAG_ZERO :
        case STATUS_FLAG_NEGATIVE :
        case STATUS_FLAG_OVERFLOW :
        case STATUS_FLAG_SIGN_BIT :
        case STATUS_FLAG_HALF_CARRY :
        case STATUS_FLAG_BIT_COPY_STORAGE :
            switch ( flagState )
            {
                case FLAG_STATE_CLEARED :
                case FLAG_STATE_SET :
                    REPLACE_BIT ( SREG , ( uint8_t ) statusFlagToWrite , ( uint8_t ) flagState );
                    break;
                default:
                    opResult = CTRL_ERR_FLAG_STATE;
            }
            break;
        case STATUS_FLAG_GLOBAL_INTERRUPT :
            switch ( flagState )
            {
                case FLAG_STATE_CLEARED :
                    cli ();
                    break;
                case FLAG_STATE_SET :
                    sei ();
                    break;
                default:
                    opResult = CTRL_ERR_FLAG_STATE;
            }
            break;
        default:
            opResult = CTRL_ERR_STATUS_FLAG;
    }
    return opResult;
}
uint16_t CTRL_getStackPointer ( void )
{
    return SP;
}
CTRL_STD_ERR_t CTRL_setStackPointer ( uint16_t stackPointerValue )
{
    CTRL_STD_ERR_t opResult = CTRL_OK;
    if ( stackPointerValue <= MAX_STACK_POINTER_VALUE )
    {
        SP = stackPointerValue;
    }
    else
    {
        opResult = CTRL_ERR_STACK_POINTER;
    }
    return opResult;
}
