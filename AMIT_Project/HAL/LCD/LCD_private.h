#ifndef AMIT_PROJECT_LCD_PRIVATE_H_
#define AMIT_PROJECT_LCD_PRIVATE_H_
#define NUMERIC_STRING_LENGTH    6
static bool data8Bit = false;
static char numericString[NUMERIC_STRING_LENGTH];
static void enable ( void );
static void waitBusy ( void );
static void intToString ( uint16_t number );
#endif