#ifndef AMIT_PROJECT_WTCHDG_H_
#define AMIT_PROJECT_WTCHDG_H_ 
#include "std_types.h"
typedef enum _WTCHDG_PRESCALLER_t
{
    WTCHDG_PRESCALLER_16K = ( uint8_t ) 0 ,
    WTCHDG_PRESCALLER_32K = ( uint8_t ) 1 ,
    WTCHDG_PRESCALLER_64k = ( uint8_t ) 2 ,
    WTCHDG_PRESCALLER_128K = ( uint8_t ) 3 ,
    WTCHDG_PRESCALLER_256K = ( uint8_t ) 4 ,
    WTCHDG_PRESCALLER_512K = ( uint8_t ) 5 ,
    WTCHDG_PRESCALLER_1024K = ( uint8_t ) 6 ,
    WTCHDG_PRESCALLER_2048K = ( uint8_t ) 7 ,
    NUM_OF_WTCHDG_PRESCALLERS
} WTCHDG_PRESCALLER_t;
typedef enum _WTCHDG_STD_ERR_t
{
    WTCHDG_OK = ( uint8_t ) 0 ,
    WTCHDG_ERR_PRESC = ( uint8_t ) 1
} WTCHDG_STD_ERR_t;
WTCHDG_STD_ERR_t WTCHDG_setPrescaller ( WTCHDG_PRESCALLER_t prescSetting );
WTCHDG_PRESCALLER_t WTCHDG_getPrescaller ( void );
void WTCHDG_enable ( void );
void WTCHDG_disable ( void );
void WTCHDG_reset ( void );
#endif
