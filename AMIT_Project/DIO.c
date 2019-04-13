#include "BitHelpers.h"
#include "Std_Types.h"
#include <avr/io.h>
#include "DIO_private.h"
#include "DIO.h"
DIO_STD_ERR_t DIO_init ()
{
    DIO_STD_ERR_t initResult = DIO_OK;
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
                            case DIRECTION_INPUT:
                                CLEAR_BIT ( ddrAValue , ( uint8_t ) DIO_inital_cfg_arr[ i ].pin );
                                switch ( DIO_inital_cfg_arr[ i ].res )
                                {
                                    case RESISTOR_PULL_UP:
                                        SET_BIT ( portAValue , ( uint8_t ) DIO_inital_cfg_arr[ i ].pin );
                                        break;
                                    case RESISTOR_OPEN:
                                        CLEAR_BIT ( portAValue , ( uint8_t ) DIO_inital_cfg_arr[ i ].pin );
                                        break;
                                    case RESISTOR_NOT_CARE:
                                        break;
                                    default:
                                        initResult = DIO_ERR_RES;
                                }
                                break;
                            case DIRECTION_OUTPUT:
                                SET_BIT ( ddrAValue , ( uint8_t ) DIO_inital_cfg_arr[ i ].pin );
                                switch ( DIO_inital_cfg_arr[ i ].initial )
                                {
                                    case PIN_STATE_HIGH:
                                        SET_BIT ( portAValue , ( uint8_t ) DIO_inital_cfg_arr[ i ].pin );
                                        break;
                                    case PIN_STATE_LOW:
                                        CLEAR_BIT ( portAValue , ( uint8_t ) DIO_inital_cfg_arr[ i ].pin );
                                        break;
                                    case PIN_STATE_NOT_CARE:
                                        break;
                                    default:
                                        initResult = DIO_ERR_STATE;
                                }
                                break;
                            default:
                                initResult = DIO_ERR_DIR;
                        }
                        break;
                    case PORT_B :
                        switch ( DIO_inital_cfg_arr[ i ].dir )
                        {
                            case DIRECTION_INPUT:
                                CLEAR_BIT ( ddrBValue , ( uint8_t ) DIO_inital_cfg_arr[ i ].pin );
                                switch ( DIO_inital_cfg_arr[ i ].res )
                                {
                                    case RESISTOR_PULL_UP:
                                        SET_BIT ( portBValue , ( uint8_t ) DIO_inital_cfg_arr[ i ].pin );
                                        break;
                                    case RESISTOR_OPEN:
                                        CLEAR_BIT ( portBValue , ( uint8_t ) DIO_inital_cfg_arr[ i ].pin );
                                        break;
                                    case RESISTOR_NOT_CARE:
                                        break;
                                    default:
                                        initResult = DIO_ERR_RES;
                                }
                                break;
                            case DIRECTION_OUTPUT:
                                SET_BIT ( ddrBValue , ( uint8_t ) DIO_inital_cfg_arr[ i ].pin );
                                switch ( DIO_inital_cfg_arr[ i ].initial )
                                {
                                    case PIN_STATE_HIGH:
                                        SET_BIT ( portBValue , ( uint8_t ) DIO_inital_cfg_arr[ i ].pin );
                                        break;
                                    case PIN_STATE_LOW:
                                        CLEAR_BIT ( portBValue , ( uint8_t ) DIO_inital_cfg_arr[ i ].pin );
                                        break;
                                    case PIN_STATE_NOT_CARE:
                                        break;
                                    default:
                                        initResult = DIO_ERR_STATE;
                                }
                                break;
                            default:
                                initResult = DIO_ERR_DIR;
                        }
                        break;
                    case PORT_C :
                        switch ( DIO_inital_cfg_arr[ i ].dir )
                        {
                            case DIRECTION_INPUT:
                                CLEAR_BIT ( ddrCValue , ( uint8_t ) DIO_inital_cfg_arr[ i ].pin );
                                switch ( DIO_inital_cfg_arr[ i ].res )
                                {
                                    case RESISTOR_PULL_UP:
                                        SET_BIT ( portCValue , ( uint8_t ) DIO_inital_cfg_arr[ i ].pin );
                                        break;
                                    case RESISTOR_OPEN:
                                        CLEAR_BIT ( portCValue , ( uint8_t ) DIO_inital_cfg_arr[ i ].pin );
                                        break;
                                    case RESISTOR_NOT_CARE:
                                        break;
                                    default:
                                        initResult = DIO_ERR_RES;
                                }
                                break;
                            case DIRECTION_OUTPUT:
                                SET_BIT ( ddrCValue , ( uint8_t ) DIO_inital_cfg_arr[ i ].pin );
                                switch ( DIO_inital_cfg_arr[ i ].initial )
                                {
                                    case PIN_STATE_HIGH:
                                        SET_BIT ( portCValue , ( uint8_t ) DIO_inital_cfg_arr[ i ].pin );
                                        break;
                                    case PIN_STATE_LOW:
                                        CLEAR_BIT ( portCValue , ( uint8_t ) DIO_inital_cfg_arr[ i ].pin );
                                        break;
                                    case PIN_STATE_NOT_CARE:
                                        break;
                                    default:
                                        initResult = DIO_ERR_STATE;
                                }
                                break;
                            default:
                                initResult = DIO_ERR_DIR;
                        }
                        break;
                    case PORT_D :
                        switch ( DIO_inital_cfg_arr[ i ].dir )
                        {
                            case DIRECTION_INPUT:
                                CLEAR_BIT ( ddrDValue , ( uint8_t ) DIO_inital_cfg_arr[ i ].pin );
                                switch ( DIO_inital_cfg_arr[ i ].res )
                                {
                                    case RESISTOR_PULL_UP:
                                        SET_BIT ( portDValue , ( uint8_t ) DIO_inital_cfg_arr[ i ].pin );
                                        break;
                                    case RESISTOR_OPEN:
                                        CLEAR_BIT ( portDValue , ( uint8_t ) DIO_inital_cfg_arr[ i ].pin );
                                        break;
                                    case RESISTOR_NOT_CARE:
                                        break;
                                    default:
                                        initResult = DIO_ERR_RES;
                                }
                                break;
                            case DIRECTION_OUTPUT:
                                SET_BIT ( ddrDValue , DIO_inital_cfg_arr[ i ].pin );
                                switch ( DIO_inital_cfg_arr[ i ].initial )
                                {
                                    case PIN_STATE_HIGH:
                                        SET_BIT ( portDValue , ( uint8_t ) DIO_inital_cfg_arr[ i ].pin );
                                        break;
                                    case PIN_STATE_LOW:
                                        CLEAR_BIT ( portDValue , ( uint8_t ) DIO_inital_cfg_arr[ i ].pin );
                                        break;
                                    case PIN_STATE_NOT_CARE:
                                        break;
                                    default:
                                        initResult = DIO_ERR_STATE;
                                }
                                break;
                            default:
                                initResult = DIO_ERR_DIR;
                        }
                        break;
                    default:
                        initResult = DIO_ERR_PORT;
                }
            }
            else
            {
                initResult = DIO_ERR_PIN_NUM;
            }
        }
    }
    else
    {
        initResult = DIO_ERR_NUM_OF_PINS;
    }
    if ( initResult == DIO_OK )
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
    return initResult;
}
DIO_STD_ERR_t DIO_direction ( PORT_t port , PIN_t pin , DIRECTION_t dir )
{
    DIO_STD_ERR_t opResult = DIO_OK;
    #pragma GCC diagnostic ignored "-Wtype-limits"
    if ( ( uint8_t ) pin >= ( uint8_t ) PIN_0 && ( uint8_t ) pin < ( uint8_t ) NUM_OF_PINS_PER_PORT )
    {
        switch ( port )
        {
            case PORT_A:
                switch ( dir )
                {
                    case DIRECTION_OUTPUT:
                        SET_BIT ( DDRA , ( uint8_t ) pin );
                        break;
                    case PIN_STATE_LOW:
                        CLEAR_BIT ( DDRA , ( uint8_t ) pin );
                        break;
                    default:
                        opResult = DIO_ERR_DIR;
                }
                break;
            case PORT_B:
                switch ( dir )
                {
                    case DIRECTION_OUTPUT:
                        SET_BIT ( DDRB , ( uint8_t ) pin );
                        break;
                    case PIN_STATE_LOW:
                        CLEAR_BIT ( DDRB , ( uint8_t ) pin );
                        break;
                    default:
                        opResult = DIO_ERR_DIR;
                }
                break;
            case PORT_C:
                switch ( dir )
                {
                    case DIRECTION_OUTPUT:
                        SET_BIT ( DDRC , ( uint8_t ) pin );
                        break;
                    case PIN_STATE_LOW:
                        CLEAR_BIT ( DDRC , ( uint8_t ) pin );
                        break;
                    default:
                        opResult = DIO_ERR_DIR;
                }
                break;
            case PORT_D:
                switch ( dir )
                {
                    case DIRECTION_OUTPUT:
                        SET_BIT ( DDRD , ( uint8_t ) pin );
                        break;
                    case PIN_STATE_LOW:
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
DIO_STD_ERR_t DIO_resistor ( PORT_t port , PIN_t pin , RESISTOR_t resistor )
{
    DIO_STD_ERR_t opResult = DIO_OK;
    #pragma GCC diagnostic ignored "-Wtype-limits"
    if ( ( uint8_t ) pin >= ( uint8_t ) PIN_0 && ( uint8_t ) pin < ( uint8_t ) NUM_OF_PINS_PER_PORT )
    {
        switch ( port )
        {
            case PORT_A:
                switch ( resistor )
                {
                    case RESISTOR_OPEN:
                        SET_BIT ( PORTA , ( uint8_t ) pin );
                        break;
                    case RESISTOR_PULL_UP:
                        CLEAR_BIT ( PORTA , ( uint8_t ) pin );
                        break;
                    case RESISTOR_NOT_CARE:
                        break;
                    default:
                        opResult = DIO_ERR_RES;
                }
                break;
            case PORT_B:
                switch ( resistor )
                {
                    case DIRECTION_OUTPUT:
                        SET_BIT ( PORTB , ( uint8_t ) pin );
                        break;
                    case PIN_STATE_LOW:
                        CLEAR_BIT ( PORTB , ( uint8_t ) pin );
                        break;
                    case RESISTOR_NOT_CARE:
                        break;
                    default:
                        opResult = DIO_ERR_RES;
                }
                break;
            case PORT_C:
                switch ( resistor )
                {
                    case DIRECTION_OUTPUT:
                        SET_BIT ( PORTC , ( uint8_t ) pin );
                        break;
                    case PIN_STATE_LOW:
                        CLEAR_BIT ( PORTC , ( uint8_t ) pin );
                        break;
                    case RESISTOR_NOT_CARE:
                        break;
                    default:
                        opResult = DIO_ERR_RES;
                }
                break;
            case PORT_D:
                switch ( resistor )
                {
                    case DIRECTION_OUTPUT:
                        SET_BIT ( PORTD , ( uint8_t ) pin );
                        break;
                    case PIN_STATE_LOW:
                        CLEAR_BIT ( PORTD , ( uint8_t ) pin );
                        break;
                    case RESISTOR_NOT_CARE:
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
    DIO_STD_ERR_t writeResult = DIO_OK;
    #pragma GCC diagnostic ignored "-Wtype-limits"
    if ( ( uint8_t ) pin >= ( uint8_t ) PIN_0 && ( uint8_t ) pin < ( uint8_t ) NUM_OF_PINS_PER_PORT )
    {
        switch ( port )
        {
            case PORT_A:
                switch ( value )
                {
                    case PIN_STATE_HIGH:
                        SET_BIT ( PORTA , ( uint8_t ) pin );
                        break;
                    case PIN_STATE_LOW:
                        CLEAR_BIT ( PORTA , ( uint8_t ) pin );
                        break;
                    case PIN_STATE_NOT_CARE:
                        break;
                    default:
                        writeResult = DIO_ERR_STATE;
                }
                break;
            case PORT_B:
                switch ( value )
                {
                    case PIN_STATE_HIGH:
                        SET_BIT ( PORTB , ( uint8_t ) pin );
                        break;
                    case PIN_STATE_LOW:
                        CLEAR_BIT ( PORTB , ( uint8_t ) pin );
                        break;
                    case PIN_STATE_NOT_CARE:
                        break;
                    default:
                        writeResult = DIO_ERR_STATE;
                }
                break;
            case PORT_C:
                switch ( value )
                {
                    case PIN_STATE_HIGH:
                        SET_BIT ( PORTC , ( uint8_t ) pin );
                        break;
                    case PIN_STATE_LOW:
                        CLEAR_BIT ( PORTC , ( uint8_t ) pin );
                        break;
                    case PIN_STATE_NOT_CARE:
                        break;
                    default:
                        writeResult = DIO_ERR_STATE;
                }
                break;
            case PORT_D:
                switch ( value )
                {
                    case PIN_STATE_HIGH:
                        SET_BIT ( PORTD , ( uint8_t ) pin );
                        break;
                    case PIN_STATE_LOW:
                        CLEAR_BIT ( PORTD , ( uint8_t ) pin );
                        break;
                    case PIN_STATE_NOT_CARE:
                        break;
                    default:
                        writeResult = DIO_ERR_STATE;
                }
                break;
            default:
                writeResult = DIO_ERR_PORT;
        }
    }
    else
    {
        writeResult = DIO_ERR_PIN_NUM;
    }
    return writeResult;
}
DIO_STD_ERR_t DIO_read ( PORT_t port , PIN_t pin , PIN_STATE_t* readState )
{
    DIO_STD_ERR_t readResult = DIO_OK;
    #pragma GCC diagnostic ignored "-Wtype-limits"
    if ( ( uint8_t ) pin >= ( uint8_t ) PIN_0 && ( uint8_t ) pin < ( uint8_t ) NUM_OF_PINS_PER_PORT )
    {
        switch ( port )
        {
            case PORT_A:
                *readState = ( PIN_STATE_t ) READ_BIT ( PINA , ( uint8_t ) pin );
                break;
            case PORT_B:
                *readState = ( PIN_STATE_t ) READ_BIT ( PINB , ( uint8_t ) pin );
                break;
            case PORT_C:
                *readState = ( PIN_STATE_t ) READ_BIT ( PINC , ( uint8_t ) pin );
                break;
            case PORT_D:
                *readState = ( PIN_STATE_t ) READ_BIT ( PIND , ( uint8_t ) pin );
                break;
            default:
                readResult = DIO_ERR_PORT;
        }
    }
    else
    {
        readResult = DIO_ERR_PIN_NUM;
    }
    return readResult;
}
void DIO_disableAllPullUpResistors ()
{
    SET_BIT ( SFIOR , PUD );
}
