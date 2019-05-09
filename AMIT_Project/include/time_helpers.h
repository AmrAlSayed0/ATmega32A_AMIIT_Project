#ifndef AMIT_PROJECT_TIME_HELPERS_H_
#define AMIT_PROJECT_TIME_HELPERS_H_
#include "FreeRTOS.h"
#include <math.h>
#if ( configCPU_CLOCK_HZ != F_CPU )
    #error "Conflict between configCPU_CLOCK_HZ and F_CPU"
#endif
static inline uint16_t calcTicksFromTimeMs ( double numOfMilliseconds )
{
    return ( uint16_t ) ceil ( numOfMilliseconds * ( ( ( ( double ) F_CPU ) / ( ( double ) configTICK_RATE_HZ ) ) / ( ( double ) 1000 ) ) );
}
#endif