#ifndef AMIT_PROJECT_EEPROM_H_
#define AMIT_PROJECT_EEPROM_H_
#include "Std_Types.h"
typedef enum _EEPROM_STD_ERR_t
{
    EEPROM_OK = ( uint8_t ) 0 ,
    EEPROM_ERR_ADDR = ( uint8_t ) 1 ,
    EEPROM_ERR_SIZE = ( uint8_t ) 2
} EEPROM_STD_ERR_t;
EEPROM_STD_ERR_t EEPROM_read ( uint16_t addr , uint8_t* readValue );
EEPROM_STD_ERR_t EEPROM_readSection ( uint16_t addr , uint16_t readSize , uint8_t readValues[readSize] );
EEPROM_STD_ERR_t EEPROM_write ( uint16_t addr , uint8_t valueToWrite );
EEPROM_STD_ERR_t EEPROM_writeSection ( uint16_t addr , uint16_t writeSize , uint8_t valuesToWrite[writeSize] );
EEPROM_STD_ERR_t EEPROM_fill ( uint16_t addr , uint16_t writeSize , uint8_t fillValue );
EEPROM_STD_ERR_t EEPROM_copy ( uint16_t destAddr , uint16_t sourceAddr , uint16_t sizeToCopy );
EEPROM_STD_ERR_t EEPROM_move ( uint16_t destAddr , uint16_t sourceAddr , uint16_t sizeToMove );
#endif
