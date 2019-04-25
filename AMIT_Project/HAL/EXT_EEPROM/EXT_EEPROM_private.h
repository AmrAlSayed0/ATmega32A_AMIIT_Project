#ifndef AMIT_PROJECT_EXT_EEPROM_PRIVATE_H_
#define AMIT_PROJECT_EXT_EEPROM_PRIVATE_H_
static EXT_EEPROM_STD_ERR_t read ( uint32_t addr , uint8_t* readValue );
static EXT_EEPROM_STD_ERR_t write ( uint32_t addr , uint8_t valueToWrite );
#endif