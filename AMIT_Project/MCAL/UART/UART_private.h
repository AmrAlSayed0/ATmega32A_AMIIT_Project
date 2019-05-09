#ifndef AMIT_PROJECT_UART_PRIVATE_H_
#define AMIT_PROJECT_UART_PRIVATE_H_
#define UBBR_CALC( BAUD_RATE , FACTOR )         ( ( ( ( double ) ( F_CPU ) ) / ( ( ( double ) ( FACTOR ) ) * ( ( double ) ( BAUD_RATE ) ) ) ) - ( ( double ) 1 ) )
#define BAUD_RATE_CALC( UBBR , FACTOR )         ( ( ( double ) ( F_CPU ) ) / ( ( ( double ) ( FACTOR ) ) * ( ( ( double ) ( UBBR ) ) + ( ( double ) 1 ) ) ) )
static UART_STD_ERR_t UART_ubbrCalc ( uint32_t baudRate , UART_TRANS_MODE_t transmissionMode , UART_TRANS_SPEED_t transmissionSpeed , uint16_t* ubbrValue );
#endif