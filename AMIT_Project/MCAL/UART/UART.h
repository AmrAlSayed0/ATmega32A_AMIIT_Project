#ifndef AMIT_PROJECT_UART_H_
#define AMIT_PROJECT_UART_H_
#include "std_types.h"
#include "common.h"
typedef enum _UART_TRANS_SPEED_t
{
    UART_NORMAL_SPEED = (uint8_t) 0 ,
    UART_DOUBLE_SPEED  = (uint8_t) 1 ,
    UART_NOT_CARE_SPEED = (uint8_t) 2 
} UART_TRANS_SPEED_t;
typedef enum _UART_PROCESS_MODE_t
{
    UART_PROC_MODE_SINGLE = (uint8_t) 0 ,
    UART_PROC_MODE_MULTI = (uint8_t) 1
} UART_PROCESS_MODE_t;
typedef enum _UART_TRANS_MODE_t
{
    UART_TRANS_ASYNC = (uint8_t) 0 ,
    UART_TRANS_SYNC = (uint8_t) 1
} UART_TRANS_MODE_t;
typedef enum _UART_INT_FLAG_t
{
    UART_FLAG_REC_COMP = (uint8_t) 0 ,
    UART_FLAG_TRANS_COMP  = (uint8_t) 1,
    UART_FLAG_EMPTY = (uint8_t) 2
} UART_INT_FLAG_t;
typedef enum _UART_ERR_FLAG_t
{
    UART_ERR_FLAG_FRAME = (uint8_t) 0 ,
    UART_ERR_FLAG_OVERRUN = (uint8_t) 1 ,
    UART_ERR_FLAG_PARITY = (uint8_t) 2
} UART_ERR_FLAG_t;
typedef enum _UART_STD_ERR_t
{
    UART_OK ,
    UART_ERR_BAUD_RATE ,
    UART_ERR_UBBR ,
    UART_ERR_TRANS ,
    UART_ERR_RECV ,
    UART_ERR_DATA_FRAME_SIZE ,
    UART_ERR_PARITY ,
    UART_ERR_STP ,
    UART_ERR_TRANS_SPEED ,
    UART_ERR_POLARITY ,
    UART_ERR_TRANS_MODE ,
    UART_ERR_MULTI ,
    UART_ERR_INT_TYPE ,
    UART_ERR_ERR_TYPE
} UART_STD_ERR_t;
typedef enum _COM_STATE_t
{
    UART_COM_DISABLED = (uint8_t) 0 ,
    UART_COM_ENABLED = (uint8_t) 1
} COM_STATE_t;
typedef enum _UART_DATA_SIZE_t
{
    UART_DATA_SIZE_5_BIT = (uint8_t) 0 ,
    UART_DATA_SIZE_6_BIT = (uint8_t) 1 ,
    UART_DATA_SIZE_7_BIT = (uint8_t) 2 ,
    UART_DATA_SIZE_8_BIT = (uint8_t) 3 ,
    UART_DATA_SIZE_9_BIT = (uint8_t) 4
} UART_DATA_SIZE_t;
typedef enum _UART_PARITY_t
{
    UART_PARITY_NO = (uint8_t) 0 ,
    UART_PARITY_EVEN = (uint8_t) 1 ,
    UART_PARITY_ODD = (uint8_t) 2
} UART_PARITY_t;
typedef enum _UART_STP_SIZE_t
{
    UART_STP_SIZE_1_BIT = (uint8_t) 0 ,
    UART_STP_SIZE_2_BIT = (uint8_t) 1 ,
} UART_STP_SIZE_t;
typedef enum _UART_CLCK_POLARITY_t
{
    UART_CLCK_POLARITY_RISING_FALLING = (uint8_t) 0 ,
    UART_CLCK_POLARITY_FALLING_RISING  = (uint8_t) 1,
    UART_CLCK_POLARITY_NOT_CARE = (uint8_t) 2
} UART_CLCK_POLARITY_t;
typedef struct _UART_CNF_t
{
    uint32_t baudRate;
    UART_TRANS_SPEED_t transmissionSpeedMode;
    UART_PROCESS_MODE_t multiProcessorMode;
    UART_TRANS_MODE_t transmissionMode;
    COM_STATE_t transmitterState;
    COM_STATE_t receiverState;
    UART_DATA_SIZE_t dataFrameSize;
    UART_PARITY_t parity;
    UART_STP_SIZE_t stopFrameSize;
    UART_CLCK_POLARITY_t clckPolarity;
} UART_CNF_t;
UART_STD_ERR_t UART_init ( UART_CNF_t* uartCnfg );
UART_STD_ERR_t UART_setInterruptState ( UART_INT_FLAG_t flagType );
UART_STD_ERR_t UART_clearInterruptState ( UART_INT_FLAG_t flagType );
UART_STD_ERR_t UART_getInterruptState ( UART_INT_FLAG_t flagType , INT_STATE_t* outputState );
UART_STD_ERR_t UART_clearInterruptFlag ( UART_INT_FLAG_t flagType );
UART_STD_ERR_t UART_getInterruptFlag ( UART_INT_FLAG_t flagType , FLAG_STATE_t* outputFlagState );
UART_STD_ERR_t UART_getErrorFlag ( UART_ERR_FLAG_t errorFlagType , FLAG_STATE_t* outputFlagState );
UART_STD_ERR_t UART_setUbbr ( uint16_t ubbrValue );
UART_STD_ERR_t UART_setTransmissionMode ( UART_TRANS_MODE_t transmissionMode );
UART_STD_ERR_t UART_setTransmissionSpeedMode ( UART_TRANS_SPEED_t transmissionSpeedMode );
UART_STD_ERR_t UART_setClckPolarity ( UART_CLCK_POLARITY_t clckPolarity );
UART_STD_ERR_t UART_setDataFrameSize ( UART_DATA_SIZE_t dataFrameSize );
UART_STD_ERR_t UART_setParitySize ( UART_PARITY_t parity );
UART_STD_ERR_t UART_setStopSize ( UART_STP_SIZE_t stopFrameSize );
UART_STD_ERR_t UART_setProcessorMode ( UART_PROCESS_MODE_t multiProcessorMode );
void UART_transmit ( uint16_t data );
uint16_t UART_receive ( void );
void UART_flush ( void );
void UART_transmitByteArray ( uint8_t* arr , uint32_t size );
void UART_transmitChar ( char charToTransmit );
void UART_transmitString ( char* stringToTransmit );
#endif
