#include <util/delay.h>
#include "bit_helpers.h"
#include "I2C.h"
#include "EXT_EEPROM.h"
#include "EXT_EEPROM_config.h"
#include "EXT_EEPROM_private.h"
#define CONTROL_ADDR ( 0x50 )
#define HIGH_BYTE_MASK ( 0x0000FF00 )
#define LOW_BYTE_MASK ( 0x000000FF )
#define MAX_EXT_EEPROM_ADDR ( ( uint32_t ) 0x01FFFF )
#define PAGE_BOUNDRY ( ( uint32_t ) 0x00FFFF )
#define EMPTY_EEPROM_VALUE ( ( uint8_t ) 0xFF )
static EXT_EEPROM_STD_ERR_t read ( uint32_t addr , uint8_t* readValue )
{
    EXT_EEPROM_STD_ERR_t opResult = EXT_EEPROM_OK;
    uint8_t controlByte = CONTROL_ADDR | LEFT_SHIFT ( READ_BIT ( addr , 16 ) , 2 );
    uint8_t highAddress = ( uint8_t ) READ_BITS_AND_SHIFT ( addr , HIGH_BYTE_MASK , 8 );
    uint8_t lowAddress = ( uint8_t ) READ_BITS_AND_SHIFT ( addr , LOW_BYTE_MASK , 0 );
    I2C_STATUS_t currentStatus = I2C_STATUS_NONE;
    uint8_t currentNumOfRetries;
    EXT_EEPROM_waitBusy ();
START:
    currentNumOfRetries = 0;
    I2C_start ();
    currentStatus = I2C_readStatus ();
    if ( currentStatus == I2C_STATUS_START_TRANS )
    {
        I2C_sendAddrAndWrite ( controlByte );
        currentStatus = I2C_readStatus ();
        if ( currentStatus == I2C_STATUS_M_SLW_W_TRANS_ACK_REC )
        {
HIGH_ADDRESS:
            I2C_sendData ( highAddress );
            currentStatus = I2C_readStatus ();
            if ( currentStatus == I2C_STATUS_M_DATA_TRANS_ACK_REC )
            {
                currentNumOfRetries = 0;
LOW_ADDRESS:
                I2C_sendData ( lowAddress );
                currentStatus = I2C_readStatus ();
                if ( currentStatus == I2C_STATUS_M_DATA_TRANS_ACK_REC )
                {
                    currentNumOfRetries = 0;
REP_START:
                    I2C_repStart ();
                    currentStatus = I2C_readStatus ();
                    if ( currentStatus == I2C_STATUS_REP_START_TRANS )
                    {
                        I2C_sendAddrAndRead ( controlByte );
                        currentStatus = I2C_readStatus ();
                        if ( currentStatus == I2C_STATUS_M_SLW_R_TRANS_ACK_REC )
                        {
                            *readValue = I2C_receiveDataWithNack ();
                            I2C_stop ();
                        }
                        else if ( currentStatus == I2C_STATUS_M_ARB_LOST )
                        {
                            goto START;
                        }
                        else
                        {
                            if ( currentNumOfRetries < MAX_NACK_RETRIES )
                            {
                                currentNumOfRetries++;
                                goto REP_START;
                            }
                            else
                            {
                                I2C_stop ();
                                opResult = EXT_EEPROM_ERR_CTRL_COM;
                            }
                        }
                    }
                    else
                    {
                        I2C_stop ();
                        opResult = EXT_EEPROM_ERR_DATA_COM;
                    }
                }
                else if ( currentStatus == I2C_STATUS_M_ARB_LOST )
                {
                    goto START;
                }
                else
                {
                    if ( currentNumOfRetries < MAX_NACK_RETRIES )
                    {
                        currentNumOfRetries++;
                        goto LOW_ADDRESS;
                    }
                    else
                    {
                        I2C_stop ();
                        opResult = EXT_EEPROM_ERR_ADDR_COM;
                    }
                }
            }
            else if ( currentStatus == I2C_STATUS_M_ARB_LOST )
            {
                goto START;
            }
            else
            {
                if ( currentNumOfRetries < MAX_NACK_RETRIES )
                {
                    currentNumOfRetries++;
                    goto HIGH_ADDRESS;
                }
                else
                {
                    I2C_stop ();
                    opResult = EXT_EEPROM_ERR_ADDR_COM;
                }
            }
        }
        else if ( currentStatus == I2C_STATUS_M_ARB_LOST )
        {
            goto START;
        }
        else
        {
            I2C_stop ();
            opResult = EXT_EEPROM_ERR_CTRL_COM;
        }
    }
    else
    {
        opResult = EXT_EEPROM_ERR_START_COM;
    }
    return opResult;
}
static EXT_EEPROM_STD_ERR_t write ( uint32_t addr , uint8_t valueToWrite )
{
    EXT_EEPROM_STD_ERR_t opResult = EXT_EEPROM_OK;
    uint8_t controlByte = CONTROL_ADDR | LEFT_SHIFT ( READ_BIT ( addr , 16 ) , 2 );
    uint8_t highAddress = ( uint8_t ) READ_BITS_AND_SHIFT ( addr , HIGH_BYTE_MASK , 8 );
    uint8_t lowAddress = ( uint8_t ) READ_BITS_AND_SHIFT ( addr , LOW_BYTE_MASK , 0 );
    uint8_t currentNumOfRetries;
    I2C_STATUS_t currentStatus = I2C_STATUS_NONE;
    EXT_EEPROM_waitBusy ();
START:
    currentNumOfRetries = 0;
    I2C_start ();
    currentStatus = I2C_readStatus ();
    if ( currentStatus == I2C_STATUS_START_TRANS )
    {
        I2C_sendAddrAndWrite ( controlByte );
        currentStatus = I2C_readStatus ();
        if ( currentStatus == I2C_STATUS_M_SLW_W_TRANS_ACK_REC )
        {
HIGH_ADDRESS:
            I2C_sendData ( highAddress );
            currentStatus = I2C_readStatus ();
            if ( currentStatus == I2C_STATUS_M_DATA_TRANS_ACK_REC )
            {
                currentNumOfRetries = 0;
LOW_ADDRESS:
                I2C_sendData ( lowAddress );
                currentStatus = I2C_readStatus ();
                if ( currentStatus == I2C_STATUS_M_DATA_TRANS_ACK_REC )
                {
                    currentNumOfRetries = 0;
DATA:
                    I2C_sendData ( valueToWrite );
                    currentStatus = I2C_readStatus ();
                    if ( currentStatus == I2C_STATUS_M_DATA_TRANS_ACK_REC )
                    {
                        I2C_stop ();
                    }
                    else if ( currentStatus == I2C_STATUS_M_ARB_LOST )
                    {
                        goto START;
                    }
                    else
                    {
                        if ( currentNumOfRetries < MAX_NACK_RETRIES )
                        {
                            currentNumOfRetries++;
                            goto DATA;
                        }
                        else
                        {
                            I2C_stop ();
                            opResult = EXT_EEPROM_ERR_DATA_COM;
                        }
                    }
                }
                else if ( currentStatus == I2C_STATUS_M_ARB_LOST )
                {
                    goto START;
                }
                else
                {
                    if ( currentNumOfRetries < MAX_NACK_RETRIES )
                    {
                        currentNumOfRetries++;
                        goto LOW_ADDRESS;
                    }
                    else
                    {
                        I2C_stop ();
                        opResult = EXT_EEPROM_ERR_ADDR_COM;
                    }
                }
            }
            else if ( currentStatus == I2C_STATUS_M_ARB_LOST )
            {
                goto START;
            }
            else
            {
                if ( currentNumOfRetries < MAX_NACK_RETRIES )
                {
                    currentNumOfRetries++;
                    goto HIGH_ADDRESS;
                }
                else
                {
                    I2C_stop ();
                    opResult = EXT_EEPROM_ERR_ADDR_COM;
                }
            }
        }
        else if ( currentStatus == I2C_STATUS_M_ARB_LOST )
        {
            goto START;
        }
        else
        {
            I2C_stop ();
            opResult = EXT_EEPROM_ERR_CTRL_COM;
        }
    }
    else
    {
        opResult = EXT_EEPROM_ERR_START_COM;
    }
    return opResult;
}
void EXT_EEPROM_waitBusy ( void )
{
    uint8_t controlByte = CONTROL_ADDR;
    I2C_STATUS_t currentStatus = I2C_STATUS_NONE;
START:
    I2C_start ();
    currentStatus = I2C_readStatus ();
    if ( currentStatus == I2C_STATUS_START_TRANS || currentStatus == I2C_STATUS_REP_START_TRANS )
    {
        I2C_sendAddrAndWrite ( controlByte );
        currentStatus = I2C_readStatus ();
        if ( currentStatus == I2C_STATUS_M_SLW_W_TRANS_NACK_REC || currentStatus == I2C_STATUS_M_ARB_LOST )
        {
            _delay_ms ( EXT_EEPROM_WRITE_TIME_IN_MS );
            goto START;
        }
        else
        {
            I2C_stop ();
        }
    }
    else
    {
        I2C_stop ();
    }
}
EXT_EEPROM_STD_ERR_t EXT_EEPROM_read ( uint32_t addr , uint8_t* readValue )
{
    EXT_EEPROM_STD_ERR_t opResult = EXT_EEPROM_OK;
    if ( addr <= MAX_EXT_EEPROM_ADDR )
    {
        opResult = read ( addr , readValue );
    }
    else
    {
        opResult = EXT_EEPROM_ERR_ADDR;
    }
    return opResult;
}
EXT_EEPROM_STD_ERR_t EXT_EEPROM_readSection ( uint32_t addr , uint32_t readSize , uint8_t readValues[readSize] )
{
    EXT_EEPROM_STD_ERR_t opResult = EXT_EEPROM_OK;
    if ( addr > MAX_EXT_EEPROM_ADDR )
    {
        opResult = EXT_EEPROM_ERR_ADDR;
    }
    else if ( ( addr + readSize - ( uint8_t ) 1 ) > MAX_EXT_EEPROM_ADDR )
    {
        opResult = EXT_EEPROM_ERR_SIZE;
    }
    else if ( readSize == ( uint8_t ) 0 )
    {
        /* Do nothing */
    }
    else
    {
        uint8_t controlByte;
        uint8_t highAddress;
        uint8_t lowAddress;
        uint32_t currentAddr = addr;
        I2C_STATUS_t currentStatus = I2C_STATUS_NONE;
        uint8_t currentNumOfRetries;
        uint32_t i = 0;
SETUP:
        controlByte = CONTROL_ADDR | LEFT_SHIFT ( READ_BIT ( addr , 16 ) , 2 );
        highAddress = ( uint8_t ) READ_BITS_AND_SHIFT ( addr , HIGH_BYTE_MASK , 8 );
        lowAddress = ( uint8_t ) READ_BITS_AND_SHIFT ( addr , LOW_BYTE_MASK , 0 );
        EXT_EEPROM_waitBusy ();
START:
        currentNumOfRetries = 0;
        I2C_start ();
        currentStatus = I2C_readStatus ();
        if ( currentStatus == I2C_STATUS_START_TRANS )
        {
            I2C_sendAddrAndWrite ( controlByte );
            currentStatus = I2C_readStatus ();
            if ( currentStatus == I2C_STATUS_M_SLW_W_TRANS_ACK_REC )
            {
HIGH_ADDRESS:
                I2C_sendData ( highAddress );
                currentStatus = I2C_readStatus ();
                if ( currentStatus == I2C_STATUS_M_DATA_TRANS_ACK_REC )
                {
                    currentNumOfRetries = 0;
LOW_ADDRESS:
                    I2C_sendData ( lowAddress );
                    currentStatus = I2C_readStatus ();
                    if ( currentStatus == I2C_STATUS_M_DATA_TRANS_ACK_REC )
                    {
                        currentNumOfRetries = 0;
REP_START:
                        I2C_repStart ();
                        currentStatus = I2C_readStatus ();
                        if ( currentStatus == I2C_STATUS_REP_START_TRANS )
                        {
                            I2C_sendAddrAndRead ( controlByte );
                            currentStatus = I2C_readStatus ();
                            if ( currentStatus == I2C_STATUS_M_SLW_R_TRANS_ACK_REC )
                            {
                                currentNumOfRetries = 0;
                                for ( ; i < readSize; i++ )
                                {
                                    if ( i + 1 != readSize )
                                    {
                                        if ( currentAddr == PAGE_BOUNDRY )
                                        {
                                            *readValues = I2C_receiveDataWithNack ();
                                            I2C_stop ();
                                            readValues++;
                                            addr = ++currentAddr;
                                            i++;
                                            goto SETUP;
                                        }
                                        else
                                        {
                                            *readValues = I2C_receiveDataWithAck ();
                                            readValues++;
                                            currentAddr++;
                                        }
                                    }
                                    else
                                    {
                                        *readValues = I2C_receiveDataWithNack ();
                                    }
                                }
                                I2C_stop ();
                            }
                            else if ( currentStatus == I2C_STATUS_M_ARB_LOST )
                            {
                                goto START;
                            }
                            else
                            {
                                if ( currentNumOfRetries < MAX_NACK_RETRIES )
                                {
                                    currentNumOfRetries++;
                                    goto REP_START;
                                }
                                else
                                {
                                    I2C_stop ();
                                    opResult = EXT_EEPROM_ERR_CTRL_COM;
                                }
                            }
                        }
                        else
                        {
                            I2C_stop ();
                            opResult = EXT_EEPROM_ERR_DATA_COM;
                        }
                    }
                    else if ( currentStatus == I2C_STATUS_M_ARB_LOST )
                    {
                        goto START;
                    }
                    else
                    {
                        if ( currentNumOfRetries < MAX_NACK_RETRIES )
                        {
                            currentNumOfRetries++;
                            goto LOW_ADDRESS;
                        }
                        else
                        {
                            I2C_stop ();
                            opResult = EXT_EEPROM_ERR_ADDR_COM;
                        }
                    }
                }
                else if ( currentStatus == I2C_STATUS_M_ARB_LOST )
                {
                    goto START;
                }
                else
                {
                    if ( currentNumOfRetries < MAX_NACK_RETRIES )
                    {
                        currentNumOfRetries++;
                        goto HIGH_ADDRESS;
                    }
                    else
                    {
                        I2C_stop ();
                        opResult = EXT_EEPROM_ERR_ADDR_COM;
                    }
                }
            }
            else if ( currentStatus == I2C_STATUS_M_ARB_LOST )
            {
                goto START;
            }
            else
            {
                I2C_stop ();
                opResult = EXT_EEPROM_ERR_CTRL_COM;
            }
        }
        else
        {
            opResult = EXT_EEPROM_ERR_START_COM;
        }
    }
    return opResult;
}
EXT_EEPROM_STD_ERR_t EXT_EEPROM_write ( uint32_t addr , uint8_t valueToWrite )
{
    EXT_EEPROM_STD_ERR_t opResult = EXT_EEPROM_OK;
    if ( addr <= MAX_EXT_EEPROM_ADDR )
    {
        opResult = write ( addr , valueToWrite );
    }
    else
    {
        opResult = EXT_EEPROM_ERR_ADDR;
    }
    return opResult;
}
EXT_EEPROM_STD_ERR_t EXT_EEPROM_writeSection ( uint32_t addr , uint32_t writeSize , uint8_t valuesToWrite[writeSize] )
{
    EXT_EEPROM_STD_ERR_t opResult = EXT_EEPROM_OK;
    if ( addr > MAX_EXT_EEPROM_ADDR )
    {
        opResult = EXT_EEPROM_ERR_ADDR;
    }
    else if ( ( addr + writeSize - ( uint8_t ) 1 ) > MAX_EXT_EEPROM_ADDR )
    {
        opResult = EXT_EEPROM_ERR_SIZE;
    }
    else if ( writeSize == ( uint8_t ) 0 )
    {
        /* Do nothing */
    }
    else
    {
        uint8_t controlByte;
        uint8_t highAddress;
        uint8_t lowAddress;
        uint32_t currentAddr = addr;
        uint8_t currentNumOfRetries;
        uint32_t i = 0;
        uint8_t currentByteNumber;
        I2C_STATUS_t currentStatus = I2C_STATUS_NONE;
SETUP:
        controlByte = CONTROL_ADDR | LEFT_SHIFT ( READ_BIT ( addr , 16 ) , 2 );
        highAddress = ( uint8_t ) READ_BITS_AND_SHIFT ( addr , HIGH_BYTE_MASK , 8 );
        lowAddress = ( uint8_t ) READ_BITS_AND_SHIFT ( addr , LOW_BYTE_MASK , 0 );
        EXT_EEPROM_waitBusy ();
START:
        currentNumOfRetries = 0;
        I2C_start ();
        currentStatus = I2C_readStatus ();
        if ( currentStatus == I2C_STATUS_START_TRANS )
        {
            I2C_sendAddrAndWrite ( controlByte );
            currentStatus = I2C_readStatus ();
            if ( currentStatus == I2C_STATUS_M_SLW_W_TRANS_ACK_REC )
            {
HIGH_ADDRESS:
                I2C_sendData ( highAddress );
                currentStatus = I2C_readStatus ();
                if ( currentStatus == I2C_STATUS_M_DATA_TRANS_ACK_REC )
                {
                    currentNumOfRetries = 0;
LOW_ADDRESS:
                    I2C_sendData ( lowAddress );
                    currentStatus = I2C_readStatus ();
                    if ( currentStatus == I2C_STATUS_M_DATA_TRANS_ACK_REC )
                    {
                        currentByteNumber = 0;
                        for ( ; i < writeSize; i++ )
                        {
                            currentNumOfRetries = 0;
                            if ( i + 1 != writeSize )
                            {
                                if ( ( currentByteNumber == 0 || currentByteNumber % 127 != 0 ) && currentAddr != PAGE_BOUNDRY )
                                {
RET_0:
                                    I2C_sendData ( *valuesToWrite );
                                    currentStatus = I2C_readStatus ();
                                    if ( currentStatus == I2C_STATUS_M_DATA_TRANS_ACK_REC )
                                    {
                                        valuesToWrite++;
                                        currentAddr++;
                                        currentByteNumber++;
                                    }
                                    else if ( currentStatus == I2C_STATUS_M_ARB_LOST )
                                    {
                                        goto START;
                                    }
                                    else
                                    {
                                        if ( currentNumOfRetries < MAX_NACK_RETRIES )
                                        {
                                            currentNumOfRetries++;
                                            goto RET_0;
                                        }
                                        else
                                        {
                                            I2C_stop ();
                                            opResult = EXT_EEPROM_ERR_DATA_COM;
                                        }
                                    }
                                }
                                else
                                {
RET_1:
                                    I2C_sendData ( *valuesToWrite );
                                    currentStatus = I2C_readStatus ();
                                    if ( currentStatus == I2C_STATUS_M_DATA_TRANS_ACK_REC )
                                    {
                                        I2C_stop ();
                                        valuesToWrite++;
                                        currentAddr++;
                                        i++;
                                        addr = currentAddr;
                                        goto SETUP;
                                    }
                                    else if ( currentStatus == I2C_STATUS_M_ARB_LOST )
                                    {
                                        goto START;
                                    }
                                    else
                                    {
                                        if ( currentNumOfRetries < MAX_NACK_RETRIES )
                                        {
                                            currentNumOfRetries++;
                                            goto RET_1;
                                        }
                                        else
                                        {
                                            I2C_stop ();
                                            opResult = EXT_EEPROM_ERR_DATA_COM;
                                        }
                                    }
                                }
                            }
                            else
                            {
FINAL_DATA:
                                I2C_sendData ( *valuesToWrite );
                                currentStatus = I2C_readStatus ();
                                if ( currentStatus == I2C_STATUS_M_DATA_TRANS_ACK_REC )
                                {
                                    I2C_stop ();
                                }
                                else if ( currentStatus == I2C_STATUS_M_ARB_LOST )
                                {
                                    goto START;
                                }
                                else
                                {
                                    if ( currentNumOfRetries < MAX_NACK_RETRIES )
                                    {
                                        currentNumOfRetries++;
                                        goto FINAL_DATA;
                                    }
                                    else
                                    {
                                        I2C_stop ();
                                        opResult = EXT_EEPROM_ERR_DATA_COM;
                                    }
                                }
                            }
                        }
                    }
                    else if ( currentStatus == I2C_STATUS_M_ARB_LOST )
                    {
                        goto START;
                    }
                    else
                    {
                        if ( currentNumOfRetries < MAX_NACK_RETRIES )
                        {
                            currentNumOfRetries++;
                            goto LOW_ADDRESS;
                        }
                        else
                        {
                            I2C_stop ();
                            opResult = EXT_EEPROM_ERR_ADDR_COM;
                        }
                    }
                }
                else if ( currentStatus == I2C_STATUS_M_ARB_LOST )
                {
                    goto START;
                }
                else
                {
                    if ( currentNumOfRetries < MAX_NACK_RETRIES )
                    {
                        currentNumOfRetries++;
                        goto HIGH_ADDRESS;
                    }
                    else
                    {
                        I2C_stop ();
                        opResult = EXT_EEPROM_ERR_ADDR_COM;
                    }
                }
            }
            else if ( currentStatus == I2C_STATUS_M_ARB_LOST )
            {
                goto START;
            }
            else
            {
                I2C_stop ();
                opResult = EXT_EEPROM_ERR_CTRL_COM;
            }
        }
        else
        {
            opResult = EXT_EEPROM_ERR_START_COM;
        }
    }
    return opResult;
}
EXT_EEPROM_STD_ERR_t EXT_EEPROM_fill ( uint32_t addr , uint32_t writeSize , uint8_t fillValue )
{
    EXT_EEPROM_STD_ERR_t opResult = EXT_EEPROM_OK;
    if ( addr > MAX_EXT_EEPROM_ADDR )
    {
        opResult = EXT_EEPROM_ERR_ADDR;
    }
    else if ( ( addr + writeSize - ( uint8_t ) 1 ) > MAX_EXT_EEPROM_ADDR )
    {
        opResult = EXT_EEPROM_ERR_SIZE;
    }
    else if ( writeSize == ( uint8_t ) 0 )
    {
        /* Do nothing */
    }
    else
    {
        uint8_t controlByte;
        uint8_t highAddress;
        uint8_t lowAddress;
        uint32_t currentAddr = addr;
        uint8_t currentNumOfRetries;
        uint32_t i = 0;
        uint8_t currentByteNumber;
        I2C_STATUS_t currentStatus = I2C_STATUS_NONE;
SETUP:
        controlByte = CONTROL_ADDR | LEFT_SHIFT ( READ_BIT ( addr , 16 ) , 2 );
        highAddress = ( uint8_t ) READ_BITS_AND_SHIFT ( addr , HIGH_BYTE_MASK , 8 );
        lowAddress = ( uint8_t ) READ_BITS_AND_SHIFT ( addr , LOW_BYTE_MASK , 0 );
        EXT_EEPROM_waitBusy ();
START:
        currentNumOfRetries = 0;
        I2C_start ();
        currentStatus = I2C_readStatus ();
        if ( currentStatus == I2C_STATUS_START_TRANS )
        {
            I2C_sendAddrAndWrite ( controlByte );
            currentStatus = I2C_readStatus ();
            if ( currentStatus == I2C_STATUS_M_SLW_W_TRANS_ACK_REC )
            {
HIGH_ADDRESS:
                I2C_sendData ( highAddress );
                currentStatus = I2C_readStatus ();
                if ( currentStatus == I2C_STATUS_M_DATA_TRANS_ACK_REC )
                {
                    currentNumOfRetries = 0;
LOW_ADDRESS:
                    I2C_sendData ( lowAddress );
                    currentStatus = I2C_readStatus ();
                    if ( currentStatus == I2C_STATUS_M_DATA_TRANS_ACK_REC )
                    {
                        currentByteNumber = 0;
                        for ( ; i < writeSize; i++ )
                        {
                            currentNumOfRetries = 0;
                            if ( i + 1 != writeSize )
                            {
                                if ( ( currentByteNumber == 0 || currentByteNumber % 127 != 0 ) && currentAddr != PAGE_BOUNDRY )
                                {
RET_0:
                                    I2C_sendData ( fillValue );
                                    currentStatus = I2C_readStatus ();
                                    if ( currentStatus == I2C_STATUS_M_DATA_TRANS_ACK_REC )
                                    {
                                        currentAddr++;
                                        currentByteNumber++;
                                    }
                                    else if ( currentStatus == I2C_STATUS_M_ARB_LOST )
                                    {
                                        goto START;
                                    }
                                    else
                                    {
                                        if ( currentNumOfRetries < MAX_NACK_RETRIES )
                                        {
                                            currentNumOfRetries++;
                                            goto RET_0;
                                        }
                                        else
                                        {
                                            I2C_stop ();
                                            opResult = EXT_EEPROM_ERR_DATA_COM;
                                        }
                                    }
                                }
                                else
                                {
RET_1:
                                    I2C_sendData ( fillValue );
                                    currentStatus = I2C_readStatus ();
                                    if ( currentStatus == I2C_STATUS_M_DATA_TRANS_ACK_REC )
                                    {
                                        I2C_stop ();
                                        currentAddr++;
                                        i++;
                                        addr = currentAddr;
                                        goto SETUP;
                                    }
                                    else if ( currentStatus == I2C_STATUS_M_ARB_LOST )
                                    {
                                        goto START;
                                    }
                                    else
                                    {
                                        if ( currentNumOfRetries < MAX_NACK_RETRIES )
                                        {
                                            currentNumOfRetries++;
                                            goto RET_1;
                                        }
                                        else
                                        {
                                            I2C_stop ();
                                            opResult = EXT_EEPROM_ERR_DATA_COM;
                                        }
                                    }
                                }
                            }
                            else
                            {
FINAL_DATA:
                                I2C_sendData ( fillValue );
                                currentStatus = I2C_readStatus ();
                                if ( currentStatus == I2C_STATUS_M_DATA_TRANS_ACK_REC )
                                {
                                    I2C_stop ();
                                }
                                else if ( currentStatus == I2C_STATUS_M_ARB_LOST )
                                {
                                    goto START;
                                }
                                else
                                {
                                    if ( currentNumOfRetries < MAX_NACK_RETRIES )
                                    {
                                        currentNumOfRetries++;
                                        goto FINAL_DATA;
                                    }
                                    else
                                    {
                                        I2C_stop ();
                                        opResult = EXT_EEPROM_ERR_DATA_COM;
                                    }
                                }
                            }
                        }
                    }
                    else if ( currentStatus == I2C_STATUS_M_ARB_LOST )
                    {
                        goto START;
                    }
                    else
                    {
                        if ( currentNumOfRetries < MAX_NACK_RETRIES )
                        {
                            currentNumOfRetries++;
                            goto LOW_ADDRESS;
                        }
                        else
                        {
                            I2C_stop ();
                            opResult = EXT_EEPROM_ERR_ADDR_COM;
                        }
                    }
                }
                else if ( currentStatus == I2C_STATUS_M_ARB_LOST )
                {
                    goto START;
                }
                else
                {
                    if ( currentNumOfRetries < MAX_NACK_RETRIES )
                    {
                        currentNumOfRetries++;
                        goto HIGH_ADDRESS;
                    }
                    else
                    {
                        I2C_stop ();
                        opResult = EXT_EEPROM_ERR_ADDR_COM;
                    }
                }
            }
            else if ( currentStatus == I2C_STATUS_M_ARB_LOST )
            {
                goto START;
            }
            else
            {
                I2C_stop ();
                opResult = EXT_EEPROM_ERR_CTRL_COM;
            }
        }
        else
        {
            opResult = EXT_EEPROM_ERR_START_COM;
        }
    }
    return opResult;
}
EXT_EEPROM_STD_ERR_t EXT_EEPROM_copy ( uint32_t destAddr , uint32_t sourceAddr , uint32_t sizeToCopy )
{
    EXT_EEPROM_STD_ERR_t opResult = EXT_EEPROM_OK;
    uint8_t readValue;
    if ( destAddr > MAX_EXT_EEPROM_ADDR || sourceAddr > MAX_EXT_EEPROM_ADDR )
    {
        opResult = EXT_EEPROM_ERR_ADDR;
    }
    else
    {
        uint32_t leadingAddress = ( uint32_t ) 0;
        uint32_t trailingAddress = ( uint32_t ) 0;
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
        if ( trailingAddress <= MAX_EXT_EEPROM_ADDR && ( leadingAddress + sizeToCopy - ( uint8_t ) 1 ) > MAX_EXT_EEPROM_ADDR )
        {
            opResult = EXT_EEPROM_ERR_SIZE;
        }
        else if ( sizeToCopy == 0 || destAddr == sourceAddr )
        {
            /* Do nothing */
        }
        else if ( sourceAddr < destAddr && sourceAddr + sizeToCopy > destAddr )
        {
            uint32_t i;
            for ( i = sizeToCopy - ( uint8_t ) 1;; i-- )
            {
                opResult = read ( sourceAddr + i , &readValue );
                opResult = write ( destAddr + i , readValue );
                if ( i == 0 )
                {
                    break;
                }
            }
        }
        else
        {
            uint32_t i;
            for ( i = ( uint32_t ) 0; i < sizeToCopy; i++ )
            {
                opResult = read ( sourceAddr + i , &readValue );
                opResult = write ( destAddr + i , readValue );
            }
        }
    }
    return opResult;
}
EXT_EEPROM_STD_ERR_t EXT_EEPROM_move ( uint32_t destAddr , uint32_t sourceAddr , uint32_t sizeToMove )
{
    EXT_EEPROM_STD_ERR_t opResult = EXT_EEPROM_OK;
    uint8_t readValue;
    if ( destAddr > MAX_EXT_EEPROM_ADDR || sourceAddr > MAX_EXT_EEPROM_ADDR )
    {
        opResult = EXT_EEPROM_ERR_ADDR;
    }
    else
    {
        uint32_t leadingAddress = ( uint32_t ) 0;
        uint32_t trailingAddress = ( uint32_t ) 0;
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
        if ( ( trailingAddress <= MAX_EXT_EEPROM_ADDR && ( leadingAddress + sizeToMove - ( uint8_t ) 1 ) > MAX_EXT_EEPROM_ADDR ) )
        {
            opResult = EXT_EEPROM_ERR_SIZE;
        }
        else if ( sizeToMove == 0 || destAddr == sourceAddr )
        {
            /* Do nothing */
        }
        else if ( sourceAddr < destAddr && sourceAddr + sizeToMove > destAddr )
        {
            uint32_t i;
            for ( i = sizeToMove - ( uint8_t ) 1;; i-- )
            {
                opResult = read ( sourceAddr + i , &readValue );
                opResult = write ( destAddr + i , readValue );
                if ( i == 0 )
                {
                    break;
                }
            }
            for ( i = 0; i < destAddr - sourceAddr; i++ )
            {
                opResult = write ( sourceAddr + i , EMPTY_EEPROM_VALUE );
            }
        }
        else
        {
            uint32_t i;
            for ( i = ( uint32_t ) 0; i < sizeToMove; i++ )
            {
                opResult = read ( sourceAddr + i , &readValue );
                opResult = write ( destAddr + i , readValue );
            }
            for ( i = 0; i < sourceAddr - destAddr; i++ )
            {
                opResult = write ( destAddr + sizeToMove + i , EMPTY_EEPROM_VALUE );
            }
        }
    }
    return opResult;
}
