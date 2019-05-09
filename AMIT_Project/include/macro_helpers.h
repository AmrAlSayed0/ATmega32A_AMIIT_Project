#ifndef AMIT_PROJECT_MACRO_HELPERS_H_
#define AMIT_PROJECT_MACRO_HELPERS_H_
#define MIN( x , y ) ( ( x ) < ( y ) ? ( x ) : ( y ) )
#define MAX( x , y ) ( ( x ) > ( y ) ? ( x ) : ( y ) )
#define CAST( Value , Type ) ( ( Type ) ( Value ) )
#define IS_POW_OF_2( x ) ( ( ( Byte ) & ( ( Byte ) - 0x01 ) ) == 0 )
#endif