#include <avr/io.h>
#include <avr/interrupt.h>
#include "io_extras.h"
#include "bit_helpers.h"
#include "EXT_INT_private.h"
#include "EXT_INT_config.h"
#include "EXT_INT.h"
interuptFunc int0VectorFunc = NULL_PTR;
interuptFunc int1VectorFunc = NULL_PTR;
interuptFunc int2VectorFunc = NULL_PTR;
EXT_INT_STD_ERR_t EXT_INT_setSense ( EXT_INT_t intToSet , INT_SENSE_t senseToSet )
{
    EXT_INT_STD_ERR_t opResult = EXT_INT_OK;
    switch ( intToSet )
    {
        case EXT_INT_0 :
        {
            uint8_t mask = ( uint8_t ) BIT_MASK2 ( ISC01 , ISC00 );
            switch ( senseToSet )
            {
                case INT_SENSE_LOW :
                case INT_SENSE_CHANGE :
                case INT_SENSE_FAILING :
                case INT_SENSE_RISING :
                    REPLACE_BITS ( MCUCR , ( uint8_t ) senseToSet , mask );
                    break;
                default:
                    opResult = EXT_INT_ERR_SENSE;
            }
        }
            break;
        case EXT_INT_1 :
        {
            uint8_t mask = ( uint8_t ) BIT_MASK2 ( ISC11 , ISC10 );
            switch ( senseToSet )
            {
                case INT_SENSE_LOW :
                case INT_SENSE_CHANGE :
                case INT_SENSE_FAILING :
                case INT_SENSE_RISING :
                    REPLACE_BITS ( MCUCR , ( uint8_t ) senseToSet , mask );
                    break;
                default:
                    opResult = EXT_INT_ERR_SENSE;
            }
        }
            break;
        case EXT_INT_2 :
            switch ( senseToSet )
            {
                case INT_SENSE_FAILING :
                    SET_BIT ( MCUCSR , ISC2 );
                    break;
                case INT_SENSE_RISING :
                    CLEAR_BIT ( MCUCSR , ISC2 );
                    break;
                case INT_SENSE_LOW :
                case INT_SENSE_CHANGE :
                default:
                    opResult = EXT_INT_ERR_SENSE;
            }
            break;
        default:
            opResult = EXT_INT_ERR_INT;
    }
    return opResult;
}
EXT_INT_STD_ERR_t EXT_INT_getSense ( EXT_INT_t intToGet , INT_SENSE_t* outputSense )
{
    EXT_INT_STD_ERR_t opResult = EXT_INT_OK;
    switch ( intToGet )
    {
        case EXT_INT_0 :
            *outputSense = ( INT_SENSE_t ) READ_BITS_AND_SHIFT ( MCUCR , BIT_MASK2 ( ISC01 , ISC00 ) , ISC00 );
            break;
        case EXT_INT_1 :
            *outputSense = ( INT_SENSE_t ) READ_BITS_AND_SHIFT ( MCUCR , BIT_MASK2 ( ISC11 , ISC10 ) , ISC10 );
            break;
        case EXT_INT_2 :
            *outputSense = READ_BIT ( MCUCSR , ISC2 ) == 0 ?
                           INT_SENSE_FAILING :
                           INT_SENSE_RISING;
            break;
        default:
            opResult = EXT_INT_ERR_INT;
    }
    return opResult;
}
EXT_INT_STD_ERR_t EXT_INT_setState ( EXT_INT_t intToSet )
{
    EXT_INT_STD_ERR_t opResult = EXT_INT_OK;
    switch ( intToSet )
    {
        case EXT_INT_0 :
            SET_BIT ( GICR , INT0 );
            break;
        case EXT_INT_1 :
            SET_BIT ( GICR , INT1 );
            break;
        case EXT_INT_2 :
            SET_BIT ( GICR , INT2 );
            break;
        default:
            opResult = EXT_INT_ERR_INT;
    }
    return opResult;
}
EXT_INT_STD_ERR_t EXT_INT_clearState ( EXT_INT_t intToSet )
{
    EXT_INT_STD_ERR_t opResult = EXT_INT_OK;
    switch ( intToSet )
    {
        case EXT_INT_0 :
            CLEAR_BIT ( GICR , INT0 );
            break;
        case EXT_INT_1 :
            CLEAR_BIT ( GICR , INT1 );
            break;
        case EXT_INT_2 :
            CLEAR_BIT ( GICR , INT2 );
            break;
        default:
            opResult = EXT_INT_ERR_INT;
    }
    return opResult;
}
EXT_INT_STD_ERR_t EXT_INT_getState ( EXT_INT_t intToSet , INT_STATE_t* outputState )
{
    EXT_INT_STD_ERR_t opResult = EXT_INT_OK;
    switch ( intToSet )
    {
        case EXT_INT_0 :
            *outputState = ( INT_STATE_t ) READ_BIT ( GICR , INT0 );
            break;
        case EXT_INT_1 :
            *outputState = ( INT_STATE_t ) READ_BIT ( GICR , INT1 );
            break;
        case EXT_INT_2 :
            *outputState = ( INT_STATE_t ) READ_BIT ( GICR , INT2 );
            break;
        default:
            opResult = EXT_INT_ERR_INT;
    }
    return opResult;
}
EXT_INT_STD_ERR_t EXT_INT_clearFlag ( EXT_INT_t intToSet )
{
    EXT_INT_STD_ERR_t opResult = EXT_INT_OK;
    switch ( intToSet )
    {
        case EXT_INT_0 :
            SET_BIT ( GIFR , INTF0 );
            break;
        case EXT_INT_1 :
            SET_BIT ( GIFR , INTF1 );
            break;
        case EXT_INT_2 :
            SET_BIT ( GIFR , INTF2 );
            break;
        default:
            opResult = EXT_INT_ERR_INT;
    }
    return opResult;
}
EXT_INT_STD_ERR_t EXT_INT_getFlag ( EXT_INT_t intToSet , FLAG_STATE_t* outputFlagState )
{
    EXT_INT_STD_ERR_t opResult = EXT_INT_OK;
    switch ( intToSet )
    {
        case EXT_INT_0 :
            *outputFlagState = ( FLAG_STATE_t ) READ_BIT ( GIFR , INTF0 );
            break;
        case EXT_INT_1 :
            *outputFlagState = ( FLAG_STATE_t ) READ_BIT ( GIFR , INTF1 );
            break;
        case EXT_INT_2 :
            *outputFlagState = ( FLAG_STATE_t ) READ_BIT ( GIFR , INTF2 );
            break;
        default:
            opResult = EXT_INT_ERR_INT;
    }
    return opResult;
}
EXT_INT_STD_ERR_t EXT_INT_getInterruptFunction ( EXT_INT_t intToSet , interuptFunc* functionToExcute )
{
    EXT_INT_STD_ERR_t opResult = EXT_INT_OK;
    switch ( intToSet )
    {
        case EXT_INT_0 :
        *functionToExcute = int0VectorFunc;
        break;
        case EXT_INT_1 :
        *functionToExcute = int1VectorFunc;
        break;
        case EXT_INT_2 :
        *functionToExcute = int2VectorFunc;
        break;
        default:
        opResult = EXT_INT_ERR_INT;
    }
    return opResult;
}
EXT_INT_STD_ERR_t EXT_INT_setInterruptFunction ( EXT_INT_t intToSet , interuptFunc functionToExcute )
{
    EXT_INT_STD_ERR_t opResult = EXT_INT_OK;
    switch ( intToSet )
    {
        case EXT_INT_0 :
        int0VectorFunc = functionToExcute;
        break;
        case EXT_INT_1 :
        int1VectorFunc = functionToExcute;
        break;
        case EXT_INT_2 :
        int2VectorFunc = functionToExcute;
        break;
        default:
        opResult = EXT_INT_ERR_INT;
    }
    return opResult;
}
ISR ( INT0_vect )
{
    if ( int0VectorFunc != NULL_PTR )
    {
        int0VectorFunc ();
    }
}
ISR ( INT1_vect )
{
    if ( int1VectorFunc != NULL_PTR )
    {
        int1VectorFunc ();
    }
}
ISR ( INT2_vect )
{
    if ( int2VectorFunc != NULL_PTR )
    {
        int2VectorFunc ();
    }
}
