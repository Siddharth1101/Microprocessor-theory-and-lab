		AREA Program,CODE,READONLY
	
		MOV R3,#0;no of times pattern occurs
		LDR R0,=Values;take the first 32bit no, and check
		LDR R5,[R0],#4
		MOV R6,#8;outer counter
next	LDR R1,[R0],#4;keep the next one ready
		MOV R2,#31;counter
repeat	AND R4,R5,#0xFF000000
		CMP R4,#0x7E000000
		ADDEQ R3,#1
		
		MOV R1,R1,LSL #1
		MOV R5,R5,LSL #1
		ADC R5,R5,#0
		
		SUBS R2,R2,#1
		BNE repeat
		SUBS R6,R6,#1
		BNE next
STOP 	B STOP		
Values DCD &E0000007,&E0000007,&E0000007,&E0000007,&E0000007,&E0000007,&E0000007,&00000007
		END