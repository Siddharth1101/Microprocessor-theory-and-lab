/*
 * _4bit_mult.asm
 *
 *  Created: 8/27/2019 3:23:55 PM
 *   Author: students
 */ 

;#include "m8def.inc"

LDI R16,0xFF
OUT DDRB,R16;SET B AS OUTPUT
LDI R16,0x00
OUT DDRD,R16;D AS INPUT

IN R1,PIND;
MOV R0,R1;

LDI R16,0x0F
AND R0,R16;multiplier (ACCUMULATOR) in R0
LDI R16,0xF0
AND R16,R1;MASKING THE FIRST 4 to get multiplicand IN R16


LDI R17, 0X04;COUNTER
LDI R18,0X01


next:
MOV R19,R18
AND R19,R0
CPI R19,0x00
CLC;CLEARS THE CARRY TO INSERT 0 AT ROR
BREQ skip
ADD R0,R16
skip:
ROR R0

DEC R17
BRNE next;COMPLETION IF ZERO REACHED

;ROL R0


OUT PORTB,R0


 


