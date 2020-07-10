LDI ZL, LOW(NUM<<1)
LDI ZH,HIGH(NUM<<1)
LDI XL,0x60
LDI XH,0x00

LPM R16,Z+;MULTIPLICAND
MOV R17,R16
NEG R17;stores the complement of the multiplicand

;STORING IN THE ACCUMULATOR, 
LPM R0,Z;MULTIPLIER
LDI R1,0x00

LDI R3 0X04;COUNTER

next:
LDS R4,R0
AND R4,0X03;extract last two bits

;check for 01
CP R4, 0X01
BRNE chk2
ADD R1,R16
RJMP end

chk2:;check for 10
CP R4,0x02
BRNE end
ADD R1,R17;adding twos complement of multiplicand

end:;shift irrespective of anything after required processes
ASR R1;MAINTAIN SIGN AND SHIFT(C OUT)
ROR R0;TAKE IN C AND SHIFT TO GET NEXT BIT

DEC R3
BRNE next;COMPLETION IF ZERO REACHED

ROL R0;roll back extra shift at end
ROL R1

ST X+,R0
ST X,R1

NUM: .db 0x1E,0X1F