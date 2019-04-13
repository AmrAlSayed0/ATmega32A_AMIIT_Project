#ifndef AMIT_PROJECT_UART_H_
#define AMIT_PROJECT_UART_H_
#include "Std_Types.h"
#include "common.h"
typedef enum _UART_TRANS_SPEED_t
{
    NORMAL_SPEED ,
    DOUBLE_SPEED ,
    NC_SPEED
} UART_TRANS_SPEED_t;
typedef enum _UART_PROCESS_MODE_t
{
    SINGLE ,
    MULTI
} UART_PROCESS_MODE_t;
typedef enum _UART_TRANS_MODE_t
{
    ASYNC ,
    SYNC
} UART_TRANS_MODE_t;
typedef enum _UART_INT_FLAG_t
{
    UART_FLAG_REC_COMP ,
    UART_FLAG_TRANS_COMP ,
    UART_FLAG_EMPTY
} UART_INT_FLAG_t;
typedef enum _UART_ERR_FLAG_t
{
    UART_ERR_FLAG_FRAME ,
    UART_ERR_FLAG_OVERRUN ,
    UART_ERR_FLAG_PARITY
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
    COM_ENABLED ,
    COM_DISABLED ,
} COM_STATE_t;
typedef enum _UART_DATA_SIZE_t
{
    BIT_5_SIZE ,
    BIT_6_SIZE ,
    BIT_7_SIZE ,
    BIT_8_SIZE ,
    BIT_9_SIZE ,
} UART_DATA_SIZE_t;
typedef enum _UART_PARITY_t
{
    NO_PARITY ,
    EVEN_PARITY ,
    ODD_PARITY
} UART_PARITY_t;
typedef enum _UART_STP_SIZE_t
{
    BIT_1_SIZE ,
    BIT_2_SIZE ,
} UART_STP_SIZE_t;
typedef enum _UART_CLCK_POLARITY_t
{
    RISING_FALLING ,
    FALLING_RISING ,
    NC_POLARITY
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
UART_STD_ERR_t UART_setTransmissionMode ( UART_TRANS_MODE_t transmissionMode );
UART_STD_ERR_t UART_setUbbr ( uint16_t ubbrValue );
void UART_transmit ( uint16_t data );
uint16_t UART_receive ( void );
void UART_flush ( void );
void UART_transmitChar ( char charToTransmit );
void UART_transmitString ( char* stringToTransmit );
#endif
