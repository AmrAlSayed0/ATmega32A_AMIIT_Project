#include <avr/interrupt.h>
#include <math.h>
#include "bit_helpers.h"
#include "TIMER_private.h"
#include "TIMER_config.h"
#include "TIMER.h"
#define MAX_SMALL_OCR_VALUE     ( ( uint8_t ) 0xFF )
#define MAX_SMALL_TIMER_VALUE   ( ( uint8_t ) 0xFF )
TIMER_STD_ERR_t TIMER_setInterruptState ( TIMER_t timer , TIMER_FLAG_t flagType )
{
    TIMER_STD_ERR_t opResult = TIMER_OK;
    switch ( timer )
    {
        case TIMER_0 :
            switch ( flagType )
            {
                case TIMER_FLAG_OCR :
                    SET_BIT ( TIMSK , OCIE0 );
                    break;
                case TIMER_FLAG_OV :
                    SET_BIT ( TIMSK , TOIE0 );
                    break;
                case TIMER_FLAG_IC :
                default:
                    opResult = TIMER_ERR_FLAG_TYPE;
            }
            break;
        case TIMER_1A :
            switch ( flagType )
            {
                case TIMER_FLAG_OCR :
                    SET_BIT ( TIMSK , OCIE1A );
                    break;
                case TIMER_FLAG_OV :
                case TIMER_FLAG_IC :
                default:
                    opResult = TIMER_ERR_FLAG_TYPE;
            }
            break;
        case TIMER_1B :
            switch ( flagType )
            {
                case TIMER_FLAG_OCR :
                    SET_BIT ( TIMSK , OCIE1B );
                    break;
                case TIMER_FLAG_OV :
                case TIMER_FLAG_IC :
                default:
                    opResult = TIMER_ERR_FLAG_TYPE;
            }
            break;
        case TIMER_1 :
            switch ( flagType )
            {
                case TIMER_FLAG_OCR :
                    SET_BIT ( TIMSK , OCIE1A );
                    break;
                case TIMER_FLAG_OV :
                    SET_BIT ( TIMSK , TOIE1 );
                    break;
                case TIMER_FLAG_IC :
                    SET_BIT ( TIMSK , TICIE1 );
                    break;
                default:
                    opResult = TIMER_ERR_FLAG_TYPE;
            }
            break;
        case TIMER_2 :
            switch ( flagType )
            {
                case TIMER_FLAG_OCR :
                    SET_BIT ( TIMSK , OCIE2 );
                    break;
                case TIMER_FLAG_OV :
                    SET_BIT ( TIMSK , TOIE2 );
                    break;
                case TIMER_FLAG_IC :
                default:
                    opResult = TIMER_ERR_FLAG_TYPE;
            }
            break;
        default:
            opResult = TIMER_ERR_TIMER_NUM;
    }
    return opResult;
}
TIMER_STD_ERR_t TIMER_clearInterruptState ( TIMER_t timer , TIMER_FLAG_t flagType )
{
    TIMER_STD_ERR_t opResult = TIMER_OK;
    switch ( timer )
    {
        case TIMER_0 :
            switch ( flagType )
            {
                case TIMER_FLAG_OCR :
                    CLEAR_BIT ( TIMSK , OCIE0 );
                    break;
                case TIMER_FLAG_OV :
                    CLEAR_BIT ( TIMSK , TOIE0 );
                    break;
                case TIMER_FLAG_IC :
                default:
                    opResult = TIMER_ERR_FLAG_TYPE;
            }
            break;
        case TIMER_1A :
            switch ( flagType )
            {
                case TIMER_FLAG_OCR :
                    CLEAR_BIT ( TIMSK , OCIE1A );
                    break;
                case TIMER_FLAG_OV :
                case TIMER_FLAG_IC :
                default:
                    opResult = TIMER_ERR_FLAG_TYPE;
            }
            break;
        case TIMER_1B :
            switch ( flagType )
            {
                case TIMER_FLAG_OCR :
                    CLEAR_BIT ( TIMSK , OCIE1B );
                    break;
                case TIMER_FLAG_OV :
                case TIMER_FLAG_IC :
                default:
                    opResult = TIMER_ERR_FLAG_TYPE;
            }
            break;
        case TIMER_1 :
            switch ( flagType )
            {
                case TIMER_FLAG_OCR :
                    CLEAR_BIT ( TIMSK , OCIE1A );
                    break;
                case TIMER_FLAG_OV :
                    CLEAR_BIT ( TIMSK , TOIE1 );
                    break;
                case TIMER_FLAG_IC :
                    CLEAR_BIT ( TIMSK , TICIE1 );
                    break;
                default:
                    opResult = TIMER_ERR_FLAG_TYPE;
            }
            break;
        case TIMER_2 :
            switch ( flagType )
            {
                case TIMER_FLAG_OCR :
                    CLEAR_BIT ( TIMSK , OCIE2 );
                    break;
                case TIMER_FLAG_OV :
                    CLEAR_BIT ( TIMSK , TOIE2 );
                    break;
                case TIMER_FLAG_IC :
                default:
                    opResult = TIMER_ERR_FLAG_TYPE;
            }
            break;
        default:
            opResult = TIMER_ERR_TIMER_NUM;
    }
    return opResult;
}
TIMER_STD_ERR_t TIMER_getInterruptState ( TIMER_t timer , TIMER_FLAG_t flagType , INT_STATE_t* outputState )
{
    TIMER_STD_ERR_t opResult = TIMER_OK;
    switch ( timer )
    {
        case TIMER_0 :
            switch ( flagType )
            {
                case TIMER_FLAG_OCR :
                    *outputState = ( INT_STATE_t ) READ_BIT ( TIMSK , OCIE0 );
                    break;
                case TIMER_FLAG_OV :
                    *outputState = ( INT_STATE_t ) READ_BIT ( TIMSK , TOIE0 );
                    break;
                case TIMER_FLAG_IC :
                default:
                    opResult = TIMER_ERR_FLAG_TYPE;
            }
            break;
        case TIMER_1A :
            switch ( flagType )
            {
                case TIMER_FLAG_OCR :
                    *outputState = ( INT_STATE_t ) READ_BIT ( TIMSK , OCIE1A );
                    break;
                case TIMER_FLAG_OV :
                case TIMER_FLAG_IC :
                default:
                    opResult = TIMER_ERR_FLAG_TYPE;
            }
            break;
        case TIMER_1B :
            switch ( flagType )
            {
                case TIMER_FLAG_OCR :
                    *outputState = ( INT_STATE_t ) READ_BIT ( TIMSK , OCIE1B );
                    break;
                case TIMER_FLAG_OV :
                case TIMER_FLAG_IC :
                default:
                    opResult = TIMER_ERR_FLAG_TYPE;
            }
            break;
        case TIMER_1 :
            switch ( flagType )
            {
                case TIMER_FLAG_OCR :
                    *outputState = ( INT_STATE_t ) READ_BIT ( TIMSK , OCIE1A );
                    break;
                case TIMER_FLAG_OV :
                    *outputState = ( INT_STATE_t ) READ_BIT ( TIMSK , TOIE1 );
                    break;
                case TIMER_FLAG_IC :
                    *outputState = ( INT_STATE_t ) READ_BIT ( TIMSK , TICIE1 );
                    break;
                default:
                    opResult = TIMER_ERR_FLAG_TYPE;
            }
            break;
        case TIMER_2 :
            switch ( flagType )
            {
                case TIMER_FLAG_OCR :
                    *outputState = ( INT_STATE_t ) READ_BIT ( TIMSK , OCIE2 );
                    break;
                case TIMER_FLAG_OV :
                    *outputState = ( INT_STATE_t ) READ_BIT ( TIMSK , TOIE2 );
                    break;
                case TIMER_FLAG_IC :
                default:
                    opResult = TIMER_ERR_FLAG_TYPE;
            }
            break;
        default:
            opResult = TIMER_ERR_TIMER_NUM;
    }
    return opResult;
}
TIMER_STD_ERR_t TIMER_clearInterruptFlag ( TIMER_t timer , TIMER_FLAG_t flagType )
{
    TIMER_STD_ERR_t opResult = TIMER_OK;
    switch ( timer )
    {
        case TIMER_0 :
            switch ( flagType )
            {
                case TIMER_FLAG_OCR :
                    SET_BIT ( TIFR , OCF0 );
                    break;
                case TIMER_FLAG_OV :
                    SET_BIT ( TIFR , TOV0 );
                    break;
                case TIMER_FLAG_IC :
                default:
                    opResult = TIMER_ERR_FLAG_TYPE;
            }
            break;
        case TIMER_1A :
            switch ( flagType )
            {
                case TIMER_FLAG_OCR :
                    SET_BIT ( TIFR , OCF1A );
                    break;
                case TIMER_FLAG_OV :
                case TIMER_FLAG_IC :
                default:
                    opResult = TIMER_ERR_FLAG_TYPE;
            }
            break;
        case TIMER_1B :
            switch ( flagType )
            {
                case TIMER_FLAG_OCR :
                    SET_BIT ( TIFR , OCF1B );
                    break;
                case TIMER_FLAG_OV :
                case TIMER_FLAG_IC :
                default:
                    opResult = TIMER_ERR_FLAG_TYPE;
            }
            break;
        case TIMER_1 :
            switch ( flagType )
            {
                case TIMER_FLAG_OCR :
                    SET_BIT ( TIFR , OCF1A );
                    break;
                case TIMER_FLAG_OV :
                    SET_BIT ( TIFR , TOV1 );
                    break;
                case TIMER_FLAG_IC :
                    SET_BIT ( TIFR , ICF1 );
                    break;
                default:
                    opResult = TIMER_ERR_FLAG_TYPE;
            }
            break;
        case TIMER_2 :
            switch ( flagType )
            {
                case TIMER_FLAG_OCR :
                    SET_BIT ( TIFR , OCF2 );
                    break;
                case TIMER_FLAG_OV :
                    SET_BIT ( TIFR , TOV2 );
                    break;
                case TIMER_FLAG_IC :
                default:
                    opResult = TIMER_ERR_FLAG_TYPE;
            }
            break;
        default:
            opResult = TIMER_ERR_TIMER_NUM;
    }
    return opResult;
}
TIMER_STD_ERR_t TIMER_getInterruptFlag ( TIMER_t timer , TIMER_FLAG_t flagType , FLAG_STATE_t* outputFlagState )
{
    TIMER_STD_ERR_t opResult = TIMER_OK;
    switch ( timer )
    {
        case TIMER_0 :
            switch ( flagType )
            {
                case TIMER_FLAG_OCR :
                    *outputFlagState = ( FLAG_STATE_t ) READ_BIT ( TIFR , OCF0 );
                    break;
                case TIMER_FLAG_OV :
                    *outputFlagState = ( FLAG_STATE_t ) READ_BIT ( TIFR , TOV0 );
                    break;
                case TIMER_FLAG_IC :
                default:
                    opResult = TIMER_ERR_FLAG_TYPE;
            }
            break;
        case TIMER_1A :
            switch ( flagType )
            {
                case TIMER_FLAG_OCR :
                    *outputFlagState = ( FLAG_STATE_t ) READ_BIT ( TIFR , OCF1A );
                    break;
                case TIMER_FLAG_OV :
                case TIMER_FLAG_IC :
                default:
                    opResult = TIMER_ERR_FLAG_TYPE;
            }
            break;
        case TIMER_1B :
            switch ( flagType )
            {
                case TIMER_FLAG_OCR :
                    *outputFlagState = ( FLAG_STATE_t ) READ_BIT ( TIFR , OCF1B );
                    break;
                case TIMER_FLAG_OV :
                case TIMER_FLAG_IC :
                default:
                    opResult = TIMER_ERR_FLAG_TYPE;
            }
            break;
        case TIMER_1 :
            switch ( flagType )
            {
                case TIMER_FLAG_OCR :
                    *outputFlagState = ( FLAG_STATE_t ) READ_BIT ( TIFR , OCF1A );
                    break;
                case TIMER_FLAG_OV :
                    *outputFlagState = ( FLAG_STATE_t ) READ_BIT ( TIFR , TOV1 );
                    break;
                case TIMER_FLAG_IC :
                    *outputFlagState = ( FLAG_STATE_t ) READ_BIT ( TIFR , ICF1 );
                    break;
                default:
                    opResult = TIMER_ERR_FLAG_TYPE;
            }
            break;
        case TIMER_2 :
            switch ( flagType )
            {
                case TIMER_FLAG_OCR :
                    *outputFlagState = ( FLAG_STATE_t ) READ_BIT ( TIFR , OCF2 );
                    break;
                case TIMER_FLAG_OV :
                    *outputFlagState = ( FLAG_STATE_t ) READ_BIT ( TIFR , TOV2 );
                    break;
                case TIMER_FLAG_IC :
                default:
                    opResult = TIMER_ERR_FLAG_TYPE;
            }
            break;
        default:
            opResult = TIMER_ERR_TIMER_NUM;
    }
    return opResult;
}
TIMER_STD_ERR_t TIMER_forceOcrMatch ( TIMER_t timer )
{
    TIMER_STD_ERR_t opResult = TIMER_OK;
    switch ( timer )
    {
        case TIMER_0 :
            SET_BIT ( TCCR0 , FOC0 );
            break;
            break;
        case TIMER_1B :
            SET_BIT ( TCCR1A , FOC1B );
            break;
        case TIMER_1A :
        case TIMER_1 :
            SET_BIT ( TCCR1A , FOC1A );
            break;
        case TIMER_2 :
            SET_BIT ( TCCR2 , FOC0 );
            break;
        default:
            opResult = TIMER_ERR_TIMER_NUM;
    }
    return opResult;
}
TIMER_STD_ERR_t TIMER_setOcr ( TIMER_t timer , uint16_t ocrValue )
{
    TIMER_STD_ERR_t opResult = TIMER_OK;
    switch ( timer )
    {
        case TIMER_0 :
            if ( ocrValue <= MAX_SMALL_OCR_VALUE )
            {
                OCR0 = ( uint8_t ) ocrValue;
            }
            else
            {
                opResult = TIMER_ERR_OCR;
            }
            break;
        case TIMER_1 :
        case TIMER_1A :
            //OCR1A = ocrValue;
#if USE_PROTECTED_SECTIONS == 1
            uint8_t intBit = ( uint8_t ) READ_BIT ( SREG , SREG_I );
            cli ();
#endif
            OCR1AH = ( uint8_t ) ( ocrValue >> 8 );
            OCR1AL = ( uint8_t ) ( ocrValue & 0xFF );
#if USE_PROTECTED_SECTIONS == 1
            REPLACE_BIT ( SREG , SREG_I , intBit );
#endif
            break;
        case TIMER_1B :
            OCR1B = ocrValue;
#if USE_PROTECTED_SECTIONS == 1
        uint8_t intBit = ( uint8_t ) READ_BIT ( SREG , SREG_I );
        cli ();
#endif
            OCR1BH = ( uint8_t ) ( ocrValue >> 8 );
            OCR1BL = ( uint8_t ) ( ocrValue & 0xFF );
#if USE_PROTECTED_SECTIONS == 1
            REPLACE_BIT ( SREG , SREG_I , intBit );
#endif
            break;
        case TIMER_2 :
            if ( ocrValue <= ( uint8_t ) MAX_SMALL_OCR_VALUE )
            {
                OCR2 = ( uint8_t ) ocrValue;
            }
            else
            {
                opResult = TIMER_ERR_OCR;
            }
            break;
        default:
            opResult = TIMER_ERR_TIMER_NUM;
    }
    return opResult;
}
TIMER_STD_ERR_t TIMER_setIcr ( TIMER_t timer , uint16_t icrValue )
{
    TIMER_STD_ERR_t opResult = TIMER_OK;
    switch ( timer )
    {
        case TIMER_0 :
            opResult = TIMER_ERR_ICR;
            break;
        case TIMER_1 :
        case TIMER_1A :
        case TIMER_1B :
            //ICR1 = ocrValue;
#if USE_PROTECTED_SECTIONS == 1
            uint8_t intBit = ( uint8_t ) READ_BIT ( SREG , SREG_I );
            cli ();
#endif
            ICR1H = ( uint8_t ) ( icrValue >> 8 );
            ICR1L = ( uint8_t ) ( icrValue & 0xFF );
#if USE_PROTECTED_SECTIONS == 1
            REPLACE_BIT ( SREG , SREG_I , intBit );
#endif
            break;
        case TIMER_2 :
            opResult = TIMER_ERR_ICR;
            break;
        default:
            opResult = TIMER_ERR_TIMER_NUM;
    }
    return opResult;
}
TIMER_STD_ERR_t TIMER_setPrescaller ( TIMER_t timer , TIMER_CLCK_t clockSetting )
{
    TIMER_STD_ERR_t opResult = TIMER_OK;
    switch ( timer )
    {
        case TIMER_0 :
            switch ( clockSetting )
            {
                case TIMER_CLCK_NO :
                case TIMER_CLCK_PRESC_1 :
                case TIMER_CLCK_PRESC_8 :
                case TIMER_CLCK_PRESC_64 :
                case TIMER_CLCK_PRESC_256 :
                case TIMER_CLCK_PRESC_1024 :
                case TIMER_CLCK_EXTERNAL_FALLING :
                case TIMER_CLCK_EXTERNAL_RISING :
                    REPLACE_BITS ( TCCR0 , ( ( uint8_t ) clockSetting ) << CS00 , BIT_MASK ( CS02 ) | BIT_MASK ( CS01 ) | BIT_MASK ( CS00 ) );
                    break;
                default:
                    opResult = TIMER_ERR_PRESCALER;
            }
            break;
        case TIMER_1A :
        case TIMER_1B :
        case TIMER_1 :
            switch ( clockSetting )
            {
                case TIMER_CLCK_NO :
                case TIMER_CLCK_PRESC_1 :
                case TIMER_CLCK_PRESC_8 :
                case TIMER_CLCK_PRESC_64 :
                case TIMER_CLCK_PRESC_256 :
                case TIMER_CLCK_PRESC_1024 :
                case TIMER_CLCK_EXTERNAL_FALLING :
                case TIMER_CLCK_EXTERNAL_RISING :
                    REPLACE_BITS ( TCCR1B , ( ( uint8_t ) clockSetting ) << CS10 , BIT_MASK ( CS12 ) | BIT_MASK ( CS11 ) | BIT_MASK ( CS10 ) );
                    break;
                default:
                    opResult = TIMER_ERR_PRESCALER;
            }
            break;
        case TIMER_2 :
            switch ( clockSetting )
            {
                case TIMER_CLCK_NO :
                case TIMER_CLCK_PRESC_1 :
                case TIMER_CLCK_PRESC_8 :
                case TIMER_CLCK_PRESC_64 :
                case TIMER_CLCK_PRESC_256 :
                case TIMER_CLCK_PRESC_1024 :
                case TIMER_CLCK_EXTERNAL_FALLING :
                case TIMER_CLCK_EXTERNAL_RISING :
                    REPLACE_BITS ( TCCR2 , ( ( uint8_t ) clockSetting ) << CS20 , BIT_MASK ( CS22 ) | BIT_MASK ( CS21 ) | BIT_MASK ( CS20 ) );
                    break;
                default:
                    opResult = TIMER_ERR_PRESCALER;
            }
            break;
        default:
            opResult = TIMER_ERR_TIMER_NUM;
    }
    return opResult;
}
TIMER_STD_ERR_t TIMER_getPrescaller ( TIMER_t timer , TIMER_CLCK_t* outputClockSetting )
{
    TIMER_STD_ERR_t opResult = TIMER_OK;
    switch ( timer )
    {
        case TIMER_0 :
            *outputClockSetting = ( TIMER_CLCK_t ) READ_BITS_AND_SHIFT ( TCCR0 , BIT_MASK ( CS02 ) | BIT_MASK ( CS01 ) | BIT_MASK ( CS00 ) , CS00 );
            break;
        case TIMER_1A :
        case TIMER_1B :
        case TIMER_1 :
            *outputClockSetting = ( TIMER_CLCK_t ) READ_BITS_AND_SHIFT ( TCCR0 , BIT_MASK ( CS12 ) | BIT_MASK ( CS11 ) | BIT_MASK ( CS10 ) , CS10 );
            break;
        case TIMER_2 :
            *outputClockSetting = ( TIMER_CLCK_t ) READ_BITS_AND_SHIFT ( TCCR0 , BIT_MASK ( CS22 ) | BIT_MASK ( CS21 ) | BIT_MASK ( CS20 ) , CS20 );
            break;
        default:
            opResult = TIMER_ERR_TIMER_NUM;
    }
    return opResult;
}
TIMER_STD_ERR_t TIMER_setMode ( TIMER_t timer , TIMER_MODE_t modeToSet )
{
    TIMER_STD_ERR_t opResult = TIMER_OK;
    switch ( timer )
    {
        case TIMER_0 :
            switch ( modeToSet )
            {
                case TIMER_MODE_NORMAL :
                    REPLACE_BITS ( TCCR0 , ( 0x00 << WGM01 ) | ( 0x00 << WGM00 ) , BIT_MASK ( WGM01 ) | BIT_MASK ( WGM00 ) );
                    break;
                case TIMER_MODE_CTC_OCR_TOP :
                    REPLACE_BITS ( TCCR0 , ( 0x01 << WGM01 ) | ( 0x00 << WGM00 ) , BIT_MASK ( WGM01 ) | BIT_MASK ( WGM00 ) );
                    break;
                case TIMER_MODE_FAST_PWM_MAX_TOP :
                    REPLACE_BITS ( TCCR0 , ( 0x01 << WGM01 ) | ( 0x01 << WGM00 ) , BIT_MASK ( WGM01 ) | BIT_MASK ( WGM00 ) );
                    break;
                case TIMER_MODE_PHASE_PWM_MAX_TOP :
                    REPLACE_BITS ( TCCR0 , ( 0x00 << WGM01 ) | ( 0x01 << WGM00 ) , BIT_MASK ( WGM01 ) | BIT_MASK ( WGM00 ) );
                    break;
                case TIMER_MODE_CTC_ICR_TOP :
                case TIMER_MODE_FAST_PWM_0xFF_TOP :
                case TIMER_MODE_FAST_PWM_0x1FF_TOP :
                case TIMER_MODE_FAST_PWM_0x3FF_TOP :
                case TIMER_MODE_FAST_PWM_OCR_TOP :
                case TIMER_MODE_FAST_PWM_ICR_TOP :
                case TIMER_MODE_PHASE_PWM_0xFF_TOP :
                case TIMER_MODE_PHASE_PWM_0x1FF_TOP :
                case TIMER_MODE_PHASE_PWM_0x3FF_TOP :
                case TIMER_MODE_PHASE_PWM_OCR_TOP :
                case TIMER_MODE_PHASE_PWM_ICR_TOP :
                case TIMER_MODE_PHASE_FREQ_PWM_OCR_TOP :
                case TIMER_MODE_PHASE_FREQ_PWM_ICR_TOP :
                default:
                    opResult = TIMER_ERR_MODE;
            }
            break;
        case TIMER_1A :
        case TIMER_1B :
        case TIMER_1 :
            switch ( modeToSet )
            {
                case TIMER_MODE_NORMAL :
                    REPLACE_BITS ( TCCR1A , ( 0x00 << WGM11 ) | ( 0x00 << WGM10 ) , BIT_MASK ( WGM11 ) | BIT_MASK ( WGM10 ) );
                    REPLACE_BITS ( TCCR1B , ( 0x00 << WGM13 ) | ( 0x00 << WGM12 ) , BIT_MASK ( WGM13 ) | BIT_MASK ( WGM12 ) );
                    break;
                case TIMER_MODE_CTC_OCR_TOP :
                    REPLACE_BITS ( TCCR1A , ( 0x00 << WGM11 ) | ( 0x00 << WGM10 ) , BIT_MASK ( WGM11 ) | BIT_MASK ( WGM10 ) );
                    REPLACE_BITS ( TCCR1B , ( 0x00 << WGM13 ) | ( 0x01 << WGM12 ) , BIT_MASK ( WGM13 ) | BIT_MASK ( WGM12 ) );
                    break;
                case TIMER_MODE_CTC_ICR_TOP :
                    REPLACE_BITS ( TCCR1A , ( 0x00 << WGM11 ) | ( 0x00 << WGM10 ) , BIT_MASK ( WGM11 ) | BIT_MASK ( WGM10 ) );
                    REPLACE_BITS ( TCCR1B , ( 0x01 << WGM13 ) | ( 0x00 << WGM12 ) , BIT_MASK ( WGM13 ) | BIT_MASK ( WGM12 ) );
                    break;
                case TIMER_MODE_FAST_PWM_0xFF_TOP :
                    REPLACE_BITS ( TCCR1A , ( 0x00 << WGM11 ) | ( 0x01 << WGM10 ) , BIT_MASK ( WGM11 ) | BIT_MASK ( WGM10 ) );
                    REPLACE_BITS ( TCCR1B , ( 0x00 << WGM13 ) | ( 0x01 << WGM12 ) , BIT_MASK ( WGM13 ) | BIT_MASK ( WGM12 ) );
                    break;
                case TIMER_MODE_FAST_PWM_0x1FF_TOP :
                    REPLACE_BITS ( TCCR1A , ( 0x01 << WGM11 ) | ( 0x00 << WGM10 ) , BIT_MASK ( WGM11 ) | BIT_MASK ( WGM10 ) );
                    REPLACE_BITS ( TCCR1B , ( 0x00 << WGM13 ) | ( 0x01 << WGM12 ) , BIT_MASK ( WGM13 ) | BIT_MASK ( WGM12 ) );
                    break;
                case TIMER_MODE_FAST_PWM_0x3FF_TOP :
                    REPLACE_BITS ( TCCR1A , ( 0x01 << WGM11 ) | ( 0x01 << WGM10 ) , BIT_MASK ( WGM11 ) | BIT_MASK ( WGM10 ) );
                    REPLACE_BITS ( TCCR1B , ( 0x00 << WGM13 ) | ( 0x01 << WGM12 ) , BIT_MASK ( WGM13 ) | BIT_MASK ( WGM12 ) );
                    break;
                case TIMER_MODE_FAST_PWM_OCR_TOP :
                    REPLACE_BITS ( TCCR1A , ( 0x01 << WGM11 ) | ( 0x01 << WGM10 ) , BIT_MASK ( WGM11 ) | BIT_MASK ( WGM10 ) );
                    REPLACE_BITS ( TCCR1B , ( 0x01 << WGM13 ) | ( 0x01 << WGM12 ) , BIT_MASK ( WGM13 ) | BIT_MASK ( WGM12 ) );
                    break;
                case TIMER_MODE_FAST_PWM_ICR_TOP :
                    REPLACE_BITS ( TCCR1A , ( 0x01 << WGM11 ) | ( 0x00 << WGM10 ) , BIT_MASK ( WGM11 ) | BIT_MASK ( WGM10 ) );
                    REPLACE_BITS ( TCCR1B , ( 0x01 << WGM13 ) | ( 0x01 << WGM12 ) , BIT_MASK ( WGM13 ) | BIT_MASK ( WGM12 ) );
                    break;
                case TIMER_MODE_PHASE_PWM_0xFF_TOP :
                    REPLACE_BITS ( TCCR1A , ( 0x00 << WGM11 ) | ( 0x01 << WGM10 ) , BIT_MASK ( WGM11 ) | BIT_MASK ( WGM10 ) );
                    REPLACE_BITS ( TCCR1B , ( 0x00 << WGM13 ) | ( 0x00 << WGM12 ) , BIT_MASK ( WGM13 ) | BIT_MASK ( WGM12 ) );
                    break;
                case TIMER_MODE_PHASE_PWM_0x1FF_TOP :
                    REPLACE_BITS ( TCCR1A , ( 0x01 << WGM11 ) | ( 0x00 << WGM10 ) , BIT_MASK ( WGM11 ) | BIT_MASK ( WGM10 ) );
                    REPLACE_BITS ( TCCR1B , ( 0x00 << WGM13 ) | ( 0x00 << WGM12 ) , BIT_MASK ( WGM13 ) | BIT_MASK ( WGM12 ) );
                    break;
                case TIMER_MODE_PHASE_PWM_0x3FF_TOP :
                    REPLACE_BITS ( TCCR1A , ( 0x01 << WGM11 ) | ( 0x01 << WGM10 ) , BIT_MASK ( WGM11 ) | BIT_MASK ( WGM10 ) );
                    REPLACE_BITS ( TCCR1B , ( 0x00 << WGM13 ) | ( 0x00 << WGM12 ) , BIT_MASK ( WGM13 ) | BIT_MASK ( WGM12 ) );
                    break;
                case TIMER_MODE_PHASE_PWM_OCR_TOP :
                    REPLACE_BITS ( TCCR1A , ( 0x01 << WGM11 ) | ( 0x01 << WGM10 ) , BIT_MASK ( WGM11 ) | BIT_MASK ( WGM10 ) );
                    REPLACE_BITS ( TCCR1B , ( 0x01 << WGM13 ) | ( 0x00 << WGM12 ) , BIT_MASK ( WGM13 ) | BIT_MASK ( WGM12 ) );
                    break;
                case TIMER_MODE_PHASE_PWM_ICR_TOP :
                    REPLACE_BITS ( TCCR1A , ( 0x01 << WGM11 ) | ( 0x00 << WGM10 ) , BIT_MASK ( WGM11 ) | BIT_MASK ( WGM10 ) );
                    REPLACE_BITS ( TCCR1B , ( 0x01 << WGM13 ) | ( 0x00 << WGM12 ) , BIT_MASK ( WGM13 ) | BIT_MASK ( WGM12 ) );
                    break;
                case TIMER_MODE_PHASE_FREQ_PWM_OCR_TOP :
                    REPLACE_BITS ( TCCR1A , ( 0x00 << WGM11 ) | ( 0x01 << WGM10 ) , BIT_MASK ( WGM11 ) | BIT_MASK ( WGM10 ) );
                    REPLACE_BITS ( TCCR1B , ( 0x01 << WGM13 ) | ( 0x00 << WGM12 ) , BIT_MASK ( WGM13 ) | BIT_MASK ( WGM12 ) );
                    break;
                case TIMER_MODE_PHASE_FREQ_PWM_ICR_TOP :
                    REPLACE_BITS ( TCCR1A , ( 0x00 << WGM11 ) | ( 0x00 << WGM10 ) , BIT_MASK ( WGM11 ) | BIT_MASK ( WGM10 ) );
                    REPLACE_BITS ( TCCR1B , ( 0x01 << WGM13 ) | ( 0x00 << WGM12 ) , BIT_MASK ( WGM13 ) | BIT_MASK ( WGM12 ) );
                    break;
                case TIMER_MODE_PHASE_PWM_MAX_TOP :
                case TIMER_MODE_FAST_PWM_MAX_TOP :
                default:
                    opResult = TIMER_ERR_MODE;
            }
            break;
        case TIMER_2 :
            switch ( modeToSet )
            {
                case TIMER_MODE_NORMAL :
                    REPLACE_BITS ( TCCR2 , ( 0x00 << WGM21 ) | ( 0x00 << WGM20 ) , BIT_MASK ( WGM21 ) | BIT_MASK ( WGM20 ) );
                    break;
                case TIMER_MODE_CTC_OCR_TOP :
                    REPLACE_BITS ( TCCR2 , ( 0x01 << WGM21 ) | ( 0x00 << WGM20 ) , BIT_MASK ( WGM21 ) | BIT_MASK ( WGM20 ) );
                    break;
                case TIMER_MODE_FAST_PWM_MAX_TOP :
                    REPLACE_BITS ( TCCR2 , ( 0x01 << WGM21 ) | ( 0x01 << WGM20 ) , BIT_MASK ( WGM21 ) | BIT_MASK ( WGM20 ) );
                    break;
                case TIMER_MODE_PHASE_PWM_MAX_TOP :
                    REPLACE_BITS ( TCCR2 , ( 0x00 << WGM21 ) | ( 0x01 << WGM20 ) , BIT_MASK ( WGM21 ) | BIT_MASK ( WGM20 ) );
                    break;
                case TIMER_MODE_CTC_ICR_TOP :
                case TIMER_MODE_FAST_PWM_0xFF_TOP :
                case TIMER_MODE_FAST_PWM_0x1FF_TOP :
                case TIMER_MODE_FAST_PWM_0x3FF_TOP :
                case TIMER_MODE_FAST_PWM_OCR_TOP :
                case TIMER_MODE_FAST_PWM_ICR_TOP :
                case TIMER_MODE_PHASE_PWM_0xFF_TOP :
                case TIMER_MODE_PHASE_PWM_0x1FF_TOP :
                case TIMER_MODE_PHASE_PWM_0x3FF_TOP :
                case TIMER_MODE_PHASE_PWM_OCR_TOP :
                case TIMER_MODE_PHASE_PWM_ICR_TOP :
                case TIMER_MODE_PHASE_FREQ_PWM_OCR_TOP :
                case TIMER_MODE_PHASE_FREQ_PWM_ICR_TOP :
                default:
                    opResult = TIMER_ERR_MODE;
            }
            break;
        default:
            opResult = TIMER_ERR_TIMER_NUM;
    }
    return opResult;
}
TIMER_STD_ERR_t TIMER_setCtcSetting ( TIMER_t timer , TIMER_CTC_SETTING_t settingToSet )
{
    TIMER_STD_ERR_t opResult = TIMER_OK;
    switch ( timer )
    {
        case TIMER_0 :
            switch ( settingToSet )
            {
                case CTC_NORMAL :
                    REPLACE_BITS ( TCCR0 , ( 0x00 << COM01 ) | ( 0x00 << COM00 ) , BIT_MASK ( COM01 ) | BIT_MASK ( COM00 ) );
                    break;
                case CTC_TOGGLE :
                    REPLACE_BITS ( TCCR0 , ( 0x00 << COM01 ) | ( 0x01 << COM00 ) , BIT_MASK ( COM01 ) | BIT_MASK ( COM00 ) );
                    break;
                case CTC_CLEAR :
                    REPLACE_BITS ( TCCR0 , ( 0x01 << COM01 ) | ( 0x00 << COM00 ) , BIT_MASK ( COM01 ) | BIT_MASK ( COM00 ) );
                    break;
                case CTC_SET :
                    REPLACE_BITS ( TCCR0 , ( 0x01 << COM01 ) | ( 0x01 << COM00 ) , BIT_MASK ( COM01 ) | BIT_MASK ( COM00 ) );
                    break;
                default:
                    opResult = TIMER_ERR_CTC;
            }
            break;
        case TIMER_1 :
        case TIMER_1A :
            switch ( settingToSet )
            {
                case CTC_NORMAL :
                    REPLACE_BITS ( TCCR1A , ( 0x00 << COM1A1 ) | ( 0x00 << COM1A0 ) , BIT_MASK ( COM1A1 ) | BIT_MASK ( COM1A0 ) );
                    break;
                case CTC_TOGGLE :
                    REPLACE_BITS ( TCCR1A , ( 0x00 << COM1A1 ) | ( 0x01 << COM1A0 ) , BIT_MASK ( COM1A1 ) | BIT_MASK ( COM1A0 ) );
                    break;
                case CTC_CLEAR :
                    REPLACE_BITS ( TCCR1A , ( 0x01 << COM1A1 ) | ( 0x00 << COM1A0 ) , BIT_MASK ( COM1A1 ) | BIT_MASK ( COM1A0 ) );
                    break;
                case CTC_SET :
                    REPLACE_BITS ( TCCR1A , ( 0x01 << COM1A1 ) | ( 0x01 << COM1A0 ) , BIT_MASK ( COM1A1 ) | BIT_MASK ( COM1A0 ) );
                    break;
                default:
                    opResult = TIMER_ERR_CTC;
            }
            break;
        case TIMER_1B :
            switch ( settingToSet )
            {
                case CTC_NORMAL :
                    REPLACE_BITS ( TCCR1B , ( 0x00 << COM1B1 ) | ( 0x00 << COM1B0 ) , BIT_MASK ( COM1B1 ) | BIT_MASK ( COM1B0 ) );
                    break;
                case CTC_TOGGLE :
                    REPLACE_BITS ( TCCR1B , ( 0x00 << COM1B1 ) | ( 0x01 << COM1B0 ) , BIT_MASK ( COM1B1 ) | BIT_MASK ( COM1B0 ) );
                    break;
                case CTC_CLEAR :
                    REPLACE_BITS ( TCCR1B , ( 0x01 << COM1B1 ) | ( 0x00 << COM1B0 ) , BIT_MASK ( COM1B1 ) | BIT_MASK ( COM1B0 ) );
                    break;
                case CTC_SET :
                    REPLACE_BITS ( TCCR1B , ( 0x01 << COM1B1 ) | ( 0x01 << COM1B0 ) , BIT_MASK ( COM1B1 ) | BIT_MASK ( COM1B0 ) );
                    break;
                default:
                    opResult = TIMER_ERR_CTC;
            }
            break;
        case TIMER_2 :
            switch ( settingToSet )
            {
                case CTC_NORMAL :
                    REPLACE_BITS ( TCCR2 , ( 0x00 << COM21 ) | ( 0x00 << COM20 ) , BIT_MASK ( COM21 ) | BIT_MASK ( COM20 ) );
                    break;
                case CTC_TOGGLE :
                    REPLACE_BITS ( TCCR2 , ( 0x00 << COM21 ) | ( 0x01 << COM20 ) , BIT_MASK ( COM21 ) | BIT_MASK ( COM20 ) );
                    break;
                case CTC_CLEAR :
                    REPLACE_BITS ( TCCR2 , ( 0x01 << COM21 ) | ( 0x00 << COM20 ) , BIT_MASK ( COM21 ) | BIT_MASK ( COM20 ) );
                    break;
                case CTC_SET :
                    REPLACE_BITS ( TCCR2 , ( 0x01 << COM21 ) | ( 0x01 << COM20 ) , BIT_MASK ( COM21 ) | BIT_MASK ( COM20 ) );
                    break;
                default:
                    opResult = TIMER_ERR_CTC;
            }
            break;
        default:
            opResult = TIMER_ERR_TIMER_NUM;
    }
    return opResult;
}
TIMER_STD_ERR_t TIMER_setFastPwmSetting ( TIMER_t timer , TIMER_FAST_PWM_SETTING_t settingToSet )
{
    TIMER_STD_ERR_t opResult = TIMER_OK;
    switch ( timer )
    {
        case TIMER_0 :
            switch ( settingToSet )
            {
                case FAST_PWM_NORMAL :
                    REPLACE_BITS ( TCCR0 , ( 0x00 << COM01 ) | ( 0x00 << COM00 ) , BIT_MASK ( COM01 ) | BIT_MASK ( COM00 ) );
                    break;
                case FAST_PWM_CLEAR_MATCH_SET_BOTTOM :
                    REPLACE_BITS ( TCCR0 , ( 0x01 << COM01 ) | ( 0x00 << COM00 ) , BIT_MASK ( COM01 ) | BIT_MASK ( COM00 ) );
                    break;
                case FAST_PWM_SET_MATCH_CLEAR_BOTTOM :
                    REPLACE_BITS ( TCCR0 , ( 0x01 << COM01 ) | ( 0x01 << COM00 ) , BIT_MASK ( COM01 ) | BIT_MASK ( COM00 ) );
                    break;
                case FAST_PWM_TOGGLE :
                default:
                    opResult = TIMER_ERR_FAST_PWM_SETTING;
            }
            break;
        case TIMER_1 :
        case TIMER_1A :
            switch ( settingToSet )
            {
                case FAST_PWM_NORMAL :
                    REPLACE_BITS ( TCCR1A , ( 0x00 << COM1A1 ) | ( 0x00 << COM1A0 ) , BIT_MASK ( COM1A1 ) | BIT_MASK ( COM1A0 ) );
                    break;
                case FAST_PWM_TOGGLE :
                    REPLACE_BITS ( TCCR1A , ( 0x00 << COM1A1 ) | ( 0x01 << COM1A0 ) , BIT_MASK ( COM1A1 ) | BIT_MASK ( COM1A0 ) );
                    break;
                case FAST_PWM_CLEAR_MATCH_SET_BOTTOM :
                    REPLACE_BITS ( TCCR1A , ( 0x01 << COM1A1 ) | ( 0x00 << COM1A0 ) , BIT_MASK ( COM1A1 ) | BIT_MASK ( COM1A0 ) );
                    break;
                case FAST_PWM_SET_MATCH_CLEAR_BOTTOM :
                    REPLACE_BITS ( TCCR1A , ( 0x01 << COM1A1 ) | ( 0x01 << COM1A0 ) , BIT_MASK ( COM1A1 ) | BIT_MASK ( COM1A0 ) );
                    break;
                default:
                    opResult = TIMER_ERR_FAST_PWM_SETTING;
            }
            break;
        case TIMER_1B :
            switch ( settingToSet )
            {
                case FAST_PWM_NORMAL :
                    REPLACE_BITS ( TCCR1B , ( 0x00 << COM1B1 ) | ( 0x00 << COM1B0 ) , BIT_MASK ( COM1B1 ) | BIT_MASK ( COM1B0 ) );
                    break;
                case FAST_PWM_TOGGLE :
                    REPLACE_BITS ( TCCR1B , ( 0x00 << COM1B1 ) | ( 0x01 << COM1B0 ) , BIT_MASK ( COM1B1 ) | BIT_MASK ( COM1B0 ) );
                    break;
                case FAST_PWM_CLEAR_MATCH_SET_BOTTOM :
                    REPLACE_BITS ( TCCR1B , ( 0x01 << COM1B1 ) | ( 0x00 << COM1B0 ) , BIT_MASK ( COM1B1 ) | BIT_MASK ( COM1B0 ) );
                    break;
                case FAST_PWM_SET_MATCH_CLEAR_BOTTOM :
                    REPLACE_BITS ( TCCR1B , ( 0x01 << COM1B1 ) | ( 0x01 << COM1B0 ) , BIT_MASK ( COM1B1 ) | BIT_MASK ( COM1B0 ) );
                    break;
                default:
                    opResult = TIMER_ERR_FAST_PWM_SETTING;
            }
            break;
        case TIMER_2 :
            switch ( settingToSet )
            {
                case FAST_PWM_NORMAL :
                    REPLACE_BITS ( TCCR2 , ( 0x00 << COM21 ) | ( 0x00 << COM20 ) , BIT_MASK ( COM21 ) | BIT_MASK ( COM20 ) );
                    break;
                case FAST_PWM_CLEAR_MATCH_SET_BOTTOM :
                    REPLACE_BITS ( TCCR2 , ( 0x01 << COM21 ) | ( 0x00 << COM20 ) , BIT_MASK ( COM21 ) | BIT_MASK ( COM20 ) );
                    break;
                case FAST_PWM_SET_MATCH_CLEAR_BOTTOM :
                    REPLACE_BITS ( TCCR2 , ( 0x01 << COM21 ) | ( 0x01 << COM20 ) , BIT_MASK ( COM21 ) | BIT_MASK ( COM20 ) );
                    break;
                case FAST_PWM_TOGGLE :
                default:
                    opResult = TIMER_ERR_FAST_PWM_SETTING;
            }
            break;
        default:
            opResult = TIMER_ERR_TIMER_NUM;
    }
    return opResult;
}
TIMER_STD_ERR_t TIMER_setCorrectPwmSetting ( TIMER_t timer , TIMER_CORRECT_PWM_SETTING_t settingToSet )
{
    TIMER_STD_ERR_t opResult = TIMER_OK;
    switch ( timer )
    {
        case TIMER_0 :
            switch ( settingToSet )
            {
                case CORRECT_PWM_NORMAL :
                    REPLACE_BITS ( TCCR0 , ( 0x00 << COM01 ) | ( 0x00 << COM00 ) , BIT_MASK ( COM01 ) | BIT_MASK ( COM00 ) );
                    break;
                case CORRECT_PWM_CLEAR_MATCH_UP_SET_MATCH_DOWN :
                    REPLACE_BITS ( TCCR0 , ( 0x01 << COM01 ) | ( 0x00 << COM00 ) , BIT_MASK ( COM01 ) | BIT_MASK ( COM00 ) );
                    break;
                case CORRECT_PWM_SET_MATCH_UP_CLEAR_MATCH_DOWN :
                    REPLACE_BITS ( TCCR0 , ( 0x01 << COM01 ) | ( 0x01 << COM00 ) , BIT_MASK ( COM01 ) | BIT_MASK ( COM00 ) );
                    break;
                case CORRECT_PWM_CORRECT :
                default:
                    opResult = TIMER_ERR_FAST_PWM_SETTING;
            }
            break;
        case TIMER_1 :
        case TIMER_1A :
            switch ( settingToSet )
            {
                case CORRECT_PWM_NORMAL :
                    REPLACE_BITS ( TCCR1A , ( 0x00 << COM1A1 ) | ( 0x00 << COM1A0 ) , BIT_MASK ( COM1A1 ) | BIT_MASK ( COM1A0 ) );
                    break;
                case CORRECT_PWM_CORRECT :
                    REPLACE_BITS ( TCCR1A , ( 0x00 << COM1A1 ) | ( 0x01 << COM1A0 ) , BIT_MASK ( COM1A1 ) | BIT_MASK ( COM1A0 ) );
                    break;
                case CORRECT_PWM_CLEAR_MATCH_UP_SET_MATCH_DOWN :
                    REPLACE_BITS ( TCCR1A , ( 0x01 << COM1A1 ) | ( 0x00 << COM1A0 ) , BIT_MASK ( COM1A1 ) | BIT_MASK ( COM1A0 ) );
                    break;
                case CORRECT_PWM_SET_MATCH_UP_CLEAR_MATCH_DOWN :
                    REPLACE_BITS ( TCCR1A , ( 0x01 << COM1A1 ) | ( 0x01 << COM1A0 ) , BIT_MASK ( COM1A1 ) | BIT_MASK ( COM1A0 ) );
                    break;
                default:
                    opResult = TIMER_ERR_FAST_PWM_SETTING;
            }
            break;
        case TIMER_1B :
            switch ( settingToSet )
            {
                case CORRECT_PWM_NORMAL :
                    REPLACE_BITS ( TCCR1B , ( 0x00 << COM1B1 ) | ( 0x00 << COM1B0 ) , BIT_MASK ( COM1B1 ) | BIT_MASK ( COM1B0 ) );
                    break;
                case CORRECT_PWM_CORRECT :
                    REPLACE_BITS ( TCCR1B , ( 0x00 << COM1B1 ) | ( 0x01 << COM1B0 ) , BIT_MASK ( COM1B1 ) | BIT_MASK ( COM1B0 ) );
                    break;
                case CORRECT_PWM_CLEAR_MATCH_UP_SET_MATCH_DOWN :
                    REPLACE_BITS ( TCCR1B , ( 0x01 << COM1B1 ) | ( 0x00 << COM1B0 ) , BIT_MASK ( COM1B1 ) | BIT_MASK ( COM1B0 ) );
                    break;
                case CORRECT_PWM_SET_MATCH_UP_CLEAR_MATCH_DOWN :
                    REPLACE_BITS ( TCCR1B , ( 0x01 << COM1B1 ) | ( 0x01 << COM1B0 ) , BIT_MASK ( COM1B1 ) | BIT_MASK ( COM1B0 ) );
                    break;
                default:
                    opResult = TIMER_ERR_FAST_PWM_SETTING;
            }
            break;
        case TIMER_2 :
            switch ( settingToSet )
            {
                case CORRECT_PWM_NORMAL :
                    REPLACE_BITS ( TCCR2 , ( 0x00 << COM21 ) | ( 0x00 << COM20 ) , BIT_MASK ( COM21 ) | BIT_MASK ( COM20 ) );
                    break;
                case CORRECT_PWM_CLEAR_MATCH_UP_SET_MATCH_DOWN :
                    REPLACE_BITS ( TCCR2 , ( 0x01 << COM21 ) | ( 0x00 << COM20 ) , BIT_MASK ( COM21 ) | BIT_MASK ( COM20 ) );
                    break;
                case CORRECT_PWM_SET_MATCH_UP_CLEAR_MATCH_DOWN :
                    REPLACE_BITS ( TCCR2 , ( 0x01 << COM21 ) | ( 0x01 << COM20 ) , BIT_MASK ( COM21 ) | BIT_MASK ( COM20 ) );
                    break;
                case CORRECT_PWM_CORRECT :
                default:
                    opResult = TIMER_ERR_FAST_PWM_SETTING;
            }
            break;
        default:
            opResult = TIMER_ERR_TIMER_NUM;
    }
    return opResult;
}
TIMER_STD_ERR_t TIMER_get ( TIMER_t timer , uint16_t* timerValue )
{
    TIMER_STD_ERR_t opResult = TIMER_OK;
    switch ( timer )
    {
        case TIMER_0 :
            *timerValue = ( uint16_t ) TCNT0;
            break;
        case TIMER_1A :
        case TIMER_1B :
        case TIMER_1 :
#if USE_PROTECTED_SECTIONS == 1
            uint8_t intBit = ( uint8_t ) READ_BIT ( SREG , SREG_I );
            cli ();
#endif
            *timerValue = ( uint16_t ) ( ( ( uint16_t ) TCNT1L ) | ( ( ( uint16_t ) TCNT1H ) << 0x08 ) );
#if USE_PROTECTED_SECTIONS == 1
            REPLACE_BIT ( SREG , SREG_I , intBit );
#endif
            break;
        case TIMER_2 :
            *timerValue = ( uint16_t ) TCNT2;
            break;
        default:
            opResult = TIMER_ERR_TIMER_NUM;
    }
    return opResult;
}
TIMER_STD_ERR_t TIMER_set ( TIMER_t timer , uint16_t timerValue )
{
    TIMER_STD_ERR_t opResult = TIMER_OK;
    switch ( timer )
    {
        case TIMER_0 :
            if ( timerValue <= MAX_SMALL_TIMER_VALUE )
            {
                TCNT0 = ( uint8_t ) timerValue;
            }
            else
            {
                opResult = TIMER_ERR_TIMER_VALUE;
            }
            break;
        case TIMER_1A :
        case TIMER_1B :
        case TIMER_1 :
            TCNT1 = timerValue;
            break;
        case TIMER_2 :
            if ( timerValue <= MAX_SMALL_TIMER_VALUE )
            {
                TCNT2 = ( uint8_t ) timerValue;
            }
            else
            {
                opResult = TIMER_ERR_TIMER_VALUE;
            }
            break;
        default:
            opResult = TIMER_ERR_TIMER_NUM;
    }
    return opResult;
}
