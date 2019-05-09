#ifndef AMIT_PROJECT_RTC_H_
#define AMIT_PROJECT_RTC_H_
//PCF8523
#include "common.h"
typedef enum _RTC_CAP_t
{
    RTC_CAP_7pF = ( uint8_t ) 0 ,
    RTC_CAP_12p5F = ( uint8_t ) 1
} RTC_CAP_t;
typedef enum _RTC_TIME_MODE_t
{
    RTC_TIME_MODE_24_HR = ( uint8_t ) 0 ,
    RTC_TIME_MODE_12_HR = ( uint8_t ) 1
} RTC_TIME_MODE_t;
typedef enum _RTC_INT_t
{
    RTC_INT_ALARM = ( uint8_t ) 0 ,
    RTC_INT_FIRST = ( uint8_t ) 1 ,
    RTC_INT_SECOND = ( uint8_t ) 2 ,
    RTC_INT_CORRECTION = ( uint8_t ) 3 ,
    RTC_INT_WTCHDG = ( uint8_t ) 4 ,
    RTC_INT_TIMER_A = ( uint8_t ) 5 ,
    RTC_INT_TIMER_B = ( uint8_t ) 6 ,
    RTC_INT_BAT_SWITCH = ( uint8_t ) 7 ,
    RTC_INT_BAT_LOW = ( uint8_t ) 8
} RTC_INT_t;
typedef enum _RTC_SWITCH_MODE_t
{
    RTC_SWITCH_ENABLED_STD_MODE = ( uint8_t ) 0 ,
    RTC_SWITCH_ENABLED_DIRECT_MODE = ( uint8_t ) 1 ,
    RTC_SWITCH_DISABLED_POWER_ONLY = ( uint8_t ) 2
} RTC_SWITCH_MODE_t;
typedef enum _RTC_BAT_LOW_DETECT_t
{
    RTC_BAT_LOW_DETECT_DISABLED = ( uint8_t ) 0 ,
    RTC_BAT_LOW_DETECT_ENABLED = ( uint8_t ) 1
} RTC_BAT_LOW_DETECT_t;
typedef enum _RTC_BATTERY_STATUS_t
{
    RTC_BATTERY_STATUS_OK ,
    RTC_BATTERY_STATUS_LOW
} RTC_BATTERY_STATUS_t;
typedef enum _RTC_INT_SIGNAL_t
{
    RTC_INT_SIGNAL_PERM ,
    RTC_INT_SIGNAL_PULSE
} RTC_INT_SIGNAL_t;
typedef enum _RTC_CLCK_FREQ_t
{
    RTC_CLCK_FREQ_32768 ,
    RTC_CLCK_FREQ_16384 ,
    RTC_CLCK_FREQ_8192 ,
    RTC_CLCK_FREQ_4096 ,
    RTC_CLCK_FREQ_1024 ,
    RTC_CLCK_FREQ_32 ,
    RTC_CLCK_FREQ_1 ,
    RTC_CLCK_FREQ_DISABLED ,
} RTC_CLCK_FREQ_t;
typedef enum _TIME_OF_DAY_t
{
    TIME_OF_DAY_AM = ( uint8_t ) 0 ,
    TIME_OF_DAY_PM = ( uint8_t ) 1
} TIME_OF_DAY_t;
typedef enum _RTC_ALARM_t
{
    RTC_ALARM_MINUTE ,
    RTC_ALARM_HOUR ,
    RTC_ALARM_DAY ,
    RTC_ALARM_WEEKDAY
} RTC_ALARM_t;
typedef enum _RTC_ALARM_STATUS_t
{
    RTC_ALARM_STATUS_DISABLED ,
    RTC_ALARM_STATUS_ENABLED ,
} RTC_ALARM_STATUS_t;
typedef enum _RTC_OFFSET_MODE_t
{
    RTC_OFFSET_MODE_2_HOURS ,
    RTC_OFFSET_MODE_MINUTE
} RTC_OFFSET_MODE_t;
typedef enum _RTC_TIMER_t
{
    RTC_TIMER_A ,
    RTC_TIMER_B ,
} RTC_TIMER_t;
typedef struct _TIME_t
{
    uint8_t seconds:6;
    uint8_t minutes:6;
    uint8_t hours:5;
    uint8_t days:5;
    uint8_t weekDay:3;
    uint8_t month:4;
    uint8_t year:7;
} TIME_t;
typedef enum _RTC_STD_ERR_t
{
    RTC_OK ,
    RTC_ERR_REG_ADDR ,
    RTC_ERR_START_COM ,
    RTC_ERR_CTRL_COM ,
    RTC_ERR_ADDR_COM ,
    RTC_ERR_DATA_COM ,
    RTC_ERR_ADDR ,
    RTC_ERR_SIZE ,
    RTC_ERR_INT
} RTC_STD_ERR_t;
//RTC_STD_ERR_t RTC_stop ();
RTC_STD_ERR_t RTC_reset ();
//RTC_STD_ERR_t RTC_getTimeMode ( RTC_TIME_MODE_t* timeMode );
//RTC_STD_ERR_t RTC_setTimeMode ( RTC_TIME_MODE_t timeMode );
RTC_STD_ERR_t RTC_getInterruptState ( RTC_INT_t interruptType , INT_STATE_t* interruptState );
RTC_STD_ERR_t RTC_setInterruptState ( RTC_INT_t interruptType , INT_STATE_t interruptState );
//RTC_STD_ERR_t RTC_getBatteryState ( RTC_BATTERY_STATUS_t* batteryStatus );
RTC_STD_ERR_t RTC_getTime ( TIME_t* time );
//RTC_STD_ERR_t RTC_setTime ( TIME_t* time );
//RTC_STD_ERR_t RTC_setAlarmState ( RTC_ALARM_t alarmType , RTC_ALARM_STATUS_t alarmStatus );
//RTC_STD_ERR_t RTC_getAlarmState ( RTC_ALARM_t alarmType , RTC_ALARM_STATUS_t* alarmStatus );
//RTC_STD_ERR_t RTC_setAlarmValue ( RTC_ALARM_t alarmType , void* alarmValue );
//RTC_STD_ERR_t RTC_getOffsetMode ( RTC_OFFSET_MODE_t* offsetMode );
//RTC_STD_ERR_t RTC_setOffsetMode ( RTC_OFFSET_MODE_t offsetMode );
//RTC_STD_ERR_t RTC_getOffsetValue ( uint8_t* offsetValue );
//RTC_STD_ERR_t RTC_setOffsetValue ( uint8_t offsetValue );
RTC_STD_ERR_t RTC_readReg ( uint8_t addr , uint8_t* readValue );
RTC_STD_ERR_t RTC_readRegs ( uint8_t addr , uint8_t readSize , uint8_t readValues[readSize] );
RTC_STD_ERR_t RTC_writeReg ( uint8_t addr , uint8_t writeValue );
RTC_STD_ERR_t RTC_writeRegs ( uint8_t addr , uint8_t writeSize , uint8_t writeValues[writeSize] );
#endif
