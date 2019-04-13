#ifndef AMIT_PROJECT_TIMER_H_
#define AMIT_PROJECT_TIMER_H_
#ifndef F_CPU
    #error "CPU clock frequency not defined"
#endif
#include "common.h"
typedef void (* CallbackFunc) ( void );
#define NULL_TIMER_CALLBACK ( ( CallbackFunc ) 0 )
typedef enum _TIMER_t
{
    TIMER_0 = ( uint8_t ) 0 ,
    TIMER_1A = ( uint8_t ) 1 ,
    TIMER_1B = ( uint8_t ) 2 ,
    TIMER_1 = ( uint8_t ) 3 ,
    TIMER_2 = ( uint8_t ) 4 ,
    NUM_OF_TIMERS
} TIMER_t;
typedef enum _DELAY_t
{
    DELAY_POLLING = ( uint8_t ) 0 ,
    DELAY_INTERRUPT = ( uint8_t ) 1
} DELAY_t;
typedef enum _TIMER_FLAG_t
{
    TIMER_FLAG_OCR = ( uint8_t ) 0 ,
    TIMER_FLAG_OV = ( uint8_t ) 1 ,
    TIMER_FLAG_IC = ( uint8_t ) 2
} TIMER_FLAG_t;
typedef enum _TIMER_MODE_t
{
    TIMER_MODE_NORMAL = ( uint8_t ) 0 ,
    TIMER_MODE_CTC_OCR_TOP = ( uint8_t ) 1 ,
    TIMER_MODE_CTC_ICR_TOP = ( uint8_t ) 2 ,
    TIMER_MODE_FAST_PWM_0xFF_TOP = ( uint8_t ) 3 ,
    TIMER_MODE_FAST_PWM_0x1FF_TOP = ( uint8_t ) 4 ,
    TIMER_MODE_FAST_PWM_0x3FF_TOP = ( uint8_t ) 5 ,
    TIMER_MODE_FAST_PWM_OCR_TOP = ( uint8_t ) 6 ,
    TIMER_MODE_FAST_PWM_ICR_TOP = ( uint8_t ) 7 ,
    TIMER_MODE_FAST_PWM_MAX_TOP = ( uint8_t ) 8 ,
    TIMER_MODE_PHASE_PWM_0xFF_TOP = ( uint8_t ) 9 ,
    TIMER_MODE_PHASE_PWM_0x1FF_TOP = ( uint8_t ) 10 ,
    TIMER_MODE_PHASE_PWM_0x3FF_TOP = ( uint8_t ) 11 ,
    TIMER_MODE_PHASE_PWM_OCR_TOP = ( uint8_t ) 12 ,
    TIMER_MODE_PHASE_PWM_ICR_TOP = ( uint8_t ) 13 ,
    TIMER_MODE_PHASE_PWM_MAX_TOP = ( uint8_t ) 14 ,
    TIMER_MODE_PHASE_FREQ_PWM_OCR_TOP = ( uint8_t ) 15 ,
    TIMER_MODE_PHASE_FREQ_PWM_ICR_TOP = ( uint8_t ) 16
} TIMER_MODE_t;
typedef enum _TIMER_CTC_SETTING_t
{
    CTC_NORMAL = ( uint8_t ) 0 ,
    CTC_TOGGLE = ( uint8_t ) 1 ,
    CTC_CLEAR = ( uint8_t ) 2 ,
    CTC_SET = ( uint8_t ) 3
} TIMER_CTC_SETTING_t;
typedef enum _TIMER_FAST_PWM_SETTING_t
{
    FAST_PWM_NORMAL = ( uint8_t ) 0 ,
    FAST_PWM_TOGGLE = ( uint8_t ) 1 ,
    FAST_PWM_CLEAR_MATCH_SET_BOTTOM = ( uint8_t ) 2 ,
    FAST_PWM_SET_MATCH_CLEAR_BOTTOM = ( uint8_t ) 3 ,
} TIMER_FAST_PWM_SETTING_t;
typedef enum _TIMER_CORRECT_PWM_SETTING_t
{
    CORRECT_PWM_NORMAL = ( uint8_t ) 0 ,
    CORRECT_PWM_CORRECT = ( uint8_t ) 1 ,
    CORRECT_PWM_CLEAR_MATCH_UP_SET_MATCH_DOWN = ( uint8_t ) 2 ,
    CORRECT_PWM_SET_MATCH_UP_CLEAR_MATCH_DOWN = ( uint8_t ) 3 ,
} TIMER_CORRECT_PWM_SETTING_t;
typedef enum _TIMER_CLCK_t
{
    TIMER_CLCK_NO = ( uint8_t ) 0 ,
    TIMER_CLCK_PRESC_1 = ( uint8_t ) 1 ,
    TIMER_CLCK_PRESC_8 = ( uint8_t ) 2 ,
    TIMER_CLCK_PRESC_64 = ( uint8_t ) 3 ,
    TIMER_CLCK_PRESC_256 = ( uint8_t ) 4 ,
    TIMER_CLCK_PRESC_1024 = ( uint8_t ) 5 ,
    TIMER_CLCK_EXTERNAL_FALLING = ( uint8_t ) 6 ,
    TIMER_CLCK_EXTERNAL_RISING = ( uint8_t ) 7
} TIMER_CLCK_t;
typedef union _TIMER_GENERIC_SETTING_t
{
    TIMER_CTC_SETTING_t ctcSetting;
    TIMER_FAST_PWM_SETTING_t fastPwmSetting;
    TIMER_CORRECT_PWM_SETTING_t correctPwmSetting;
} TIMER_GENERIC_SETTING_t;
typedef enum _TIMER_STD_ERR_t
{
    TIMER_OK = ( uint8_t ) 0 ,
    TIMER_ERR_TIMER_NUM = ( uint8_t ) 1 ,
    TIMER_ERR_MODE = ( uint8_t ) 2 ,
    TIMER_ERR_CTC_SETTING = ( uint8_t ) 3 ,
    TIMER_ERR_FAST_PWM_SETTING = ( uint8_t ) 4 ,
    TIMER_ERR_CORRECT_PWM_SETTING = ( uint8_t ) 5 ,
    TIMER_ERR_PRESCALER = ( uint8_t ) 6 ,
    TIMER_ERR_FLAG_TYPE = ( uint8_t ) 7 ,
    TIMER_ERR_OCR = ( uint8_t ) 8 ,
    TIMER_ERR_CTC = ( uint8_t ) 9 ,
    TIMER_ERR_TIMER_VALUE = ( uint8_t ) 10
} TIMER_STD_ERR_t;
TIMER_STD_ERR_t TIMER_setInterruptState ( TIMER_t timer , TIMER_FLAG_t flagType );
TIMER_STD_ERR_t TIMER_clearInterruptState ( TIMER_t timer , TIMER_FLAG_t flagType );
TIMER_STD_ERR_t TIMER_getInterruptState ( TIMER_t timer , TIMER_FLAG_t flagType , INT_STATE_t* outputState );
TIMER_STD_ERR_t TIMER_clearInterruptFlag ( TIMER_t timer , TIMER_FLAG_t flagType );
TIMER_STD_ERR_t TIMER_getInterruptFlag ( TIMER_t timer , TIMER_FLAG_t flagType , FLAG_STATE_t* outputFlagState );
TIMER_STD_ERR_t TIMER_forceOcrMatch ( TIMER_t timer );
TIMER_STD_ERR_t TIMER_setOcr ( TIMER_t timer , uint16_t ocrValue );
TIMER_STD_ERR_t TIMER_setPrescaller ( TIMER_t timer , TIMER_CLCK_t clockSetting );
TIMER_STD_ERR_t TIMER_getPrescaller ( TIMER_t timer , TIMER_CLCK_t* outputClockSetting );
TIMER_STD_ERR_t TIMER_setMode ( TIMER_t timer , TIMER_MODE_t modeToSet );
TIMER_STD_ERR_t TIMER_setCtcSetting ( TIMER_t timer , TIMER_CTC_SETTING_t settingToSet );
TIMER_STD_ERR_t TIMER_setFastPwmSetting ( TIMER_t timer , TIMER_FAST_PWM_SETTING_t settingToSet );
TIMER_STD_ERR_t TIMER_setCorrectPwmSetting ( TIMER_t timer , TIMER_CORRECT_PWM_SETTING_t settingToSet );
TIMER_STD_ERR_t TIMER_read ( TIMER_t timer , uint16_t* timerValue );
TIMER_STD_ERR_t TIMER_write ( TIMER_t timer , uint16_t timerValue );
#endif
