#ifndef AMIT_PROJECT_IO_EXTRAS_H_
#define AMIT_PROJECT_IO_EXTRAS_H_
#include <avr/io.h>
#ifndef REG_R0
    #define REG_R0  _SFR_MEM8(0x00)
#endif
#ifndef REG_R1
    #define REG_R1  _SFR_MEM8(0x01)
#endif
#ifndef REG_R2
    #define REG_R2  _SFR_MEM8(0x02)
#endif
#ifndef REG_R3
    #define REG_R3  _SFR_MEM8(0x03)
#endif
#ifndef REG_R4
    #define REG_R4  _SFR_MEM8(0x04)
#endif
#ifndef REG_R5
    #define REG_R5  _SFR_MEM8(0x05)
#endif
#ifndef REG_R6
    #define REG_R6  _SFR_MEM8(0x06)
#endif
#ifndef REG_R7
    #define REG_R7  _SFR_MEM8(0x07)
#endif
#ifndef REG_R8
    #define REG_R8  _SFR_MEM8(0x08)
#endif
#ifndef REG_R9
    #define REG_R9  _SFR_MEM8(0x09)
#endif
#ifndef REG_R10
    #define REG_R10 _SFR_MEM8(0x0A)
#endif
#ifndef REG_R11
    #define REG_R11 _SFR_MEM8(0x0B)
#endif
#ifndef REG_R12
    #define REG_R12 _SFR_MEM8(0x0C)
#endif
#ifndef REG_R13
    #define REG_R13 _SFR_MEM8(0x0D)
#endif
#ifndef REG_R14
    #define REG_R14 _SFR_MEM8(0x0E)
#endif
#ifndef REG_R15
    #define REG_R15 _SFR_MEM8(0x0F)
#endif
#ifndef REG_R16
    #define REG_R16 _SFR_MEM8(0x10)
#endif
#ifndef REG_R17
    #define REG_R17 _SFR_MEM8(0x11)
#endif
#ifndef REG_R18
    #define REG_R18 _SFR_MEM8(0x12)
#endif
#ifndef REG_R19
    #define REG_R19 _SFR_MEM8(0x13)
#endif
#ifndef REG_R20
    #define REG_R20 _SFR_MEM8(0x14)
#endif
#ifndef REG_R21
    #define REG_R21 _SFR_MEM8(0x15)
#endif
#ifndef REG_R22
    #define REG_R22 _SFR_MEM8(0x16)
#endif
#ifndef REG_R23
    #define REG_R23 _SFR_MEM8(0x17)
#endif
#ifndef REG_R24
    #define REG_R24 _SFR_MEM8(0x18)
#endif
#ifndef REG_R25
    #define REG_R25 _SFR_MEM8(0x19)
#endif
#ifndef REG_R26
    #define REG_R26 _SFR_MEM8(0x1A)
#endif
#ifndef REG_R27
    #define REG_R27 _SFR_MEM8(0x1B)
#endif
#ifndef REG_R28
    #define REG_R28 _SFR_MEM8(0x1C)
#endif
#ifndef REG_R29
    #define REG_R29 _SFR_MEM8(0x1D)
#endif
#ifndef REG_R30
    #define REG_R30 _SFR_MEM8(0x1E)
#endif
#ifndef REG_R31
    #define REG_R31 _SFR_MEM8(0x1F)
#endif
#ifndef REG_X
    #define REG_X   _SFR_MEM16(0x1A)
#endif
#ifndef REG_XL
    #define REG_XL  _SFR_MEM8(0x1A)
#endif
#ifndef REG_XH
    #define REG_XH  _SFR_MEM8(0x1B)
#endif
#ifndef REG_Y
    #define REG_Y   _SFR_MEM16(0x1C)
#endif
#ifndef REG_YL
    #define REG_YL  _SFR_MEM8(0x1C)
#endif
#ifndef REG_YH
    #define REG_YH  _SFR_MEM8(0x1D)
#endif
#ifndef REG_Z
    #define REG_Z   _SFR_MEM16(0x1E)
#endif
#ifndef REG_ZL
    #define REG_ZL  _SFR_MEM8(0x1E)
#endif
#ifndef REG_ZH
    #define REG_ZH  _SFR_MEM8(0x1F)
#endif
#ifndef SP
    #define SP		_SFR_IO16(0x3D)
#endif
#ifndef SPH
    #define SPH		_SFR_IO8(0x3D)
#endif
#ifndef SPL
    #define SPL		_SFR_IO8(0x3E)
#endif
#ifndef SPH
    #define SREG	_SFR_IO8(0x3F)
#endif
#ifndef SREG_C
    #define SREG_C  0
#endif
#ifndef SREG_Z
    #define SREG_Z  1
#endif
#ifndef SREG_N
    #define SREG_N  2
#endif
#ifndef SREG_V
    #define SREG_V  3
#endif
#ifndef SREG_S
    #define SREG_S  4
#endif
#ifndef SREG_H
    #define SREG_H  5
#endif
#ifndef SREG_T
    #define SREG_T  6
#endif
#ifndef SREG_I
    #define SREG_I  7
#endif
#endif