#include <avr/io.h>
#include "io_extras.h"
#include <avr/wdt.h>
#include "bit_helpers.h"
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
WTCHDG_PRESCALLER_t WTCHDG_getPrescaller ( void )
{
    return ( WTCHDG_PRESCALLER_t ) READ_BITS_AND_SHIFT ( WDTCR , BIT_MASK ( WDP2 ) | BIT_MASK ( WDP1 ) | BIT_MASK ( WDP0 ) , WDP0 );
}
void WTCHDG_enable ( void )
{
    SET_BIT ( WDTCR , WDE );
}
void WTCHDG_disable ( void )
{
    /* reset WDT */
    wdt_reset ();
    /* Write logical one to WDTOE and WDE */
    WDTCR |= ( 0x01 << WDTOE ) | ( 0x01 << WDE );
    /* Turn off WDT */
    WDTCR = 0x00;
}
void WTCHDG_reset ( void )
{
    wdt_reset ();
}
