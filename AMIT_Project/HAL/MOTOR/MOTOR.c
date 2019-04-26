#include <math.h>
#include "DIO.h"
#include "TIMER.h"
#include "MOTOR.h"
#include "MOTOR_config.h"
#include "MOTOR_private.h"
uint8_t currentSpeed = 0;
MOTOR_DIRECTION_t currentDirection = MOTOR_CLOCKWISE;
#define MAX_SPEED 1
void MOTOR_init ( void )
{
    DIO_setDirection ( PWM_CONTROL_PORT , PWM_CONTROL_PIN , DIRECTION_OUTPUT );
    DIO_setDirection ( PULSE_PORT , PULSE_PIN , DIRECTION_OUTPUT );
}
MOTOR_STD_ERR_t MOTOR_setSpeed ( double speed )
{
    MOTOR_STD_ERR_t opResult = MOTOR_OK;
    if ( speed >= 0 && speed <= MAX_SPEED )
    {
        currentSpeed = speed;
        uint8_t roundedOcrValue = ( uint8_t ) round ( speed * ( ( double ) 255 ) );
        TIMER_setMode ( PWM_TIMER , TIMER_MODE_FAST_PWM_MAX_TOP );
        switch ( currentDirection )
        {
            case MOTOR_CLOCKWISE :
                TIMER_setFastPwmSetting ( PWM_TIMER , FAST_PWM_CLEAR_MATCH_SET_BOTTOM );
                break;
            case MOTOR_ANTICLOCKWISE :
                TIMER_setFastPwmSetting ( PWM_TIMER , FAST_PWM_SET_MATCH_CLEAR_BOTTOM );
                break;
            default:;
        }
        TIMER_setOcr ( PWM_TIMER , roundedOcrValue );
    }
    else
    {
        opResult = MOTOR_ERR_SPEED;
    }
    return opResult;
}
MOTOR_STD_ERR_t MOTOR_setDirection ( MOTOR_DIRECTION_t direction )
{
    MOTOR_STD_ERR_t opResult = MOTOR_OK;
    currentDirection = direction;
    switch ( direction )
    {
        case MOTOR_CLOCKWISE :
            DIO_write ( PWM_CONTROL_PORT , PWM_CONTROL_PIN , PIN_STATE_LOW );
            TIMER_setFastPwmSetting ( PWM_TIMER , FAST_PWM_CLEAR_MATCH_SET_BOTTOM );
            break;
        case MOTOR_ANTICLOCKWISE :
            DIO_write ( PWM_CONTROL_PORT , PWM_CONTROL_PIN , PIN_STATE_HIGH );
            TIMER_setFastPwmSetting ( PWM_TIMER , FAST_PWM_SET_MATCH_CLEAR_BOTTOM );
            break;
        default:
            opResult = MOTOR_ERR_DIRECTION;
    }
    return opResult;
}
void MOTOR_start ()
{
    TIMER_setPrescaller ( PWM_TIMER , TIMER_CLCK_PRESC_256 );
    switch ( currentDirection )
    {
        case MOTOR_CLOCKWISE :
            TIMER_setFastPwmSetting ( PWM_TIMER , FAST_PWM_CLEAR_MATCH_SET_BOTTOM );
            break;
        case MOTOR_ANTICLOCKWISE :
            TIMER_setFastPwmSetting ( PWM_TIMER , FAST_PWM_SET_MATCH_CLEAR_BOTTOM );
            break;
        default:;
    }
}
void MOTOR_stop ()
{
    TIMER_setPrescaller ( PWM_TIMER , TIMER_CLCK_NO );
    TIMER_setFastPwmSetting ( PWM_TIMER , FAST_PWM_NORMAL );
    DIO_write ( PULSE_PORT , PULSE_PIN , PIN_STATE_LOW );
    DIO_write ( PWM_CONTROL_PORT , PWM_CONTROL_PIN , PIN_STATE_LOW );
}
