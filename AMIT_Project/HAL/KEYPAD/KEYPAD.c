#include "BitHelpers.h"
#include "common.h"
#include "DIO.h"
#include "KEYPAD_private.h"
#include "KEYPAD_config.h"
#include "KEYPAD.h"
void KEYPAD_init ( void )
{
    /* Columns */
    DIO_setDirection ( KEYPAD_COLUMN_1_PORT , KEYPAD_COLUMN_1_PIN , DIRECTION_INPUT );
    DIO_setResistor ( KEYPAD_COLUMN_1_PORT , KEYPAD_COLUMN_1_PIN , RESISTOR_PULL_UP );
    DIO_setDirection ( KEYPAD_COLUMN_2_PORT , KEYPAD_COLUMN_2_PIN , DIRECTION_INPUT );
    DIO_setResistor ( KEYPAD_COLUMN_2_PORT , KEYPAD_COLUMN_2_PIN , RESISTOR_PULL_UP );
    DIO_setDirection ( KEYPAD_COLUMN_3_PORT , KEYPAD_COLUMN_3_PIN , DIRECTION_INPUT );
    DIO_setResistor ( KEYPAD_COLUMN_3_PORT , KEYPAD_COLUMN_3_PIN , RESISTOR_PULL_UP );
    DIO_setDirection ( KEYPAD_COLUMN_4_PORT , KEYPAD_COLUMN_4_PIN , DIRECTION_INPUT );
    DIO_setResistor ( KEYPAD_COLUMN_4_PORT , KEYPAD_COLUMN_4_PIN , RESISTOR_PULL_UP );
    /* Rows */
    DIO_setDirection ( KEYPAD_ROW_A_PORT , KEYPAD_ROW_A_PIN , DIRECTION_OUTPUT );
    DIO_write ( KEYPAD_ROW_A_PORT , KEYPAD_ROW_A_PIN , PIN_STATE_HIGH );
    DIO_setDirection ( KEYPAD_ROW_B_PORT , KEYPAD_ROW_B_PIN , DIRECTION_OUTPUT );
    DIO_write ( KEYPAD_ROW_B_PORT , KEYPAD_ROW_B_PIN , PIN_STATE_HIGH );
    DIO_setDirection ( KEYPAD_ROW_C_PORT , KEYPAD_ROW_C_PIN , DIRECTION_OUTPUT );
    DIO_write ( KEYPAD_ROW_C_PORT , KEYPAD_ROW_C_PIN , PIN_STATE_HIGH );
    DIO_setDirection ( KEYPAD_ROW_D_PORT , KEYPAD_ROW_D_PIN , DIRECTION_OUTPUT );
    DIO_write ( KEYPAD_ROW_D_PORT , KEYPAD_ROW_D_PIN , PIN_STATE_HIGH );
}
uint16_t KEYPAD_getPressedKey ( void )
{
    uint16_t pressedKeys = KEY_NONE;
    DIO_write ( KEYPAD_ROW_A_PORT , KEYPAD_ROW_A_PIN , PIN_STATE_LOW );
    DIO_write ( KEYPAD_ROW_B_PORT , KEYPAD_ROW_B_PIN , PIN_STATE_HIGH );
    DIO_write ( KEYPAD_ROW_C_PORT , KEYPAD_ROW_C_PIN , PIN_STATE_HIGH );
    DIO_write ( KEYPAD_ROW_D_PORT , KEYPAD_ROW_D_PIN , PIN_STATE_HIGH );
    PIN_STATE_t pinState = PIN_STATE_NOT_CARE;
    DIO_read ( KEYPAD_COLUMN_1_PORT , KEYPAD_COLUMN_1_PIN , &pinState );
    if ( pinState == PIN_STATE_LOW )
    {
        pressedKeys |= KEY_7;
    }
    pinState = PIN_STATE_NOT_CARE;
    DIO_read ( KEYPAD_COLUMN_2_PORT , KEYPAD_COLUMN_2_PIN , &pinState );
    if ( pinState == PIN_STATE_LOW )
    {
        pressedKeys |= KEY_8;
    }
    pinState = PIN_STATE_NOT_CARE;
    DIO_read ( KEYPAD_COLUMN_3_PORT , KEYPAD_COLUMN_3_PIN , &pinState );
    if ( pinState == PIN_STATE_LOW )
    {
        pressedKeys |= KEY_9;
    }
    pinState = PIN_STATE_NOT_CARE;
    DIO_read ( KEYPAD_COLUMN_4_PORT , KEYPAD_COLUMN_4_PIN , &pinState );
    if ( pinState == PIN_STATE_LOW )
    {
        pressedKeys |= KEY_DIV;
    }
    DIO_write ( KEYPAD_ROW_A_PORT , KEYPAD_ROW_A_PIN , PIN_STATE_HIGH );
    DIO_write ( KEYPAD_ROW_B_PORT , KEYPAD_ROW_B_PIN , PIN_STATE_LOW );
    DIO_write ( KEYPAD_ROW_C_PORT , KEYPAD_ROW_C_PIN , PIN_STATE_HIGH );
    DIO_write ( KEYPAD_ROW_D_PORT , KEYPAD_ROW_D_PIN , PIN_STATE_HIGH );
    pinState = PIN_STATE_NOT_CARE;
    DIO_read ( KEYPAD_COLUMN_1_PORT , KEYPAD_COLUMN_1_PIN , &pinState );
    if ( pinState == PIN_STATE_LOW )
    {
        pressedKeys |= KEY_4;
    }
    pinState = PIN_STATE_NOT_CARE;
    DIO_read ( KEYPAD_COLUMN_2_PORT , KEYPAD_COLUMN_2_PIN , &pinState );
    if ( pinState == PIN_STATE_LOW )
    {
        pressedKeys |= KEY_5;
    }
    pinState = PIN_STATE_NOT_CARE;
    DIO_read ( KEYPAD_COLUMN_3_PORT , KEYPAD_COLUMN_3_PIN , &pinState );
    if ( pinState == PIN_STATE_LOW )
    {
        pressedKeys |= KEY_6;
    }
    pinState = PIN_STATE_NOT_CARE;
    DIO_read ( KEYPAD_COLUMN_4_PORT , KEYPAD_COLUMN_4_PIN , &pinState );
    if ( pinState == PIN_STATE_LOW )
    {
        pressedKeys |= KEY_MULT;
    }
    DIO_write ( KEYPAD_ROW_A_PORT , KEYPAD_ROW_A_PIN , PIN_STATE_HIGH );
    DIO_write ( KEYPAD_ROW_B_PORT , KEYPAD_ROW_B_PIN , PIN_STATE_HIGH );
    DIO_write ( KEYPAD_ROW_C_PORT , KEYPAD_ROW_C_PIN , PIN_STATE_LOW );
    DIO_write ( KEYPAD_ROW_D_PORT , KEYPAD_ROW_D_PIN , PIN_STATE_HIGH );
    pinState = PIN_STATE_NOT_CARE;
    DIO_read ( KEYPAD_COLUMN_1_PORT , KEYPAD_COLUMN_1_PIN , &pinState );
    if ( pinState == PIN_STATE_LOW )
    {
        pressedKeys |= KEY_1;
    }
    pinState = PIN_STATE_NOT_CARE;
    DIO_read ( KEYPAD_COLUMN_2_PORT , KEYPAD_COLUMN_2_PIN , &pinState );
    if ( pinState == PIN_STATE_LOW )
    {
        pressedKeys |= KEY_2;
    }
    pinState = PIN_STATE_NOT_CARE;
    DIO_read ( KEYPAD_COLUMN_3_PORT , KEYPAD_COLUMN_3_PIN , &pinState );
    if ( pinState == PIN_STATE_LOW )
    {
        pressedKeys |= KEY_3;
    }
    pinState = PIN_STATE_NOT_CARE;
    DIO_read ( KEYPAD_COLUMN_4_PORT , KEYPAD_COLUMN_4_PIN , &pinState );
    if ( pinState == PIN_STATE_LOW )
    {
        pressedKeys |= KEY_NEG;
    }
    DIO_write ( KEYPAD_ROW_A_PORT , KEYPAD_ROW_A_PIN , PIN_STATE_HIGH );
    DIO_write ( KEYPAD_ROW_B_PORT , KEYPAD_ROW_B_PIN , PIN_STATE_HIGH );
    DIO_write ( KEYPAD_ROW_C_PORT , KEYPAD_ROW_C_PIN , PIN_STATE_HIGH );
    DIO_write ( KEYPAD_ROW_D_PORT , KEYPAD_ROW_D_PIN , PIN_STATE_LOW );
    pinState = PIN_STATE_NOT_CARE;
    DIO_read ( KEYPAD_COLUMN_1_PORT , KEYPAD_COLUMN_1_PIN , &pinState );
    if ( pinState == PIN_STATE_LOW )
    {
        pressedKeys |= KEY_C;
    }
    pinState = PIN_STATE_NOT_CARE;
    DIO_read ( KEYPAD_COLUMN_2_PORT , KEYPAD_COLUMN_2_PIN , &pinState );
    if ( pinState == PIN_STATE_LOW )
    {
        pressedKeys |= KEY_0;
    }
    pinState = PIN_STATE_NOT_CARE;
    DIO_read ( KEYPAD_COLUMN_3_PORT , KEYPAD_COLUMN_3_PIN , &pinState );
    if ( pinState == PIN_STATE_LOW )
    {
        pressedKeys |= KEY_EQ;
    }
    pinState = PIN_STATE_NOT_CARE;
    DIO_read ( KEYPAD_COLUMN_4_PORT , KEYPAD_COLUMN_4_PIN , &pinState );
    if ( pinState == PIN_STATE_LOW )
    {
        pressedKeys |= KEY_PLUS;
    }
    DIO_write ( KEYPAD_ROW_A_PORT , KEYPAD_ROW_A_PIN , PIN_STATE_HIGH );
    DIO_write ( KEYPAD_ROW_B_PORT , KEYPAD_ROW_B_PIN , PIN_STATE_HIGH );
    DIO_write ( KEYPAD_ROW_C_PORT , KEYPAD_ROW_C_PIN , PIN_STATE_HIGH );
    DIO_write ( KEYPAD_ROW_D_PORT , KEYPAD_ROW_D_PIN , PIN_STATE_HIGH );
    return pressedKeys;
}
