#include <avr/io.h>
#include "io_extras.h"
#include "BitHelpers.h"
#include "Std_Types.h"
#include "DIO_private.h"
#include "DIO.h"
DIO_STD_ERR_t DIO_init ( void )
{
    DIO_STD_ERR_t opResult = DIO_OK;
    uint8_t portAValue = ( uint8_t ) 0;
    uint8_t portBValue = ( uint8_t ) 0;
    uint8_t portCValue = ( uint8_t ) 0;
    uint8_t portDValue = ( uint8_t ) 0;
    uint8_t ddrAValue = ( uint8_t ) 0;
    uint8_t ddrBValue = ( uint8_t ) 0;
    uint8_t ddrCValue = ( uint8_t ) 0;
    uint8_t ddrDValue = ( uint8_t ) 0;
    if ( ( uint8_t ) NUM_OF_PINS <= MAX_NUM_OF_PINS )
    {
        uint8_t i;
        for ( i = ( uint8_t ) 0; i < ( uint8_t ) NUM_OF_PINS; i++ )
        {
            #pragma GCC diagnostic ignored "-Wtype-limits"
            if ( ( uint8_t ) DIO_inital_cfg_arr[ i ].pin >= ( uint8_t ) PIN_0 && ( uint8_t ) DIO_inital_cfg_arr[ i ].pin < ( uint8_t ) NUM_OF_PINS_PER_PORT )
            {
                switch ( DIO_inital_cfg_arr[ i ].port )
                {
                    case PORT_A :
                        switch ( DIO_inital_cfg_arr[ i ].dir )
                        {
                            case DIRECTION_INPUT :
                                CLEAR_BIT ( ddrAValue , ( uint8_t ) DIO_inital_cfg_arr[ i ].pin );
                                switch ( DIO_inital_cfg_arr[ i ].res )
                                {
                                    case RESISTOR_PULL_UP :
                                        SET_BIT ( portAValue , ( uint8_t ) DIO_inital_cfg_arr[ i ].pin );
                                        break;
                                    case RESISTOR_OPEN :
                                        CLEAR_BIT ( portAValue , ( uint8_t ) DIO_inital_cfg_arr[ i ].pin );
                                        break;
                                    case RESISTOR_NOT_CARE :
                                        break;
                                    default:
                                        opResult = DIO_ERR_RES;
                                }
                                break;
                            case DIRECTION_OUTPUT :
                                SET_BIT ( ddrAValue , ( uint8_t ) DIO_inital_cfg_arr[ i ].pin );
                                switch ( DIO_inital_cfg_arr[ i ].pinState )
                                {
                                    case PIN_STATE_HIGH :
                                        SET_BIT ( portAValue , ( uint8_t ) DIO_inital_cfg_arr[ i ].pin );
                                        break;
                                    case PIN_STATE_LOW :
                                        CLEAR_BIT ( portAValue , ( uint8_t ) DIO_inital_cfg_arr[ i ].pin );
                                        break;
                                    case PIN_STATE_NOT_CARE :
                                        break;
                                    default:
                                        opResult = DIO_ERR_STATE;
                                }
                                break;
                            default:
                                opResult = DIO_ERR_DIR;
                        }
                        break;
                    case PORT_B :
                        switch ( DIO_inital_cfg_arr[ i ].dir )
                        {
                            case DIRECTION_INPUT :
                                CLEAR_BIT ( ddrBValue , ( uint8_t ) DIO_inital_cfg_arr[ i ].pin );
                                switch ( DIO_inital_cfg_arr[ i ].res )
                                {
                                    case RESISTOR_PULL_UP :
                                        SET_BIT ( portBValue , ( uint8_t ) DIO_inital_cfg_arr[ i ].pin );
                                        break;
                                    case RESISTOR_OPEN :
                                        CLEAR_BIT ( portBValue , ( uint8_t ) DIO_inital_cfg_arr[ i ].pin );
                                        break;
                                    case RESISTOR_NOT_CARE :
                                        break;
                                    default:
                                        opResult = DIO_ERR_RES;
                                }
                                break;
                            case DIRECTION_OUTPUT :
                                SET_BIT ( ddrBValue , ( uint8_t ) DIO_inital_cfg_arr[ i ].pin );
                                switch ( DIO_inital_cfg_arr[ i ].pinState )
                                {
                                    case PIN_STATE_HIGH :
                                        SET_BIT ( portBValue , ( uint8_t ) DIO_inital_cfg_arr[ i ].pin );
                                        break;
                                    case PIN_STATE_LOW :
                                        CLEAR_BIT ( portBValue , ( uint8_t ) DIO_inital_cfg_arr[ i ].pin );
                                        break;
                                    case PIN_STATE_NOT_CARE :
                                        break;
                                    default:
                                        opResult = DIO_ERR_STATE;
                                }
                                break;
                            default:
                                opResult = DIO_ERR_DIR;
                        }
                        break;
                    case PORT_C :
                        switch ( DIO_inital_cfg_arr[ i ].dir )
                        {
                            case DIRECTION_INPUT :
                                CLEAR_BIT ( ddrCValue , ( uint8_t ) DIO_inital_cfg_arr[ i ].pin );
                                switch ( DIO_inital_cfg_arr[ i ].res )
                                {
                                    case RESISTOR_PULL_UP :
                                        SET_BIT ( portCValue , ( uint8_t ) DIO_inital_cfg_arr[ i ].pin );
                                        break;
                                    case RESISTOR_OPEN :
                                        CLEAR_BIT ( portCValue , ( uint8_t ) DIO_inital_cfg_arr[ i ].pin );
                                        break;
                                    case RESISTOR_NOT_CARE :
                                        break;
                                    default:
                                        opResult = DIO_ERR_RES;
                                }
                                break;
                            case DIRECTION_OUTPUT :
                                SET_BIT ( ddrCValue , ( uint8_t ) DIO_inital_cfg_arr[ i ].pin );
                                switch ( DIO_inital_cfg_arr[ i ].pinState )
                                {
                                    case PIN_STATE_HIGH :
                                        SET_BIT ( portCValue , ( uint8_t ) DIO_inital_cfg_arr[ i ].pin );
                                        break;
                                    case PIN_STATE_LOW :
                                        CLEAR_BIT ( portCValue , ( uint8_t ) DIO_inital_cfg_arr[ i ].pin );
                                        break;
                                    case PIN_STATE_NOT_CARE :
                                        break;
                                    default:
                                        opResult = DIO_ERR_STATE;
                                }
                                break;
                            default:
                                opResult = DIO_ERR_DIR;
                        }
                        break;
                    case PORT_D :
                        switch ( DIO_inital_cfg_arr[ i ].dir )
                        {
                            case DIRECTION_INPUT :
                                CLEAR_BIT ( ddrDValue , ( uint8_t ) DIO_inital_cfg_arr[ i ].pin );
                                switch ( DIO_inital_cfg_arr[ i ].res )
                                {
                                    case RESISTOR_PULL_UP :
                                        SET_BIT ( portDValue , ( uint8_t ) DIO_inital_cfg_arr[ i ].pin );
                                        break;
                                    case RESISTOR_OPEN :
                                        CLEAR_BIT ( portDValue , ( uint8_t ) DIO_inital_cfg_arr[ i ].pin );
                                        break;
                                    case RESISTOR_NOT_CARE :
                                        break;
                                    default:
                                        opResult = DIO_ERR_RES;
                                }
                                break;
                            case DIRECTION_OUTPUT :
                                SET_BIT ( ddrDValue , DIO_inital_cfg_arr[ i ].pin );
                                switch ( DIO_inital_cfg_arr[ i ].pinState )
                                {
                                    case PIN_STATE_HIGH :
                                        SET_BIT ( portDValue , ( uint8_t ) DIO_inital_cfg_arr[ i ].pin );
                                        break;
                                    case PIN_STATE_LOW :
                                        CLEAR_BIT ( portDValue , ( uint8_t ) DIO_inital_cfg_arr[ i ].pin );
                                        break;
                                    case PIN_STATE_NOT_CARE :
                                        break;
                                    default:
                                        opResult = DIO_ERR_STATE;
                                }
                                break;
                            default:
                                opResult = DIO_ERR_DIR;
                        }
                        break;
                    default:
                        opResult = DIO_ERR_PORT;
                }
            }
            else
            {
                opResult = DIO_ERR_PIN_NUM;
            }
        }
    }
    else
    {
        opResult = DIO_ERR_NUM_OF_PINS;
    }
    if ( opResult == DIO_OK )
    {
        DDRA = ddrAValue;
        DDRB = ddrBValue;
        DDRC = ddrCValue;
        DDRD = ddrDValue;
        PORTA = portAValue;
        PORTB = portBValue;
        PORTC = portCValue;
        PORTD = portDValue;
    }
    return opResult;
}
DIO_STD_ERR_t DIO_getConfig ( DIO_CNF_t* cnfg )
{
    DIO_STD_ERR_t opResult = DIO_OK;
    #pragma GCC diagnostic ignored "-Wtype-limits"
    if ( ( uint8_t ) cnfg->pin >= ( uint8_t ) PIN_0 && ( uint8_t ) cnfg->pin < ( uint8_t ) NUM_OF_PINS_PER_PORT )
    {
        switch ( cnfg->port )
        {
            case PORT_A :
                cnfg->dir = ( DIRECTION_t ) READ_BIT ( DDRA , ( uint8_t ) cnfg->pin );
                switch ( cnfg->dir )
                {
                    case DIRECTION_INPUT :
                        cnfg->res = ( RESISTOR_t ) READ_BIT ( PORTA , ( uint8_t ) cnfg->pin );
                        cnfg->pinState = PIN_STATE_NOT_CARE;
                        break;
                    case DIRECTION_OUTPUT :
                        cnfg->pinState = READ_BIT ( PORTA , ( uint8_t ) cnfg->pin );
                        cnfg->res = RESISTOR_NOT_CARE;
                        break;
                    default:;
                }
                break;
            case PORT_B :
                cnfg->dir = ( DIRECTION_t ) READ_BIT ( DDRB , ( uint8_t ) cnfg->pin );
                switch ( cnfg->dir )
                {
                    case DIRECTION_INPUT :
                        cnfg->res = ( RESISTOR_t ) READ_BIT ( PORTB , ( uint8_t ) cnfg->pin );
                        cnfg->pinState = PIN_STATE_NOT_CARE;
                        break;
                    case DIRECTION_OUTPUT :
                        cnfg->pinState = READ_BIT ( PORTB , ( uint8_t ) cnfg->pin );
                        cnfg->res = RESISTOR_NOT_CARE;
                        break;
                    default:;
                }
                break;
            case PORT_C :
                cnfg->dir = ( DIRECTION_t ) READ_BIT ( DDRC , ( uint8_t ) cnfg->pin );
                switch ( cnfg->dir )
                {
                    case DIRECTION_INPUT :
                        cnfg->res = ( RESISTOR_t ) READ_BIT ( PORTC , ( uint8_t ) cnfg->pin );
                        cnfg->pinState = PIN_STATE_NOT_CARE;
                        break;
                    case DIRECTION_OUTPUT :
                        cnfg->pinState = READ_BIT ( PORTC , ( uint8_t ) cnfg->pin );
                        cnfg->res = RESISTOR_NOT_CARE;
                        break;
                    default:;
                }
                break;
            case PORT_D :
                cnfg->dir = ( DIRECTION_t ) READ_BIT ( DDRD , ( uint8_t ) cnfg->pin );
                switch ( cnfg->dir )
                {
                    case DIRECTION_INPUT :
                        cnfg->res = ( RESISTOR_t ) READ_BIT ( PORTD , ( uint8_t ) cnfg->pin );
                        cnfg->pinState = PIN_STATE_NOT_CARE;
                        break;
                    case DIRECTION_OUTPUT :
                        cnfg->pinState = READ_BIT ( PORTD , ( uint8_t ) cnfg->pin );
                        cnfg->res = RESISTOR_NOT_CARE;
                        break;
                    default:;
                }
                break;
            default:
                opResult = DIO_ERR_PORT;
        }
    }
    else
    {
        opResult = DIO_ERR_PIN_NUM;
    }
    return opResult;
}
DIO_STD_ERR_t DIO_setConfig ( DIO_CNF_t* cnfg )
{
    DIO_STD_ERR_t opResult = DIO_OK;
    #pragma GCC diagnostic ignored "-Wtype-limits"
    if ( ( uint8_t ) cnfg->pin >= ( uint8_t ) PIN_0 && ( uint8_t ) cnfg->pin < ( uint8_t ) NUM_OF_PINS_PER_PORT )
    {
        switch ( cnfg->port )
        {
            case PORT_A :
                switch ( cnfg->dir )
                {
                    case DIRECTION_INPUT :
                        CLEAR_BIT ( DDRA , ( uint8_t ) cnfg->pin );
                        switch ( cnfg->res )
                        {
                            case RESISTOR_PULL_UP :
                                SET_BIT ( PORTA , ( uint8_t ) cnfg->pin );
                                break;
                            case RESISTOR_OPEN :
                                CLEAR_BIT ( PORTA , ( uint8_t ) cnfg->pin );
                                break;
                            case RESISTOR_NOT_CARE :
                                break;
                            default:
                                opResult = DIO_ERR_RES;
                        }
                        break;
                    case DIRECTION_OUTPUT :
                        SET_BIT ( DDRA , ( uint8_t ) cnfg->pin );
                        switch ( cnfg->pinState )
                        {
                            case PIN_STATE_HIGH :
                                SET_BIT ( PORTA , ( uint8_t ) cnfg->pin );
                                break;
                            case PIN_STATE_LOW :
                                CLEAR_BIT ( PORTA , ( uint8_t ) cnfg->pin );
                                break;
                            case PIN_STATE_NOT_CARE :
                                break;
                            default:
                                opResult = DIO_ERR_STATE;
                        }
                        break;
                    default:
                        opResult = DIO_ERR_DIR;
                }
                break;
            case PORT_B :
                switch ( cnfg->dir )
                {
                    case DIRECTION_INPUT :
                        CLEAR_BIT ( DDRB , ( uint8_t ) cnfg->pin );
                        switch ( cnfg->res )
                        {
                            case RESISTOR_PULL_UP :
                                SET_BIT ( PORTB , ( uint8_t ) cnfg->pin );
                                break;
                            case RESISTOR_OPEN :
                                CLEAR_BIT ( PORTB , ( uint8_t ) cnfg->pin );
                                break;
                            case RESISTOR_NOT_CARE :
                                break;
                            default:
                                opResult = DIO_ERR_RES;
                        }
                        break;
                    case DIRECTION_OUTPUT :
                        SET_BIT ( DDRB , ( uint8_t ) cnfg->pin );
                        switch ( cnfg->pinState )
                        {
                            case PIN_STATE_HIGH :
                                SET_BIT ( PORTB , ( uint8_t ) cnfg->pin );
                                break;
                            case PIN_STATE_LOW :
                                CLEAR_BIT ( PORTB , ( uint8_t ) cnfg->pin );
                                break;
                            case PIN_STATE_NOT_CARE :
                                break;
                            default:
                                opResult = DIO_ERR_STATE;
                        }
                        break;
                    default:
                        opResult = DIO_ERR_DIR;
                }
                break;
            case PORT_C :
                switch ( cnfg->dir )
                {
                    case DIRECTION_INPUT :
                        CLEAR_BIT ( DDRC , ( uint8_t ) cnfg->pin );
                        switch ( cnfg->res )
                        {
                            case RESISTOR_PULL_UP :
                                SET_BIT ( PORTC , ( uint8_t ) cnfg->pin );
                                break;
                            case RESISTOR_OPEN :
                                CLEAR_BIT ( PORTC , ( uint8_t ) cnfg->pin );
                                break;
                            case RESISTOR_NOT_CARE :
                                break;
                            default:
                                opResult = DIO_ERR_RES;
                        }
                        break;
                    case DIRECTION_OUTPUT :
                        SET_BIT ( DDRC , ( uint8_t ) cnfg->pin );
                        switch ( cnfg->pinState )
                        {
                            case PIN_STATE_HIGH :
                                SET_BIT ( PORTC , ( uint8_t ) cnfg->pin );
                                break;
                            case PIN_STATE_LOW :
                                CLEAR_BIT ( PORTC , ( uint8_t ) cnfg->pin );
                                break;
                            case PIN_STATE_NOT_CARE :
                                break;
                            default:
                                opResult = DIO_ERR_STATE;
                        }
                        break;
                    default:
                        opResult = DIO_ERR_DIR;
                }
                break;
            case PORT_D :
                switch ( cnfg->dir )
                {
                    case DIRECTION_INPUT :
                        CLEAR_BIT ( DDRD , ( uint8_t ) cnfg->pin );
                        switch ( cnfg->res )
                        {
                            case RESISTOR_PULL_UP :
                                SET_BIT ( PORTD , ( uint8_t ) cnfg->pin );
                                break;
                            case RESISTOR_OPEN :
                                CLEAR_BIT ( PORTD , ( uint8_t ) cnfg->pin );
                                break;
                            case RESISTOR_NOT_CARE :
                                break;
                            default:
                                opResult = DIO_ERR_RES;
                        }
                        break;
                    case DIRECTION_OUTPUT :
                        SET_BIT ( DDRD , cnfg->pin );
                        switch ( cnfg->pinState )
                        {
                            case PIN_STATE_HIGH :
                                SET_BIT ( PORTD , ( uint8_t ) cnfg->pin );
                                break;
                            case PIN_STATE_LOW :
                                CLEAR_BIT ( PORTD , ( uint8_t ) cnfg->pin );
                                break;
                            case PIN_STATE_NOT_CARE :
                                break;
                            default:
                                opResult = DIO_ERR_STATE;
                        }
                        break;
                    default:
                        opResult = DIO_ERR_DIR;
                }
                break;
            default:
                opResult = DIO_ERR_PORT;
        }
    }
    else
    {
        opResult = DIO_ERR_PIN_NUM;
    }
    return opResult;
}
DIO_STD_ERR_t DIO_getDirection ( PORT_t port , PIN_t pin , DIRECTION_t* dir )
{
    DIO_STD_ERR_t opResult = DIO_OK;
    #pragma GCC diagnostic ignored "-Wtype-limits"
    if ( ( uint8_t ) pin >= ( uint8_t ) PIN_0 && ( uint8_t ) pin < ( uint8_t ) NUM_OF_PINS_PER_PORT )
    {
        switch ( port )
        {
            case PORT_A :
                *dir = ( DIRECTION_t ) READ_BIT ( DDRA , ( uint8_t ) pin );
                break;
            case PORT_B :
                *dir = ( DIRECTION_t ) READ_BIT ( DDRB , ( uint8_t ) pin );
                break;
            case PORT_C :
                *dir = ( DIRECTION_t ) READ_BIT ( DDRC , ( uint8_t ) pin );
                break;
            case PORT_D :
                *dir = ( DIRECTION_t ) READ_BIT ( DDRD , ( uint8_t ) pin );
                break;
            default:
                opResult = DIO_ERR_PORT;
        }
    }
    else
    {
        opResult = DIO_ERR_PIN_NUM;
    }
    return opResult;
}
DIO_STD_ERR_t DIO_setDirection ( PORT_t port , PIN_t pin , DIRECTION_t dir )
{
    DIO_STD_ERR_t opResult = DIO_OK;
    #pragma GCC diagnostic ignored "-Wtype-limits"
    if ( ( uint8_t ) pin >= ( uint8_t ) PIN_0 && ( uint8_t ) pin < ( uint8_t ) NUM_OF_PINS_PER_PORT )
    {
        switch ( port )
        {
            case PORT_A :
                switch ( dir )
                {
                    case DIRECTION_OUTPUT :
                        SET_BIT ( DDRA , ( uint8_t ) pin );
                        break;
                    case DIRECTION_INPUT :
                        CLEAR_BIT ( DDRA , ( uint8_t ) pin );
                        break;
                    default:
                        opResult = DIO_ERR_DIR;
                }
                break;
            case PORT_B :
                switch ( dir )
                {
                    case DIRECTION_OUTPUT :
                        SET_BIT ( DDRB , ( uint8_t ) pin );
                        break;
                    case DIRECTION_INPUT :
                        CLEAR_BIT ( DDRB , ( uint8_t ) pin );
                        break;
                    default:
                        opResult = DIO_ERR_DIR;
                }
                break;
            case PORT_C :
                switch ( dir )
                {
                    case DIRECTION_OUTPUT :
                        SET_BIT ( DDRC , ( uint8_t ) pin );
                        break;
                    case DIRECTION_INPUT :
                        CLEAR_BIT ( DDRC , ( uint8_t ) pin );
                        break;
                    default:
                        opResult = DIO_ERR_DIR;
                }
                break;
            case PORT_D :
                switch ( dir )
                {
                    case DIRECTION_OUTPUT :
                        SET_BIT ( DDRD , ( uint8_t ) pin );
                        break;
                    case DIRECTION_INPUT :
                        CLEAR_BIT ( DDRD , ( uint8_t ) pin );
                        break;
                    default:
                        opResult = DIO_ERR_DIR;
                }
                break;
            default:
                opResult = DIO_ERR_PORT;
        }
    }
    else
    {
        opResult = DIO_ERR_PIN_NUM;
    }
    return opResult;
}
DIO_STD_ERR_t DIO_getResistor ( PORT_t port , PIN_t pin , RESISTOR_t* resistor )
{
    DIO_STD_ERR_t opResult = DIO_OK;
    #pragma GCC diagnostic ignored "-Wtype-limits"
    if ( ( uint8_t ) pin >= ( uint8_t ) PIN_0 && ( uint8_t ) pin < ( uint8_t ) NUM_OF_PINS_PER_PORT )
    {
        switch ( port )
        {
            case PORT_A :
                if ( READ_BIT ( DDRA , ( uint8_t ) pin ) == ( uint8_t ) DIRECTION_INPUT )
                {
                    *resistor = ( RESISTOR_t ) READ_BIT ( PORTA , ( uint8_t ) pin );
                }
                else
                {
                    opResult = DIO_ERR_DIR;
                }
                break;
            case PORT_B :
                if ( READ_BIT ( DDRB , ( uint8_t ) pin ) == ( uint8_t ) DIRECTION_INPUT )
                {
                    *resistor = ( RESISTOR_t ) READ_BIT ( PORTB , ( uint8_t ) pin );
                }
                else
                {
                    opResult = DIO_ERR_DIR;
                }
                break;
            case PORT_C :
                if ( READ_BIT ( DDRC , ( uint8_t ) pin ) == ( uint8_t ) DIRECTION_INPUT )
                {
                    *resistor = ( RESISTOR_t ) READ_BIT ( PORTC , ( uint8_t ) pin );
                }
                else
                {
                    opResult = DIO_ERR_DIR;
                }
                break;
            case PORT_D :
                if ( READ_BIT ( DDRD , ( uint8_t ) pin ) == ( uint8_t ) DIRECTION_INPUT )
                {
                    *resistor = ( RESISTOR_t ) READ_BIT ( PORTD , ( uint8_t ) pin );
                }
                else
                {
                    opResult = DIO_ERR_DIR;
                }
                break;
            default:
                opResult = DIO_ERR_PORT;
        }
    }
    else
    {
        opResult = DIO_ERR_PIN_NUM;
    }
    return opResult;
}
DIO_STD_ERR_t DIO_setResistor ( PORT_t port , PIN_t pin , RESISTOR_t resistor )
{
    DIO_STD_ERR_t opResult = DIO_OK;
    #pragma GCC diagnostic ignored "-Wtype-limits"
    if ( ( uint8_t ) pin >= ( uint8_t ) PIN_0 && ( uint8_t ) pin < ( uint8_t ) NUM_OF_PINS_PER_PORT )
    {
        switch ( port )
        {
            case PORT_A :
                switch ( resistor )
                {
                    case RESISTOR_PULL_UP :
                        SET_BIT ( PORTA , ( uint8_t ) pin );
                        break;
                    case RESISTOR_OPEN :
                        CLEAR_BIT ( PORTA , ( uint8_t ) pin );
                        break;
                    case RESISTOR_NOT_CARE :
                        break;
                    default:
                        opResult = DIO_ERR_RES;
                }
                break;
            case PORT_B :
                switch ( resistor )
                {
                    case RESISTOR_PULL_UP :
                        SET_BIT ( PORTB , ( uint8_t ) pin );
                        break;
                    case RESISTOR_OPEN :
                        CLEAR_BIT ( PORTB , ( uint8_t ) pin );
                        break;
                    case RESISTOR_NOT_CARE :
                        break;
                    default:
                        opResult = DIO_ERR_RES;
                }
                break;
            case PORT_C :
                switch ( resistor )
                {
                    case RESISTOR_PULL_UP :
                        SET_BIT ( PORTC , ( uint8_t ) pin );
                        break;
                    case RESISTOR_OPEN :
                        CLEAR_BIT ( PORTC , ( uint8_t ) pin );
                        break;
                    case RESISTOR_NOT_CARE :
                        break;
                    default:
                        opResult = DIO_ERR_RES;
                }
                break;
            case PORT_D :
                switch ( resistor )
                {
                    case RESISTOR_PULL_UP :
                        SET_BIT ( PORTD , ( uint8_t ) pin );
                        break;
                    case RESISTOR_OPEN :
                        CLEAR_BIT ( PORTD , ( uint8_t ) pin );
                        break;
                    case RESISTOR_NOT_CARE :
                        break;
                    default:
                        opResult = DIO_ERR_RES;
                }
                break;
            default:
                opResult = DIO_ERR_PORT;
        }
    }
    else
    {
        opResult = DIO_ERR_PIN_NUM;
    }
    return opResult;
}
DIO_STD_ERR_t DIO_write ( PORT_t port , PIN_t pin , PIN_STATE_t value )
{
    DIO_STD_ERR_t opResult = DIO_OK;
    #pragma GCC diagnostic ignored "-Wtype-limits"
    if ( ( uint8_t ) pin >= ( uint8_t ) PIN_0 && ( uint8_t ) pin < ( uint8_t ) NUM_OF_PINS_PER_PORT )
    {
        switch ( port )
        {
            case PORT_A :
                switch ( value )
                {
                    case PIN_STATE_HIGH :
                        SET_BIT ( PORTA , ( uint8_t ) pin );
                        break;
                    case PIN_STATE_LOW :
                        CLEAR_BIT ( PORTA , ( uint8_t ) pin );
                        break;
                    case PIN_STATE_NOT_CARE :
                        break;
                    default:
                        opResult = DIO_ERR_STATE;
                }
                break;
            case PORT_B :
                switch ( value )
                {
                    case PIN_STATE_HIGH :
                        SET_BIT ( PORTB , ( uint8_t ) pin );
                        break;
                    case PIN_STATE_LOW :
                        CLEAR_BIT ( PORTB , ( uint8_t ) pin );
                        break;
                    case PIN_STATE_NOT_CARE :
                        break;
                    default:
                        opResult = DIO_ERR_STATE;
                }
                break;
            case PORT_C :
                switch ( value )
                {
                    case PIN_STATE_HIGH :
                        SET_BIT ( PORTC , ( uint8_t ) pin );
                        break;
                    case PIN_STATE_LOW :
                        CLEAR_BIT ( PORTC , ( uint8_t ) pin );
                        break;
                    case PIN_STATE_NOT_CARE :
                        break;
                    default:
                        opResult = DIO_ERR_STATE;
                }
                break;
            case PORT_D :
                switch ( value )
                {
                    case PIN_STATE_HIGH :
                        SET_BIT ( PORTD , ( uint8_t ) pin );
                        break;
                    case PIN_STATE_LOW :
                        CLEAR_BIT ( PORTD , ( uint8_t ) pin );
                        break;
                    case PIN_STATE_NOT_CARE :
                        break;
                    default:
                        opResult = DIO_ERR_STATE;
                }
                break;
            default:
                opResult = DIO_ERR_PORT;
        }
    }
    else
    {
        opResult = DIO_ERR_PIN_NUM;
    }
    return opResult;
}
DIO_STD_ERR_t DIO_read ( PORT_t port , PIN_t pin , PIN_STATE_t* readState )
{
    DIO_STD_ERR_t opResult = DIO_OK;
    #pragma GCC diagnostic ignored "-Wtype-limits"
    if ( ( uint8_t ) pin >= ( uint8_t ) PIN_0 && ( uint8_t ) pin < ( uint8_t ) NUM_OF_PINS_PER_PORT )
    {
        switch ( port )
        {
            case PORT_A :
                *readState = ( PIN_STATE_t ) READ_BIT ( PINA , ( uint8_t ) pin );
                break;
            case PORT_B :
                *readState = ( PIN_STATE_t ) READ_BIT ( PINB , ( uint8_t ) pin );
                break;
            case PORT_C :
                *readState = ( PIN_STATE_t ) READ_BIT ( PINC , ( uint8_t ) pin );
                break;
            case PORT_D :
                *readState = ( PIN_STATE_t ) READ_BIT ( PIND , ( uint8_t ) pin );
                break;
            default:
                opResult = DIO_ERR_PORT;
        }
    }
    else
    {
        opResult = DIO_ERR_PIN_NUM;
    }
    return opResult;
}
void DIO_disableAllPullUpResistors ( void )
{
    SET_BIT ( SFIOR , PUD );
}
