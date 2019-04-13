#ifndef AMIT_PROJECT_BIT_HELPERS_H_
#define AMIT_PROJECT_BIT_HELPERS_H_
#define SET_ZERO( x ) ( ( x ) ^= ( x ) )
#define BIT_MASK( x ) ( 1ULL << ( x ) )
#define RIGHT_SHIFT( x , y ) ( ( x ) >> ( y ) )
#define LEFT_SHIFT( x , y ) ( ( x ) << ( y ) )
#define READ_BIT( Byte , BitNum ) ( RIGHT_SHIFT ( Byte , BitNum ) & 0x01 )
#define READ_BITS( Byte , Mask ) ( ( Byte ) & ( Mask ) )
#define READ_BITS_AND_SHIFT( Byte , Mask , Shift ) ( READ_BITS ( Byte , Mask ) >> ( Shift ) )
#define SET_BIT( Byte , BitNum ) ( ( Byte ) |= BIT_MASK ( BitNum ) )
#define SET_BITS( Byte , Mask ) ( ( Byte ) |= ( Mask ) )
#define CLEAR_BIT( Byte , BitNum ) ( ( Byte ) &= ~ BIT_MASK ( BitNum ) )
#define CLEAR_BITS( Byte , Mask ) ( ( Byte ) &= ~ ( Mask ) )
#define TOGGLE_BIT( Byte , BitNum ) ( ( Byte ) ^= BIT_MASK ( BitNum ) )
#define TOGGLE_BITS( Byte , Mask ) ( ( Byte ) ^= ( Mask ) )
#define REPLACE_BIT( Byte , BitNum , BitState ) ( ( Byte ) &= ( ~ BIT_MASK ( BitNum ) ) | ( ( ! ( ! ( BitState ) ) ) << ( BitNum ) ) )
#define REPLACE_BITS( Byte , NewValue , Mask ) ( ( Byte ) = ( ( ( Byte ) & ~ ( Mask ) ) | ( ( NewValue ) & ( Mask ) ) ) )
#endif
