#ifndef AMIT_PROJECT_LED_H_
#define AMIT_PROJECT_LED_H_
typedef enum _LED_t
{
    LED_1 ,
    LED_2
} LED_t;
void LED_init ( void );
void LED_turnOn ( LED_t led );
void LED_turnOff ( LED_t led );
#endif
