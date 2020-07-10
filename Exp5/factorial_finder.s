	AREA Program, CODE,READONLY
	
	MOV R0,#1
	MOV R1,#3
	MOV R3,#1

	BL keepmul 	
	B finish 

keepmul

	MUL R4,R3,R0
	MOV R3,R4
	ADD R0,R0,#1
	CMP R0,R1
	BLE keepmul
	MOV PC,LR

finish B finish

	END
	