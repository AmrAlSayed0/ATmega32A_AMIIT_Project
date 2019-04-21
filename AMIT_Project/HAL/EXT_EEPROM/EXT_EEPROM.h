#ifndef AMIT_PROJECT_EXT_EEPROM_H_
#define AMIT_PROJECT_EXT_EEPROM_H_
//24AA1025
#include "std_types.h"
typedef enum _EXT_EEPROM_STD_ERR_t
{
    EXT_EEPROM_OK ,
    EXT_EEPROM_ERR_ADDR ,
    EXT_EEPROM_ERR_SIZE ,
    EXT_EEPROM_ERR_START_COM ,
    EXT_EEPROM_ERR_CTRL_COM ,
    EXT_EEPROM_ERR_ADDR_COM ,
    EXT_EEPROM_ERR_DATA_COM
} EXT_EEPROM_STD_ERR_t;
void EXT_EEPROM_waitBusy ( void );
EXT_EEPROM_STD_ERR_t EXT_EEPROM_read ( uint32_t addr , uint8_t* readValue );
EXT_EEPROM_STD_ERR_t EXT_EEPROM_readSection ( uint32_t addr , uint32_t readSize , uint8_t readValues[readSize] );
EXT_EEPROM_STD_ERR_t EXT_EEPROM_write ( uint32_t addr , uint8_t valueToWrite );
EXT_EEPROM_STD_ERR_t EXT_EEPROM_writeSection ( uint32_t addr , uint32_t writeSize , uint8_t valuesToWrite[writeSize] );
EXT_EEPROM_STD_ERR_t EXT_EEPROM_fill ( uint32_t addr , uint32_t writeSize , uint8_t fillValue );
EXT_EEPROM_STD_ERR_t EXT_EEPROM_copy ( uint32_t destAddr , uint32_t sourceAddr , uint32_t sizeToCopy );
EXT_EEPROM_STD_ERR_t EXT_EEPROM_move ( uint32_t destAddr , uint32_t sourceAddr , uint32_t sizeToMove );
#endif
