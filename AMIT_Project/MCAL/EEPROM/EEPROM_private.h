#ifndef AMIT_PROJECT_EEPROM_PRIVATE_H_
#define AMIT_PROJECT_EEPROM_PRIVATE_H_
#include "std_types.h"
static inline uint8_t read ( uint16_t addr );
static inline void write ( uint16_t addr , uint8_t valueToWrite );
#endif