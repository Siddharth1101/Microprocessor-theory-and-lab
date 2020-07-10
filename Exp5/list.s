	AREA Program,CODE,READONLY

	LDR R0,=list
	LDR R1,#0;the result register
	LDR R2,#12;SHIFT-LEVEL
	LDR R3,&000F; mask
	
repeat

	;load the value
	LDRB R4,[R0],#1
	
	AND R4,R4,R3;mask it
	
	;shift it accordingly
	MOV R4,R4,LSL R2
	SUB R2,R2,#4;change shift amount
	
	ADD R1,R4;add it to final answer
	
	TST R2
	BEQ repeat
	

list DCB &C2,&31,&G3,&F4
