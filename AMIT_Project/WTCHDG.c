#include <avr/io.h>
#include <avr/wdt.h>
#include "BitHelpers.h"
#include "WTCHDG_private.h"
#include "WTCHDG_config.h"
#include "WTCHDG.h"
WTCHDG_STD_ERR_t WTCHDG_setPrescaller ( WTCHDG_PRESCALLER_t prescSetting )
{
    WTCHDG_STD_ERR_t opResult = WTCHDG_OK;
    #pragma GCC diagnostic ignored "-Wtype-limits"
    if ( ( uint8_t ) prescSetting >= ( uint8_t ) WTCHDG_PRESCALLER_16K && ( uint8_t ) prescSetting < ( uint8_t ) NUM_OF_WTCHDG_PRESCALLERS )
    {
        REPLACE_BITS ( WDTCR , ( ( uint8_t ) prescSetting ) << WDP0 , BIT_MASK ( WDP2 ) | BIT_MASK ( WDP1 ) | BIT_MASK ( WDP0 ) );
    }
    else
    {
        opResult = WTCHDG_ERR_PRESC;
    }
    return opResult;
}
WTCHDG_PRESCALLER_t WTCHDG_getPrescaller ()
{
    return ( WTCHDG_PRESCALLER_t ) READ_BITS_AND_SHIFT ( WDTCR , BIT_MASK ( WDP2 ) | BIT_MASK ( WDP1 ) | BIT_MASK ( WDP0 ) , WDP0 );
}
void WTCHDG_enable ()
{
    SET_BIT ( WDTCR , WDE );
}
void WTCHDG_disable ()
{
    /* reset WDT */
    wdt_reset ();
    /* Write logical one to WDTOE and WDE */
    WDTCR |= ( 1 << WDTOE ) | ( 1 << WDE );
    /* Turn off WDT */
    WDTCR = 0x00;
}
void WTCHDG_reset ()
{
    wdt_reset ();
}
