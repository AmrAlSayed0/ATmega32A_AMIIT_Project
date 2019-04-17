#ifndef AMIT_PROJECT_SLEEP_H_
#define AMIT_PROJECT_SLEEP_H_
typedef enum _SLEEP_MODE_t
{
    SLEEP_MOD_IDLE = ( uint8_t ) 0 ,
    SLEEP_MOD_ADC = ( uint8_t ) 1 ,
    SLEEP_MOD_PWR_DOWN = ( uint8_t ) 2 ,
    SLEEP_MOD_PWR_SAVE = ( uint8_t ) 3 ,
    SLEEP_MOD_STANDBY = ( uint8_t ) 6 ,
    SLEEP_MOD_EXT_STANDBY = ( uint8_t ) 7
} SLEEP_MODE_t;
typedef enum _SLEEP_STD_ERR_t
{
    SLEEP_OK = ( uint8_t ) 0 ,
    SLEEP_ERR_MODE = ( uint8_t ) 1
} SLEEP_STD_ERR_t;
void SLEEP_enable ( void );
void SLEEP_disable ( void );
void SLEEP_sleep ( void );
SLEEP_STD_ERR_t SLEEP_setMode ( SLEEP_MODE_t mode );
SLEEP_MODE_t SLEEP_getMode ( void );
#endif
