 lds r16, 0x60
 lds r17, 0x61
 mov r18, r17
 add r17,r16
 ldi r20, 0x00
 brsh check_carry
 inc r20
 check_carry : 
 sts 0x62, r17
 sts 0x63, r20
 

 clc
 ldi r20,0x00
 sub r18,r16
 brpl pos
 com r20
 neg r18
 pos:
 sts 0x64, r18
 sts 0x65, r20
 nop
  