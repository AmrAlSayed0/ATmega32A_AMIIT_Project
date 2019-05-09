#ifndef AMIT_PROJECT_I2C_H_
#define AMIT_PROJECT_I2C_H_
#ifndef F_CPU
    #error "CPU clock frequency not defined"
#endif
#include "std_types.h"
typedef enum _I2C_TRANS_MODE_t
{
    I2C_NONE = ( uint8_t ) 0 ,
    I2C_MASTER_TRANSMITTER = ( uint8_t ) 1 ,
    I2C_MASTER_RECEIVER = ( uint8_t ) 2 ,
    I2C_SLAVE_TRANSMITTER = ( uint8_t ) 3 ,
    I2C_SLAVE_RECEIVER = ( uint8_t ) 4
} I2C_TRANS_MODE_t;
typedef enum _I2C_STATUS_t
{
    I2C_STATUS_BUS_ERROR = ( uint8_t ) 0 ,
    I2C_STATUS_START_TRANS = ( uint8_t ) 0x08 ,
    I2C_STATUS_REP_START_TRANS = ( uint8_t ) 0x10 ,
    I2C_STATUS_M_SLW_W_TRANS_ACK_REC = ( uint8_t ) 0x18 ,
    I2C_STATUS_M_SLW_W_TRANS_NACK_REC = ( uint8_t ) 0x20 ,
    I2C_STATUS_M_DATA_TRANS_ACK_REC = ( uint8_t ) 0x28 ,
    I2C_STATUS_M_DATA_TRANS_NACK_REC = ( uint8_t ) 0x30 ,
    I2C_STATUS_M_ARB_LOST = ( uint8_t ) 0x38 ,
    I2C_STATUS_M_SLW_R_TRANS_ACK_REC = ( uint8_t ) 0x40 ,
    I2C_STATUS_M_SLW_R_TRANS_NACK_REC = ( uint8_t ) 0x48 ,
    I2C_STATUS_M_DATA_REC_ACK_TRANS = ( uint8_t ) 0x50 ,
    I2C_STATUS_M_DATA_REC_NACK_TRANS = ( uint8_t ) 0x58 ,
    I2C_STATUS_S_SLA_W_REC_ACK_TRANS = ( uint8_t ) 0x60 ,
    I2C_STATUS_S_SLA_W_REC_ACK_TRANS_ARB_LOST = ( uint8_t ) 0x68 ,
    I2C_STATUS_S_GEN_CALL_REC_ACK_TRANS = ( uint8_t ) 0x70 ,
    I2C_STATUS_S_GEN_CALL_REC_ACK_TRANS_ARB_LOST = ( uint8_t ) 0x78 ,
    I2C_STATUS_S_SLA_DATA_REC_ACK_TRANS = ( uint8_t ) 0x80 ,
    I2C_STATUS_S_SLA_DATA_REC_NACK_TRANS = ( uint8_t ) 0x88 ,
    I2C_STATUS_S_GEN_DATA_REC_ACK_TRANS = ( uint8_t ) 0x90 ,
    I2C_STATUS_S_GEN_DATA_REC_NACK_TRANS = ( uint8_t ) 0x98 ,
    I2C_STATUS_S_STOP_REP_START_REC = ( uint8_t ) 0xA0 ,
    I2C_STATUS_S_SLA_R_REC_ACK_TRANS = ( uint8_t ) 0xA8 ,
    I2C_STATUS_S_SLA_R_REC_ACK_TRANS_ARB_LOST = ( uint8_t ) 0xB0 ,
    I2C_STATUS_S_DATA_TRANS_ACK_REC = ( uint8_t ) 0xB8 ,
    I2C_STATUS_S_DATA_TRANS_NACK_REC = ( uint8_t ) 0xC0 ,
    I2C_STATUS_S_LAST_DATA_TRANS_ACK_REC = ( uint8_t ) 0xC8 ,
    I2C_STATUS_NO_INFO = ( uint8_t ) 0xF8
} I2C_STATUS_t;
typedef enum _I2C_STD_ERR_t
{
    I2C_OK = ( uint8_t ) 0 ,
    I2C_ERR_SPEED = ( uint8_t ) 1 ,
    I2C_ERR_SLAVE_ADDR = ( uint8_t ) 2 ,
    I2C_ERR_COM = ( uint8_t ) 3
} I2C_STD_ERR_t;
void I2C_waitOperation ( void );
I2C_STATUS_t I2C_readStatus ( void );
I2C_STD_ERR_t I2C_masterInit ( uint32_t speed );
void I2C_start ( void );
void I2C_repStart ( void );
I2C_STD_ERR_t I2C_sendAddrAndRead ( uint8_t addr );
I2C_STD_ERR_t I2C_sendAddrAndWrite ( uint8_t addr );
void I2C_sendData ( uint8_t data );
uint8_t I2C_receiveDataWithAck ( void );
uint8_t I2C_receiveDataWithNack ( void );
void I2C_stop ( void );
void I2C_sendAck ( void );
void I2C_sendNack ( void );
I2C_STD_ERR_t I2C_slaveInit ( uint8_t addr , bool generalCallEnable );
#endif
