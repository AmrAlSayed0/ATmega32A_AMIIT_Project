#ifndef AMIT_PROJECT_BIT_HELPERS_H_
#define AMIT_PROJECT_BIT_HELPERS_H_
#define SET_ZERO( x ) ( ( x ) ^= ( x ) )
#define BIT_MASK( x ) ( 1ULL << ( x ) )
#define RIGHT_SHIFT( x , y ) ( ( x ) >> ( y ) )
#define LEFT_SHIFT( x , y ) ( ( x ) << ( y ) )
#define READ_BIT( Byte , BitNum ) ( RIGHT_SHIFT ( Byte , BitNum ) & 0x01 )
#define READ_BITS( Byte , Mask ) ( ( Byte ) & ( Mask ) )
#define READ_BITS_AND_SHIFT( Byte , Mask , Shift ) ( RIGHT_SHIFT ( READ_BITS ( Byte , Mask ) , Shift ) )
#define SET_BIT( Byte , BitNum ) ( ( Byte ) |= BIT_MASK ( BitNum ) )
#define SET_BITS( Byte , Mask ) ( ( Byte ) |= ( Mask ) )
#define CLEAR_BIT( Byte , BitNum ) ( ( Byte ) &= ~ BIT_MASK ( BitNum ) )
#define CLEAR_BITS( Byte , Mask ) ( ( Byte ) &= ~ ( Mask ) )
#define TOGGLE_BIT( Byte , BitNum ) ( ( Byte ) ^= BIT_MASK ( BitNum ) )
#define TOGGLE_BITS( Byte , Mask ) ( ( Byte ) ^= ( Mask ) )
#define REPLACE_BIT( Byte , BitNum , BitState ) ( ( Byte ) &= ( ~ BIT_MASK ( BitNum ) ) | ( ( ! ( ! ( BitState ) ) ) << ( BitNum ) ) )
#define REPLACE_BITS( Byte , NewValue , Mask ) ( ( Byte ) = ( ( ( Byte ) & ~ ( Mask ) ) | ( ( NewValue ) & ( Mask ) ) ) )
#define BIT_MASK1( Bit0 ) BIT_MASK ( Bit0 )
#define BIT_MASK2( Bit0 , Bit1 ) ( BIT_MASK1 ( Bit0 ) | BIT_MASK1 ( Bit1 ) )
#define BIT_MASK3( Bit0 , Bit1 , Bit2 ) ( BIT_MASK2 ( Bit0 , Bit1 ) | BIT_MASK1 ( Bit2 ) )
#define BIT_MASK4( Bit0 , Bit1 , Bit2 , Bit3 ) ( BIT_MASK2 ( Bit0 , Bit1 ) | BIT_MASK2 ( Bit2 , Bit3 ) )
#define BIT_MASK5( Bit0 , Bit1 , Bit2 , Bit3 , Bit4 ) ( BIT_MASK4 ( Bit0 , Bit1 , Bit2 , Bit3 ) | BIT_MASK1 ( Bit4 ) )
#define BIT_MASK6( Bit0 , Bit1 , Bit2 , Bit3 , Bit4 , Bit5 ) ( BIT_MASK4 ( Bit0 , Bit1 , Bit2 , Bit3 ) | BIT_MASK2 ( Bit4 , Bit5 ) )
#define BIT_MASK7( Bit0 , Bit1 , Bit2 , Bit3 , Bit4 , Bit5 , Bit6 ) ( BIT_MASK4 ( Bit0 , Bit1 , Bit2 , Bit3 ) | BIT_MASK3 ( Bit4 , Bit5 , Bit6 ) )
#define BIT_MASK8( Bit0 , Bit2 , Bit3 , Bit4 , Bit5 , Bit6 , Bit7 , Bit8 ) ( BIT_MASK4 ( Bit0 , Bit2 , Bit3 , Bit4 ) | BIT_MASK4 ( Bit0 , Bit2 , Bit3 , Bit4 ) )
// 01011000 --> 01010000
#define CLEAR_LEAST_SIG_ONE( Byte ) ( ( Byte ) &= ( ( Byte ) - 0x01 ) )
// 10100111 --> 10101111
#define SET_LEAST_SIG_ZERO( Byte ) ( ( Byte ) |= ( ( Byte ) + 0x01 ) )
// 01011000 --> 00001000
#define ISOLATE_LEAST_SIG_ONE( Byte ) ( ( Byte ) & ( - ( Byte ) ) )
// 10100111 --> 00001000
#define ISOLATE_LEAST_SIG_ZERO( Byte ) ( ~ ( Byte ) & ( ( Byte ) + 0x01 ) )
// Creates a bit mask of all the trailing zeros 01011000 --> 00000111
#define CREATE_TRAILING_ZEROS_MASK( Byte ) ( ( ~ ( Byte ) ) & ( ( Byte ) - 0x01 ) )
// 01011000 --> 01011111
#define RIGHT_PROPAGATE_LEAST_SIG_ONE( Byte ) ( ( Byte ) == 0 ? 0 : ( ( Byte ) | ( ( Byte ) - 0x1 ) ) )
#define CLEAR_LEAST_SIG_ONES_SEQ( Byte ) ( ( ( ( Byte ) | ( ( Byte ) - 0x01 ) ) + 0x01 ) & ( Byte ) )
#endif
