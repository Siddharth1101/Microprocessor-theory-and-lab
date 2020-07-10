		AREA Program,CODE,READONLY
	
		LDR R0,Value;load the value
	
		MOV R1,#0;initialise the parity result
	
next
		MOVS R0, R0,LSR #1
		MVNCS R1,R1;NOT IF  
		BNE next
		AND R1,R1,1
stop 	B stop	
Value 	DCD &00CB0071
		END