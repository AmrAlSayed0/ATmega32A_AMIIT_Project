#include <avr/sleep.h>
#include "bit_helpers.h"
#include "SLEEP_private.h"
#include "SLEEP_config.h"
#include "SLEEP.h"
void SLEEP_enable ( void )
{
    SET_BIT ( MCUCR , SE );
}
void SLEEP_disable ( void )
{
    CLEAR_BIT ( MCUCR , SE );
}
void SLEEP_sleep ( void )
{
    sleep_mode ();
}
SLEEP_STD_ERR_t SLEEP_setMode ( SLEEP_MODE_t mode )
{
    SLEEP_STD_ERR_t opResult = SLEEP_OK;
    switch ( mode )
    {
        case SLEEP_MOD_IDLE :
        case SLEEP_MOD_ADC :
        case SLEEP_MOD_PWR_DOWN :
        case SLEEP_MOD_PWR_SAVE :
        case SLEEP_MOD_STANDBY :
        case SLEEP_MOD_EXT_STANDBY :
            REPLACE_BITS ( MCUCR , ( ( uint8_t ) mode ) << SM0 , BIT_MASK3 ( SM2 , SM1 , SM0 ) );
            break;
        default:
            opResult = SLEEP_ERR_MODE;
    }
    return opResult;
}
SLEEP_MODE_t SLEEP_getMode ( void )
{
    return ( SLEEP_MODE_t ) READ_BITS_AND_SHIFT ( MCUCR , BIT_MASK3 ( SM2 , SM1 , SM0 ) , SM0 );
}
