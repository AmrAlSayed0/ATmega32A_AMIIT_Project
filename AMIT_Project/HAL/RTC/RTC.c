#include <util/delay.h>
#include "bit_helpers.h"
#include "I2C.h"
#include "RTC.h"
#include "RTC_config.h"
#include "RTC_private.h"
#define MAX_REG_ADDR ( ( uint8_t ) 0x13 )
#define RTC_I2C_ADDR ( 0x68 ) //01101000
#define TIME_REGS_COUNT 7
#define RESET_REG_VALUE ( ( uint8_t ) 0x58 )
//
#define SECONDS_TENS_MASK   BIT_MASK3 ( SECONDS_TENS_2 , SECONDS_TENS_1 , SECONDS_TENS_0 )
#define SECONDS_UNITS_MASK  BIT_MASK4 ( SECONDS_UNITS_3, SECONDS_UNITS_2 , SECONDS_UNITS_1 , SECONDS_UNITS_0 )
//
#define MINUTES_TENS_MASK   BIT_MASK3 ( MINUTES_TENS_2 , MINUTES_TENS_1 , MINUTES_TENS_0 )
#define MINUTES_UNITS_MASK  BIT_MASK4 ( MINUTES_UNITS_3, MINUTES_UNITS_2 , MINUTES_UNITS_1 , MINUTES_UNITS_0 )
//
#define HOURS_TENS_MASK     BIT_MASK2 ( HOURS_24_TENS_1 , HOURS_24_TENS_0 )
#define HOURS_UNITS_MASK    BIT_MASK4 ( HOURS_24_UNITS_3 , HOURS_24_UNITS_2 , HOURS_24_UNITS_1 , HOURS_24_UNITS_0 )
//
#define DAYS_TENS_MASK      BIT_MASK2 ( DAYS_TENS_1 , DAYS_TENS_0 )
#define DAYS_UNITS_MASK     BIT_MASK4 ( DAYS_UNITS_3 , DAYS_UNITS_2 , DAYS_UNITS_1 , DAYS_UNITS_0 )
//
#define WEEKDAYS_MASK       BIT_MASK3 ( WEEKDAYS_2 , WEEKDAYS_1 , WEEKDAYS_0 )
//
#define MONTHS_TENS_MASK    BIT_MASK1 ( MONTHS_TENS )
#define MONTHS_UNITS_MASK   BIT_MASK4 ( MONTHS_UNITS_3 , MONTHS_UNITS_2 , MONTHS_UNITS_1 , MONTHS_UNITS_0 )
//
#define YEARS_TENS          BIT_MASK4 ( YEARS_TENS_3 , YEARS_TENS_2 , YEARS_TENS_1 , YEARS_TENS_0 )
#define YEARS_UNITS         BIT_MASK4 ( YEARS_UNITS_3 , YEARS_UNITS_2 , YEARS_UNITS_1 , YEARS_UNITS_0 )
RTC_STD_ERR_t RTC_reset ()
{
    RTC_STD_ERR_t opResult = RTC_OK;
    opResult = RTC_writeReg ( CONTROL_1 , RESET_REG_VALUE );
    return opResult;
}
RTC_STD_ERR_t RTC_getInterruptState ( RTC_INT_t interruptType , INT_STATE_t* interruptState )
{
    RTC_STD_ERR_t opResult = RTC_OK;
    uint8_t regAddrToRead;
    uint8_t bitNumToRead;
    switch ( interruptType )
    {
        case RTC_INT_ALARM :
            regAddrToRead = CONTROL_1;
            bitNumToRead = CONTROL_1_AIE;
            break;
        case RTC_INT_FIRST :
        case RTC_INT_SECOND :
            regAddrToRead = CONTROL_1;
            bitNumToRead = CONTROL_1_SIE;
            break;
        case RTC_INT_CORRECTION :
            regAddrToRead = CONTROL_1;
            bitNumToRead = CONTROL_1_CIE;
            break;
        case RTC_INT_WTCHDG :
            regAddrToRead = CONTROL_2;
            bitNumToRead = CONTROL_2_WTAIE;
            break;
        case RTC_INT_TIMER_A :
            regAddrToRead = CONTROL_2;
            bitNumToRead = CONTROL_2_CTAIE;
            break;
        case RTC_INT_TIMER_B :
            regAddrToRead = CONTROL_2;
            bitNumToRead = CONTROL_2_CTBIE;
            break;
        case RTC_INT_BAT_SWITCH :
            regAddrToRead = CONTROL_3;
            bitNumToRead = CONTROL_3_BSIE;
            break;
        case RTC_INT_BAT_LOW :
            regAddrToRead = CONTROL_3;
            bitNumToRead = CONTROL_3_BLIE;
            break;
        default:
            opResult = RTC_ERR_INT;
    }
    if ( opResult == RTC_OK )
    {
        uint8_t readValue;
        opResult = RTC_readReg ( regAddrToRead , &readValue );
        if ( opResult == RTC_OK )
        {
            *interruptState = ( INT_STATE_t ) READ_BIT ( readValue , bitNumToRead );
        }
    }
    return opResult;
}
RTC_STD_ERR_t RTC_setInterruptState ( RTC_INT_t interruptType , INT_STATE_t interruptState )
{
    RTC_STD_ERR_t opResult = RTC_OK;
    uint8_t regAddrToChange;
    uint8_t bitNumToChange;
    switch ( interruptType )
    {
        case RTC_INT_ALARM :
            regAddrToChange = CONTROL_1;
            bitNumToChange = CONTROL_1_AIE;
            break;
        case RTC_INT_FIRST :
        case RTC_INT_SECOND :
            regAddrToChange = CONTROL_1;
            bitNumToChange = CONTROL_1_SIE;
            break;
        case RTC_INT_CORRECTION :
            regAddrToChange = CONTROL_1;
            bitNumToChange = CONTROL_1_CIE;
            break;
        case RTC_INT_WTCHDG :
            regAddrToChange = CONTROL_2;
            bitNumToChange = CONTROL_2_WTAIE;
            break;
        case RTC_INT_TIMER_A :
            regAddrToChange = CONTROL_2;
            bitNumToChange = CONTROL_2_CTAIE;
            break;
        case RTC_INT_TIMER_B :
            regAddrToChange = CONTROL_2;
            bitNumToChange = CONTROL_2_CTBIE;
            break;
        case RTC_INT_BAT_SWITCH :
            regAddrToChange = CONTROL_3;
            bitNumToChange = CONTROL_3_BSIE;
            break;
        case RTC_INT_BAT_LOW :
            regAddrToChange = CONTROL_3;
            bitNumToChange = CONTROL_3_BLIE;
            break;
        default:
            opResult = RTC_ERR_INT;
    }
    if ( opResult == RTC_OK )
    {
        uint8_t regValue;
        opResult = RTC_readReg ( regAddrToChange , &regValue );
        if ( opResult == RTC_OK )
        {
            REPLACE_BIT ( regValue , bitNumToChange , ( uint8_t ) interruptState );
            opResult = RTC_writeReg ( regAddrToChange , regValue );
        }
    }
    return opResult;
}
RTC_STD_ERR_t RTC_readReg ( uint8_t addr , uint8_t* readValue )
{
    RTC_STD_ERR_t opResult = RTC_OK;
    if ( addr <= MAX_REG_ADDR )
    {
        I2C_STATUS_t currentStatus = I2C_STATUS_NO_INFO;
        uint8_t currentNumOfRetries;
START:
        currentNumOfRetries = 0;
        I2C_start ();
        currentStatus = I2C_readStatus ();
        if ( currentStatus == I2C_STATUS_START_TRANS )
        {
            I2C_sendAddrAndWrite ( RTC_I2C_ADDR );
            currentStatus = I2C_readStatus ();
            if ( currentStatus == I2C_STATUS_M_SLW_W_TRANS_ACK_REC )
            {
ADDRESS:
                I2C_sendData ( addr );
                currentStatus = I2C_readStatus ();
                if ( currentStatus == I2C_STATUS_M_DATA_TRANS_ACK_REC )
                {
                    currentNumOfRetries = 0;
                    I2C_stop ();
SEC_START:
                    I2C_start ();
                    currentStatus = I2C_readStatus ();
                    if ( currentStatus == I2C_STATUS_START_TRANS )
                    {
                        I2C_sendAddrAndRead ( RTC_I2C_ADDR );
                        currentStatus = I2C_readStatus ();
                        if ( currentStatus == I2C_STATUS_M_SLW_R_TRANS_ACK_REC )
                        {
                            *readValue = I2C_receiveDataWithNack ();
                            I2C_stop ();
                        }
                        else if ( currentStatus == I2C_STATUS_M_ARB_LOST )
                        {
                            goto SEC_START;
                        }
                        else
                        {
                            if ( currentNumOfRetries < MAX_NACK_RETRIES )
                            {
                                currentNumOfRetries++;
                                goto SEC_START;
                            }
                            else
                            {
                                I2C_stop ();
                                opResult = RTC_ERR_CTRL_COM;
                            }
                        }
                    }
                    else
                    {
                        I2C_stop ();
                        opResult = RTC_ERR_START_COM;
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
                        goto ADDRESS;
                    }
                    else
                    {
                        I2C_stop ();
                        opResult = RTC_ERR_ADDR_COM;
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
                opResult = RTC_ERR_CTRL_COM;
            }
        }
        else
        {
            opResult = RTC_ERR_START_COM;
        }
    }
    else
    {
        opResult = RTC_ERR_REG_ADDR;
    }
    return opResult;
}
RTC_STD_ERR_t RTC_readRegs ( uint8_t addr , uint8_t readSize , uint8_t readValues[readSize] )
{
    RTC_STD_ERR_t opResult = RTC_OK;
    if ( addr > MAX_REG_ADDR )
    {
        opResult = RTC_ERR_ADDR;
    }
    else if ( ( addr + readSize - ( uint8_t ) 1 ) > MAX_REG_ADDR )
    {
        opResult = RTC_ERR_SIZE;
    }
    else if ( readSize == ( uint8_t ) 0 )
    {
        /* Do nothing */
    }
    else
    {
        I2C_STATUS_t currentStatus = I2C_STATUS_NO_INFO;
        uint8_t i = 0;
        uint8_t currentNumOfRetries;
START:
        currentNumOfRetries = 0;
        I2C_start ();
        currentStatus = I2C_readStatus ();
        if ( currentStatus == I2C_STATUS_START_TRANS )
        {
            I2C_sendAddrAndWrite ( RTC_I2C_ADDR );
            currentStatus = I2C_readStatus ();
            if ( currentStatus == I2C_STATUS_M_SLW_W_TRANS_ACK_REC )
            {
ADDRESS:
                I2C_sendData ( addr );
                currentStatus = I2C_readStatus ();
                if ( currentStatus == I2C_STATUS_M_DATA_TRANS_ACK_REC )
                {
                    currentNumOfRetries = 0;
                    I2C_stop ();
SEC_START:
                    I2C_start ();
                    currentStatus = I2C_readStatus ();
                    if ( currentStatus == I2C_STATUS_START_TRANS )
                    {
                        I2C_sendAddrAndRead ( RTC_I2C_ADDR );
                        currentStatus = I2C_readStatus ();
                        if ( currentStatus == I2C_STATUS_M_SLW_R_TRANS_ACK_REC )
                        {
                            currentNumOfRetries = 0;
                            for ( ; i < readSize; i++ )
                            {
                                if ( i + 1 != readSize )
                                {
                                    *readValues = I2C_receiveDataWithAck ();
                                    readValues++;
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
                            goto SEC_START;
                        }
                        else
                        {
                            if ( currentNumOfRetries < MAX_NACK_RETRIES )
                            {
                                currentNumOfRetries++;
                                goto SEC_START;
                            }
                            else
                            {
                                I2C_stop ();
                                opResult = RTC_ERR_CTRL_COM;
                            }
                        }
                    }
                    else
                    {
                        I2C_stop ();
                        opResult = RTC_ERR_START_COM;
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
                        goto ADDRESS;
                    }
                    else
                    {
                        I2C_stop ();
                        opResult = RTC_ERR_ADDR_COM;
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
                opResult = RTC_ERR_CTRL_COM;
            }
        }
        else
        {
            opResult = RTC_ERR_START_COM;
        }
    }
    return opResult;
}
RTC_STD_ERR_t RTC_writeReg ( uint8_t addr , uint8_t writeValue )
{
    RTC_STD_ERR_t opResult = RTC_OK;
    if ( addr <= MAX_REG_ADDR )
    {
        uint8_t currentNumOfRetries;
        I2C_STATUS_t currentStatus = I2C_STATUS_NO_INFO;
START:
        currentNumOfRetries = 0;
        I2C_start ();
        currentStatus = I2C_readStatus ();
        if ( currentStatus == I2C_STATUS_START_TRANS )
        {
            I2C_sendAddrAndWrite ( RTC_I2C_ADDR );
            currentStatus = I2C_readStatus ();
            if ( currentStatus == I2C_STATUS_M_SLW_W_TRANS_ACK_REC )
            {
ADDRESS:
                I2C_sendData ( addr );
                currentStatus = I2C_readStatus ();
                if ( currentStatus == I2C_STATUS_M_DATA_TRANS_ACK_REC )
                {
                    currentNumOfRetries = 0;
DATA:
                    I2C_sendData ( writeValue );
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
                            opResult = RTC_ERR_DATA_COM;
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
                        goto ADDRESS;
                    }
                    else
                    {
                        I2C_stop ();
                        opResult = RTC_ERR_ADDR_COM;
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
                opResult = RTC_ERR_CTRL_COM;
            }
        }
        else
        {
            opResult = RTC_ERR_START_COM;
        }
    }
    else
    {
        opResult = RTC_ERR_REG_ADDR;
    }
    return opResult;
}
RTC_STD_ERR_t RTC_writeRegs ( uint8_t addr , uint8_t writeSize , uint8_t writeValues[writeSize] )
{
    RTC_STD_ERR_t opResult = RTC_OK;
    if ( addr > MAX_REG_ADDR )
    {
        opResult = RTC_ERR_ADDR;
    }
    else if ( ( addr + writeSize - ( uint8_t ) 1 ) > MAX_REG_ADDR )
    {
        opResult = RTC_ERR_SIZE;
    }
    else if ( writeSize == ( uint8_t ) 0 )
    {
        /* Do nothing */
    }
    else
    {
        uint8_t i = 0;
        uint8_t currentNumOfRetries;
        I2C_STATUS_t currentStatus = I2C_STATUS_NO_INFO;
START:
        currentNumOfRetries = 0;
        I2C_start ();
        currentStatus = I2C_readStatus ();
        if ( currentStatus == I2C_STATUS_START_TRANS )
        {
            I2C_sendAddrAndWrite ( RTC_I2C_ADDR );
            currentStatus = I2C_readStatus ();
            if ( currentStatus == I2C_STATUS_M_SLW_W_TRANS_ACK_REC )
            {
ADDRESS:
                I2C_sendData ( addr );
                currentStatus = I2C_readStatus ();
                if ( currentStatus == I2C_STATUS_M_DATA_TRANS_ACK_REC )
                {
                    for ( ; i < writeSize; i++ )
                    {
                        currentNumOfRetries = 0;
                        if ( i + 1 != writeSize )
                        {
DATA:
                            I2C_sendData ( *writeValues );
                            currentStatus = I2C_readStatus ();
                            if ( currentStatus == I2C_STATUS_M_DATA_TRANS_ACK_REC )
                            {
                                writeValues++;
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
                                    opResult = RTC_ERR_DATA_COM;
                                }
                            }
                        }
                        else
                        {
FINAL_DATA:
                            I2C_sendData ( *writeValues );
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
                                    opResult = RTC_ERR_DATA_COM;
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
                        goto ADDRESS;
                    }
                    else
                    {
                        I2C_stop ();
                        opResult = RTC_ERR_ADDR_COM;
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
                opResult = RTC_ERR_CTRL_COM;
            }
        }
        else
        {
            opResult = RTC_ERR_START_COM;
        }
    }
    return opResult;
}
RTC_STD_ERR_t RTC_getTime ( TIME_t* time )
{
    RTC_STD_ERR_t opResult = RTC_OK;
    uint8_t timeRegs[TIME_REGS_COUNT];
    opResult = RTC_readRegs ( SECONDS , TIME_REGS_COUNT , timeRegs );
    if ( opResult == RTC_OK )
    {
        time->seconds = ( uint8_t ) ( ( READ_BITS_AND_SHIFT ( timeRegs[ 0 ] , SECONDS_TENS_MASK , SECONDS_TENS_0 ) * 10 ) + READ_BITS_AND_SHIFT ( timeRegs[ 0 ] , SECONDS_UNITS_MASK , SECONDS_UNITS_0 ) );
        time->minutes = ( uint8_t ) ( ( READ_BITS_AND_SHIFT ( timeRegs[ 1 ] , MINUTES_TENS_MASK , MINUTES_TENS_0 ) * 10 ) + READ_BITS_AND_SHIFT ( timeRegs[ 1 ] , MINUTES_UNITS_MASK , MINUTES_UNITS_0 ) );
        time->hours = ( uint8_t ) ( ( READ_BITS_AND_SHIFT ( timeRegs[ 2 ] , HOURS_TENS_MASK , HOURS_24_TENS_0 ) * 10 ) + READ_BITS_AND_SHIFT ( timeRegs[ 2 ] , HOURS_UNITS_MASK , HOURS_24_UNITS_0 ) );
        time->days = ( uint8_t ) ( ( READ_BITS_AND_SHIFT ( timeRegs[ 3 ] , DAYS_TENS_MASK , DAYS_TENS_0 ) * 10 ) + READ_BITS_AND_SHIFT ( timeRegs[ 3 ] , DAYS_UNITS_MASK , DAYS_UNITS_0 ) );
        time->weekDay = ( uint8_t ) READ_BITS_AND_SHIFT ( timeRegs[ 4 ] , WEEKDAYS_MASK , WEEKDAYS_0 );
        time->month = ( uint8_t ) ( ( READ_BITS_AND_SHIFT ( timeRegs[ 5 ] , MONTHS_TENS_MASK , MONTHS_TENS ) * 10 ) + READ_BITS_AND_SHIFT ( timeRegs[ 5 ] , MONTHS_UNITS_MASK , MONTHS_UNITS_0 ) );
        time->year = ( uint8_t ) ( ( READ_BITS_AND_SHIFT ( timeRegs[ 6 ] , YEARS_TENS , YEARS_TENS_0 ) * 10 ) + READ_BITS_AND_SHIFT ( timeRegs[ 6 ] , YEARS_UNITS , YEARS_UNITS_0 ) );
    }
    return opResult;
}

