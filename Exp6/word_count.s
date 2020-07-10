
		AREA Program, CODE, READONLY
		ENTRY
Main
		LDR R0, Message;
		EOR R1, R1, R1;
		
findSta
		LDR R3, [R0], #4;
		SUBS R3, R3, #2;
		BNE findSta;
findEnd
		LDR R3, [R0], #4;
		ADD R1, #1;
		SUBS R3, R3, #3;
		BNE findEnd;
Done
		SUB R1, #1;
		STR R1, length;
Stop
		B Stop;

LIST	
		DCD	&5C;
		DCD	&02;
		DCD &2D;
		DCD &04;
		DCD &05;
		DCD &03;
		ALIGN
			
Message	 DCD LIST;
	
length	DCW 0;
		ALIGN
	
		END;