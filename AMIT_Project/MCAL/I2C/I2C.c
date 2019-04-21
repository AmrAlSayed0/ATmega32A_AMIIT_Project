#include <math.h>
#include <avr/io.h>
#include "io_extras.h"
#include <util/twi.h>
#include "bit_helpers.h"
#include "common.h"
#include "I2C_private.h"
#include "I2C_config.h"
#include "I2C.h"
#define MAX_SLAVE_ADDR          ( ( uint8_t ) 0x7F )
#define RESERVED_ADDR_1         ( 0x03 ) //00000011
#define RESERVED_ADDR_2_MASK    ( 0x7C ) //01111100
#define MAX_I2C_SPEED           ( ( uint32_t ) 400000 )
// SCL = CPU_CLCK / ( 16 + 2 * TWBR * ( 4 ^ TWPS ) )
#define SCL_CALC( twbrValue , twpsValue )   ( ( ( double ) F_CPU ) / ( ( double ) ( ( ( double ) 16 ) + ( ( ( double ) 2 ) * ( ( double ) ( twbrValue ) ) * pow ( 4 , ( twpsValue ) ) ) ) ) )
// TWBR = ( CPU_CLCK - ( 16 * SCL ) ) / ( 2 * TWBR * ( 4 ^ TWPS ) )
#define TWBR_CALC( sclValue , twpsValue )   ( ( ( ( double ) F_CPU ) - ( ( ( double ) 16 ) * ( ( double ) ( sclValue ) ) ) ) / ( ( ( double ) 2 ) * ( ( double ) ( sclValue ) ) * ( pow ( 4 , twpsValue ) ) ) )
#define MAX_POSSIBLE_I2C_SPEED              ( ( uint32_t ) floor ( SCL_CALC ( 0 , 0 ) ) ) //TWBR = 0, TWPS = 0
#define MIN_POSSIBLE_I2C_SPEED_PRESC_1      ( ( uint32_t ) ceil ( SCL_CALC ( 255 , 0 ) ) ) //TWBR = 255, TWPS = 0
#define MIN_POSSIBLE_I2C_SPEED_PRESC_4      ( ( uint32_t ) ceil ( SCL_CALC ( 255 , 1 ) ) ) //TWBR = 255, TWPS = 1
#define MIN_POSSIBLE_I2C_SPEED_PRESC_16     ( ( uint32_t ) ceil ( SCL_CALC ( 255 , 2 ) ) ) //TWBR = 255, TWPS = 2
#define MIN_POSSIBLE_I2C_SPEED_PRESC_64     ( ( uint32_t ) ceil ( SCL_CALC ( 255 , 3 ) ) ) //TWBR = 255, TWPS = 3
#define WAIT_OPERATION() \
    while ( READ_BIT ( TWCR , TWINT ) == BIT_STATE_CLEARED ) \
    { \
    }
#define SEND_START() \
    TWCR = ( BIT_MASK ( TWINT ) | BIT_MASK ( TWSTA ) | BIT_MASK ( TWEN ) ); \
    WAIT_OPERATION ();
#define SEND_REPEATED_START() \
    TWCR = ( BIT_MASK ( TWINT ) | BIT_MASK ( TWSTA ) | BIT_MASK ( TWEN ) ); \
    WAIT_OPERATION ();
#define SEND_STOP() \
    TWCR = ( BIT_MASK ( TWINT ) | BIT_MASK ( TWSTO ) | BIT_MASK ( TWEN ) );
#define SEND_STOP_AND_START() \
    TWCR = ( BIT_MASK ( TWINT ) | BIT_MASK ( TWSTA ) | BIT_MASK ( TWSTO ) | BIT_MASK ( TWEN ) );
#define SEND_ACK() \
    TWCR = ( BIT_MASK ( TWINT ) | BIT_MASK ( TWEA ) | BIT_MASK ( TWEN ) );
 #define SETUP_ACK() \
    TWCR = ( BIT_MASK ( TWINT ) | BIT_MASK ( TWEA ) | BIT_MASK ( TWEN ) );
#define SEND_NACK() \
    TWCR = ( BIT_MASK ( TWINT ) | BIT_MASK ( TWEN ) );
#define SETUP_NACK() \
    TWCR = ( BIT_MASK ( TWINT ) | BIT_MASK ( TWEN ) );
#define SEND_SLA_R( Addr ) \
    TWDR = ( ( ( ( uint8_t ) ( Addr ) ) << 1 ) | TW_READ ); \
    TWCR = ( BIT_MASK ( TWINT ) | BIT_MASK ( TWEN ) ); \
    WAIT_OPERATION ();
#define SEND_SLA_W( Addr ) \
    TWDR = ( ( ( ( uint8_t ) ( Addr ) ) << 1 ) | TW_WRITE ); \
    TWCR = ( BIT_MASK ( TWINT ) | BIT_MASK ( TWEN ) ); \
    WAIT_OPERATION ();
#define SEND_DATA( Data ) \
    TWDR = ( ( uint8_t ) ( Data ) ); \
    TWCR = ( BIT_MASK ( TWINT ) | BIT_MASK ( TWEN ) ); \
    WAIT_OPERATION ();
#define ENABLE_ACK() \
    TWCR = ( BIT_MASK ( TWEA ) | BIT_MASK ( TWEN ) );
