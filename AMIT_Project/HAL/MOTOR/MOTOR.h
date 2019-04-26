#ifndef AMIT_PROJECT_MOTOR_H_
#define AMIT_PROJECT_MOTOR_H_
typedef enum _MOTOR_STD_ERR_t
{
    MOTOR_OK ,
    MOTOR_ERR_SPEED,
    MOTOR_ERR_DIRECTION
} MOTOR_STD_ERR_t;
typedef enum _MOTOR_DIRECTION_t
{
    MOTOR_CLOCKWISE,
    MOTOR_ANTICLOCKWISE    
} MOTOR_DIRECTION_t;
void MOTOR_init ( void );
MOTOR_STD_ERR_t MOTOR_setSpeed ( double speed );
MOTOR_STD_ERR_t MOTOR_setDirection ( MOTOR_DIRECTION_t direction );
void MOTOR_start ();
void MOTOR_stop ();
#endif
