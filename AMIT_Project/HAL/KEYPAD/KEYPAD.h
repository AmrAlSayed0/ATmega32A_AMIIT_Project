#ifndef AMIT_PROJECT_KEYPAD_H_
#define AMIT_PROJECT_KEYPAD_H_
#define KEY_NONE    ( ( uint16_t ) 0 )
#define KEY_0       ( ( uint16_t ) ( 0x01 << 0x00 ) )
#define KEY_1       ( ( uint16_t ) ( 0x01 << 0x01 ) )
#define KEY_2       ( ( uint16_t ) ( 0x01 << 0x02 ) )
#define KEY_3       ( ( uint16_t ) ( 0x01 << 0x03 ) )
#define KEY_4       ( ( uint16_t ) ( 0x01 << 0x04 ) )
#define KEY_5       ( ( uint16_t ) ( 0x01 << 0x05 ) )
#define KEY_6       ( ( uint16_t ) ( 0x01 << 0x06 ) )
#define KEY_7       ( ( uint16_t ) ( 0x01 << 0x07 ) )
#define KEY_8       ( ( uint16_t ) ( 0x01 << 0x08 ) )
#define KEY_9       ( ( uint16_t ) ( 0x01 << 0x09 ) )
#define KEY_C       ( ( uint16_t ) ( 0x01 << 0x0A ) )
#define KEY_EQ      ( ( uint16_t ) ( 0x01 << 0x0B ) )
#define KEY_PLUS    ( ( uint16_t ) ( 0x01 << 0x0C ) )
#define KEY_NEG     ( ( uint16_t ) ( 0x01 << 0x0D ) )
#define KEY_MULT    ( ( uint16_t ) ( 0x01 << 0x0E ) )
#define KEY_DIV     ( ( uint16_t ) ( 0x01 << 0x0F ) )
void KEYPAD_init ( void );
uint16_t KEYPAD_getPressedKey ( void );
#endif
