/*
 * ledblink_10times.asm
 *
 *  Created: 9/3/2019 3:21:38 PM
 *   Author: students
 */ 
 #include "m8def.inc"
; Replace with your application code
.org 0
rjmp reset

.org INT0addr; CHANGE THIS IF USING INT 1
rjmp int1_ISR

.org 0x0100

reset:
      LDI R16,0x70
	  OUT SPL,R16
	  LDI R16,0x00
	  OUT SPH,R16

	  LDI R16,0x01
	  OUT DDRB,R16

	  LDI R16,0x00
	  OUT DDRD,R16

	  IN R16,MCUCR;Load MCUCR register 
	  ORI R16,(1<<ISC00|1<<ISC01);CHANGE TO 10 AND 11 IF USING INT1
	  OUT MCUCR,R16

	  IN R16,GICR; Load GICR register 
	  ORI R16,(1<<INT0);CHANGE IF USING INT1
	  OUT GICR,R16

	  LDI R16,0x00
	  OUT PORTB,R16

	  SEI
ind_loop:rjmp ind_loop

int1_ISR:IN R16,SREG
		 PUSH R16

		 LDI R16,0X0A;to blink 10 times
		 MOV R0,R16

	c1:	 LDI R16,0x01
		 OUT PORTB,R16;set led to HIGH

		 LDI R16,0xFF
	a1:	 LDI R17,0xFF
	a2:	 DEC R17
		 BRNE a2
		 DEC R16
		 BRNE a1
		 
		 LDI R16,0x00
		 OUT PORTB,R16;set led to LOW

		 LDI R16,0xFF
	b1:	 LDI R17,0xFF
	b2:	 DEC R17
		 BRNE b2
		 DEC R16
		 BRNE b1

		 DEC R0
		 BRNE c1;go on to next blink
		 POP R16
		 OUT SREG,R16
		 
		 RETI 
