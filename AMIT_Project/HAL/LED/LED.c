#include "DIO.h"
#include "LED_private.h"
#include "LED_config.h"
#include "LED.h"
#ifndef LED_H_
#define LED_H_
void LED_init ( void )
{
    DIO_setDirection ( LED_1_PORT , LED_1_PIN , DIRECTION_OUTPUT );
    DIO_write ( LED_1_PORT , LED_1_PIN , PIN_STATE_LOW );
    DIO_setDirection ( LED_2_PORT , LED_2_PIN , DIRECTION_OUTPUT );
    DIO_write ( LED_2_PORT , LED_2_PIN , PIN_STATE_LOW );
}
void LED_turnOn ( LED_t led )
{
    switch ( led )
    {
        case LED_1 :
            DIO_write ( LED_1_PORT , LED_1_PIN , PIN_STATE_HIGH );
            break;
        case LED_2 :
            DIO_write ( LED_2_PORT , LED_2_PIN , PIN_STATE_HIGH );
            break;
        default:;
    }
}
void LED_turnOff ( LED_t led )
{
    switch ( led )
    {
        case LED_1 :
            DIO_write ( LED_1_PORT , LED_1_PIN , PIN_STATE_LOW );
            break;
        case LED_2 :
            DIO_write ( LED_2_PORT , LED_2_PIN , PIN_STATE_LOW );
            break;
        default:;
    }
}
#endif
