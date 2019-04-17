#include <avr/io.h>
#include <avr/interrupt.h>
#include "io_extras.h"
#include "BitHelpers.h"
#include "Std_Types.h"
#include "common.h"
#include "EEPROM_private.h"
#include "EEPROM_config.h"
#include "EEPROM.h"
#define MAX_INTERNAL_EEPROM_ADDR ( ( uint16_t ) 0x3FF ) /* 1023 */
#define EMPTY_EEPROM_VALUE ( ( uint8_t ) 0xFF )
static inline uint8_t read ( uint16_t addr )
{
    /* Wait for completion of previous write */
    while ( READ_BIT ( EECR , EEWE ) == BIT_STATE_SET )
    {
    }
    /* Set up address register */
    EEAR = addr;
    /* Start EEPROM read by writing EERE */
    SET_BIT ( EECR , EERE );
    return EEDR;
}
static inline void write ( uint16_t addr , uint8_t valueToWrite )
{
    /* Wait for completion of previous write */
    while ( READ_BIT ( EECR , EEWE ) == BIT_STATE_SET )
    {
    }
    while ( READ_BIT ( SPMCR , SPMEN ) == BIT_STATE_SET )
    {
    }
    /* Set up address and data registers */
    EEAR = addr;
    EEDR = valueToWrite;
    /* Write logical one to EEMWE */
    REPLACE_BITS ( EECR , ( 0x01 << EEMWE ) | ( 0x00 << EEWE ) , BIT_MASK ( EEMWE ) | BIT_MASK ( EEWE ) );
    /* Start EEPROM write by setting EEWE */
    SET_BIT ( EECR , EEWE );
}
EEPROM_STD_ERR_t EEPROM_read ( uint16_t addr , uint8_t* readValue )
{
    EEPROM_STD_ERR_t readResult = EEPROM_OK;
    if ( addr <= MAX_INTERNAL_EEPROM_ADDR )
    {
#if USE_PROTECTED_SECTIONS == 1
        uint8_t intBit = ( uint8_t ) READ_BIT ( SREG , SREG_I );
        cli ();
#endif
        *readValue = read ( addr );
#if USE_PROTECTED_SECTIONS == 1
        REPLACE_BIT ( SREG , SREG_I , intBit );
#endif
    }
    else
    {
        readResult = EEPROM_ERR_ADDR;
    }
    return readResult;
}
EEPROM_STD_ERR_t EEPROM_readSection ( uint16_t addr , uint16_t readSize , uint8_t readValues[readSize] )
{
    EEPROM_STD_ERR_t readResult = EEPROM_OK;
    if ( addr > MAX_INTERNAL_EEPROM_ADDR )
    {
        readResult = EEPROM_ERR_ADDR;
    }
    else if ( ( addr + readSize - ( uint8_t ) 1 ) > MAX_INTERNAL_EEPROM_ADDR )
    {
        readResult = EEPROM_ERR_SIZE;
    }
    else if ( readSize == ( uint8_t ) 0 )
    {
        /* Do nothing */
    }
    else
    {
        uint16_t i;
        for ( i = ( uint16_t ) 0; i < readSize; i++ )
        {
#if USE_PROTECTED_SECTIONS == 1
            uint8_t intBit = ( uint8_t ) READ_BIT ( SREG , SREG_I );
            cli ();
#endif
            *readValues = read ( addr + i );
#if USE_PROTECTED_SECTIONS == 1
            REPLACE_BIT ( SREG , SREG_I , intBit );
#endif
            readValues++;
        }
    }
    return readResult;
}
EEPROM_STD_ERR_t EEPROM_write ( uint16_t addr , uint8_t valueToWrite )
{
    EEPROM_STD_ERR_t writeResult = EEPROM_OK;
    if ( addr <= MAX_INTERNAL_EEPROM_ADDR )
    {
#if USE_PROTECTED_SECTIONS == 1
        uint8_t intBit = ( uint8_t ) READ_BIT ( SREG , SREG_I );
        cli ();
#endif
        write ( addr , valueToWrite );
#if USE_PROTECTED_SECTIONS == 1
        REPLACE_BIT ( SREG , SREG_I , intBit );
#endif
    }
    else
    {
        writeResult = EEPROM_ERR_ADDR;
    }
    return writeResult;
}
EEPROM_STD_ERR_t EEPROM_writeSection ( uint16_t addr , uint16_t writeSize , uint8_t valuesToWrite[writeSize] )
{
    EEPROM_STD_ERR_t writeResult = EEPROM_OK;
    if ( addr > MAX_INTERNAL_EEPROM_ADDR )
    {
        writeResult = EEPROM_ERR_ADDR;
    }
    else if ( ( addr + writeSize - ( uint8_t ) 1 ) > MAX_INTERNAL_EEPROM_ADDR )
    {
        writeResult = EEPROM_ERR_SIZE;
    }
    else if ( writeSize == ( uint8_t ) 0 )
    {
        /* Do nothing */
    }
    else
    {
        uint16_t i;
        for ( i = ( uint16_t ) 0; i < writeSize; i++ )
        {
#if USE_PROTECTED_SECTIONS == 1
            uint8_t intBit = ( uint8_t ) READ_BIT ( SREG , SREG_I );
            cli ();
#endif
            write ( addr + i , *valuesToWrite );
#if USE_PROTECTED_SECTIONS == 1
            REPLACE_BIT ( SREG , SREG_I , intBit );
#endif
            valuesToWrite++;
        }
    }
    return writeResult;
}
EEPROM_STD_ERR_t EEPROM_fill ( uint16_t addr , uint16_t writeSize , uint8_t fillValue )
{
    EEPROM_STD_ERR_t writeResult = EEPROM_OK;
    if ( addr > MAX_INTERNAL_EEPROM_ADDR )
    {
        writeResult = EEPROM_ERR_ADDR;
    }
    else if ( ( addr + writeSize - ( uint8_t ) 1 ) > MAX_INTERNAL_EEPROM_ADDR )
    {
        writeResult = EEPROM_ERR_SIZE;
    }
    else if ( writeSize == ( uint8_t ) 0 )
    {
        /* Do nothing */
    }
    else
    {
        uint16_t i;
        for ( i = ( uint16_t ) 0; i < writeSize; i++ )
        {
#if USE_PROTECTED_SECTIONS == 1
            uint8_t intBit = ( uint8_t ) READ_BIT ( SREG , SREG_I );
            cli ();
#endif
            write ( addr + i , fillValue );
#if USE_PROTECTED_SECTIONS == 1
            REPLACE_BIT ( SREG , SREG_I , intBit );
#endif
        }
    }
    return writeResult;
}
EEPROM_STD_ERR_t EEPROM_copy ( uint16_t destAddr , uint16_t sourceAddr , uint16_t sizeToCopy )
{
    EEPROM_STD_ERR_t moveResult = EEPROM_OK;
    if ( destAddr > MAX_INTERNAL_EEPROM_ADDR || sourceAddr > MAX_INTERNAL_EEPROM_ADDR )
    {
        moveResult = EEPROM_ERR_ADDR;
    }
    else
    {
        uint16_t leadingAddress = ( uint16_t ) 0;
        uint16_t trailingAddress = ( uint16_t ) 0;
        if ( sourceAddr > destAddr )
        {
            leadingAddress = sourceAddr;
            trailingAddress = destAddr;
        }
        else
        {
            leadingAddress = destAddr;
            trailingAddress = sourceAddr;
        }
        if ( trailingAddress <= MAX_INTERNAL_EEPROM_ADDR && ( leadingAddress + sizeToCopy - ( uint8_t ) 1 ) > MAX_INTERNAL_EEPROM_ADDR )
        {
            moveResult = EEPROM_ERR_SIZE;
        }
        else if ( sizeToCopy == 0 || destAddr == sourceAddr )
        {
            /* Do nothing */
        }
        else if ( sourceAddr < destAddr && sourceAddr + sizeToCopy > destAddr )
        {
            uint16_t i;
            for ( i = sizeToCopy - ( uint8_t ) 1;; i-- )
            {
#if USE_PROTECTED_SECTIONS == 1
                uint8_t intBit = ( uint8_t ) READ_BIT ( SREG , SREG_I );
                cli ();
#endif
                write ( destAddr + i , read ( sourceAddr + i ) );
#if USE_PROTECTED_SECTIONS == 1
                REPLACE_BIT ( SREG , SREG_I , intBit );
#endif
                if ( i == 0 )
                {
                    break;
                }
            }
        }
        else
        {
            uint16_t i;
            for ( i = ( uint16_t ) 0; i < sizeToCopy; i++ )
            {
#if USE_PROTECTED_SECTIONS == 1
                uint8_t intBit = ( uint8_t ) READ_BIT ( SREG , SREG_I );
                cli ();
#endif
                write ( destAddr + i , read ( sourceAddr + i ) );
#if USE_PROTECTED_SECTIONS == 1
                REPLACE_BIT ( SREG , SREG_I , intBit );
#endif
            }
        }
    }
    return moveResult;
}
EEPROM_STD_ERR_t EEPROM_move ( uint16_t destAddr , uint16_t sourceAddr , uint16_t sizeToMove )
{
    EEPROM_STD_ERR_t moveResult = EEPROM_OK;
    if ( destAddr > MAX_INTERNAL_EEPROM_ADDR || sourceAddr > MAX_INTERNAL_EEPROM_ADDR )
    {
        moveResult = EEPROM_ERR_ADDR;
    }
    else
    {
        uint16_t leadingAddress = ( uint16_t ) 0;
        uint16_t trailingAddress = ( uint16_t ) 0;
        if ( sourceAddr > destAddr )
        {
            leadingAddress = sourceAddr;
            trailingAddress = destAddr;
        }
        else
        {
            leadingAddress = destAddr;
            trailingAddress = sourceAddr;
        }
        if ( ( trailingAddress <= MAX_INTERNAL_EEPROM_ADDR && ( leadingAddress + sizeToMove - ( uint16_t ) 1 ) > MAX_INTERNAL_EEPROM_ADDR ) )
        {
            moveResult = EEPROM_ERR_SIZE;
        }
        else if ( sizeToMove == 0 || destAddr == sourceAddr )
        {
            /* Do nothing */
        }
        else if ( sourceAddr < destAddr && sourceAddr + sizeToMove > destAddr )
        {
            uint16_t i;
            for ( i = sizeToMove - ( uint16_t ) 1;; i-- )
            {
#if USE_PROTECTED_SECTIONS == 1
                uint8_t intBit = ( uint8_t ) READ_BIT ( SREG , SREG_I );
                cli ();
#endif
                write ( destAddr + i , read ( sourceAddr + i ) );
#if USE_PROTECTED_SECTIONS == 1
                REPLACE_BIT ( SREG , SREG_I , intBit );
#endif
                if ( i == 0 )
                {
                    break;
                }
            }
            for ( i = 0; i < destAddr - sourceAddr; i++ )
            {
#if USE_PROTECTED_SECTIONS == 1
                uint8_t intBit = ( uint8_t ) READ_BIT ( SREG , SREG_I );
                cli ();
#endif
                write ( sourceAddr + i , EMPTY_EEPROM_VALUE );
#if USE_PROTECTED_SECTIONS == 1
                REPLACE_BIT ( SREG , SREG_I , intBit );
#endif
            }
        }
        else
        {
            uint16_t i;
            for ( i = ( uint16_t ) 0; i < sizeToMove; i++ )
            {
#if USE_PROTECTED_SECTIONS == 1
                uint8_t intBit = ( uint8_t ) READ_BIT ( SREG , SREG_I );
                cli ();
#endif
                write ( destAddr + i , read ( sourceAddr + i ) );
#if USE_PROTECTED_SECTIONS == 1
                REPLACE_BIT ( SREG , SREG_I , intBit );
#endif
            }
            for ( i = 0; i < sourceAddr - destAddr; i++ )
            {
#if USE_PROTECTED_SECTIONS == 1
                uint8_t intBit = ( uint8_t ) READ_BIT ( SREG , SREG_I );
                cli ();
#endif
                write ( destAddr + sizeToMove + i , EMPTY_EEPROM_VALUE );
#if USE_PROTECTED_SECTIONS == 1
                REPLACE_BIT ( SREG , SREG_I , intBit );
#endif
            }
        }
    }
    return moveResult;
}