void I2C_waitOperation ( void )
{
    WAIT_OPERATION ();
}
I2C_STATUS_t I2C_readStatus ( void )
{
    return ( I2C_STATUS_t ) TW_STATUS;
}
I2C_STD_ERR_t I2C_masterInit ( uint32_t speed )
{
    I2C_STD_ERR_t opResult = I2C_OK;
    if ( speed > ( uint8_t ) 0 && speed <= MAX_I2C_SPEED )
    {
        if ( speed <= MAX_POSSIBLE_I2C_SPEED )
        {
            if ( speed >= MIN_POSSIBLE_I2C_SPEED_PRESC_64 && speed < MIN_POSSIBLE_I2C_SPEED_PRESC_16 )
            {
                TWBR = ( uint8_t ) round ( TWBR_CALC ( speed , 3 ) );
                REPLACE_BITS ( TWSR , ( 0x01 << TWPS1 ) | ( 1 < TWPS0 ) , BIT_MASK ( TWPS1 ) | BIT_MASK ( TWPS0 ) );
            }
            else if ( speed >= MIN_POSSIBLE_I2C_SPEED_PRESC_16 && speed < MIN_POSSIBLE_I2C_SPEED_PRESC_4 )
            {
                TWBR = ( uint8_t ) round ( TWBR_CALC ( speed , 2 ) );
                REPLACE_BITS ( TWSR , ( 0x01 << TWPS1 ) | ( 0 < TWPS0 ) , BIT_MASK ( TWPS1 ) | BIT_MASK ( TWPS0 ) );
            }
            else if ( speed >= MIN_POSSIBLE_I2C_SPEED_PRESC_4 && speed < MIN_POSSIBLE_I2C_SPEED_PRESC_1 )
            {
                TWBR = ( uint8_t ) round ( TWBR_CALC ( speed , 1 ) );
                REPLACE_BITS ( TWSR , ( 0x00 << TWPS1 ) | ( 1 < TWPS0 ) , BIT_MASK ( TWPS1 ) | BIT_MASK ( TWPS0 ) );
            }
            else if ( speed >= MIN_POSSIBLE_I2C_SPEED_PRESC_1 )
            {
                TWBR = ( uint8_t ) round ( TWBR_CALC ( speed , 0 ) );
                REPLACE_BITS ( TWSR , ( 0x00 << TWPS1 ) | ( 0 < TWPS0 ) , BIT_MASK ( TWPS1 ) | BIT_MASK ( TWPS0 ) );
            }
            else
            {
                opResult = I2C_ERR_SPEED;
            }
        }
        else
        {
            opResult = I2C_ERR_SPEED;
        }
    }
    else
    {
        opResult = I2C_ERR_SPEED;
    }
    return opResult;
}
void I2C_start ( void )
{
    SEND_START ();
}
void I2C_repStart ( void )
{
    SEND_START ();
}
I2C_STD_ERR_t I2C_sendAddrAndRead ( uint8_t addr )
{
    I2C_STD_ERR_t opResult = I2C_OK;
    if ( addr <= MAX_SLAVE_ADDR || addr != RESERVED_ADDR_1 || ( READ_BITS ( addr , RESERVED_ADDR_2_MASK ) != RESERVED_ADDR_2_MASK ) )
    {
        SEND_SLA_R ( addr );
    }
    else
    {
        opResult = I2C_ERR_SLAVE_ADDR;
    }
    return opResult;
}
I2C_STD_ERR_t I2C_sendAddrAndWrite ( uint8_t addr )
{
    I2C_STD_ERR_t opResult = I2C_OK;
    if ( addr <= MAX_SLAVE_ADDR || addr != RESERVED_ADDR_1 || ( READ_BITS ( addr , RESERVED_ADDR_2_MASK ) != RESERVED_ADDR_2_MASK ) )
    {
        SEND_SLA_W ( addr );
    }
    else
    {
        opResult = I2C_ERR_SLAVE_ADDR;
    }
    return opResult;
}
void I2C_sendData ( uint8_t data )
{
    SEND_DATA ( data );
}
uint8_t I2C_receiveDataWithAck ( void )
{
    SETUP_ACK ();
    WAIT_OPERATION ();
    return TWDR;
}
uint8_t I2C_receiveDataWithNack ( void )
{
    SETUP_NACK ();
    WAIT_OPERATION ();
    return TWDR;
}
void I2C_stop ( void )
{
    SEND_STOP ();
}
void I2C_sendAck ( void )
{
    SEND_ACK ();
}
void I2C_sendNack ( void )
{
    SEND_NACK ();
}
I2C_STD_ERR_t I2C_slaveInit ( uint8_t addr , bool generalCallEnable )
{
    I2C_STD_ERR_t opResult = I2C_OK;
    if ( addr <= MAX_SLAVE_ADDR || addr != RESERVED_ADDR_1 || ( READ_BITS ( addr , RESERVED_ADDR_2_MASK ) != RESERVED_ADDR_2_MASK ) )
    {
        TWAR = ( addr << 1 ) | ( !generalCallEnable ?
                                 0 :
                                 1 );
        ENABLE_ACK ();
    }
    else
    {
        opResult = I2C_ERR_SLAVE_ADDR;
    }
    return opResult;
}
