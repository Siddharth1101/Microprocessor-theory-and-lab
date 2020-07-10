/********************************************************************

Keypad library for five way navigation and two soft key.

Features:
	Automatic 80 FPS scanning using TIMER0
	3 point major polling for complete noice free operation
	Fully debounced.
	Automatic buffering of commands (no missed keypress!)
	Automatic repeat when user presses and hold a key.  

Written By:
	Avinash Gupta


Copyright 2008-2012
eXtreme Electronics, India
www.eXtremeElectronics.co.in
********************************************************************/

#include <avr/io.h>
#include <avr/interrupt.h>

#include "keypad.h"

uint8_t KeyBuffer[7][3];	//Raw key samples
uint8_t KeyState[7];
uint8_t KeyPrevState[7];

//Repeat counters
uint8_t KeyRepeatWait[7];
uint8_t KeyRepeatRate[7];

#define KEY_REPEAT_WAIT 128;
#define KEY_REPEAT_RATE 32;

volatile uint8_t key;

//Queue
volatile uint8_t KeypadCmdQ[KEYPAD_QMAX];	//Final Command Received (Buffer)
volatile int8_t KeypadQFront=-1,KeypadQEnd=-1;

void KeypadInit()
{
	//Init Key States
	uint8_t i;
	for(i=0;i<7;i++)
	{
		KeyPrevState[i]=RELEASED;
		KeyState[i]=RELEASED;

		//Repeat
		KeyRepeatWait[i]=KEY_REPEAT_WAIT;
		KeyRepeatRate[i]=KEY_REPEAT_RATE;
	}

	//First make all i/o pins input
	MICRO_KEY_DDR&=(~(1<<MICRO_KEY_POS));			//MICRO KEY
	GRILL_KEY_DDR&=(~(1<<GRILL_KEY_POS));			//GRILL KEY
	TM_KEY_DDR&=(~(1<<TM_KEY_POS));					//TEN MINUTE KEY
	M_KEY_DDR&=(~(1<<M_KEY_POS));					//MINUTE KEY
	TS_KEY_DDR&=(~(1<<TS_KEY_POS));					//TEN SEC KEY
	STOP_KEY_DDR&=(~(1<<STOP_KEY_POS));				//STOP KEY
	START_KEY_DDR&=(~(1<<START_KEY_POS));			//START KEY


	//Now enable internal pullups
	MICRO_KEY_PORT|=(1<<MICRO_KEY_POS);			
	GRILL_KEY_PORT|=(1<<GRILL_KEY_POS);		
	TM_KEY_PORT|=(1<<TM_KEY_POS);		
	M_KEY_PORT|=(1<<M_KEY_POS);		
	TS_KEY_PORT|=(1<<TS_KEY_POS);		
	STOP_KEY_PORT|=(1<<STOP_KEY_POS);
	START_KEY_PORT|=(1<<START_KEY_POS);


	//Init TIMER0 for keypad scanner (Approx 488 fps)
	TCCR0=(1<<CS01);	//Prescaller 8
	TIMSK|=(1<<TOIE0);			//Enable overflow interrupt

	sei();//Enable interrpts
}

ISR(TIMER0_OVF_vect)
{
	static uint8_t n=0;

	for(uint8_t i=0;i<7;i++)
	{
		KeyBuffer[i][n]=GetRawKeyState(i);
	}

	n++;
	if(n==3)
	{
		n=0;
		for(uint8_t i=0;i<7;i++)
		{
			KeyPrevState[i]=KeyState[i];
			KeyState[i]=MajorVote(i);

			if(KeyState[i]==PRESSED)
			{
				if(KeyPrevState[i]==RELEASED)
				{
					//Now We Have Got a keypress
					//Add it to Queue
				
					//Step1:Check of Q full
					if((KeypadQEnd==(KEYPAD_QMAX-1) && KeypadQFront==0)||((KeypadQEnd+1)==KeypadQFront))
					{
						KeypadQFront++;
						if(KeypadQFront==(KEYPAD_QMAX)) 
							KeypadQFront=0;
					}

					if(KeypadQEnd==(KEYPAD_QMAX-1))
						KeypadQEnd=0;
					else
						KeypadQEnd++;

					KeypadCmdQ[KeypadQEnd]=i;
					if(KeypadQFront==-1) KeypadQFront=0;
				}
				else
				{
					if(KeyRepeatWait[i]!=0) KeyRepeatWait[i]--;
					else
					{
						KeyRepeatRate[i]--;
						if(KeyRepeatRate[i]==0)
						{
							KeyRepeatRate[i]=KEY_REPEAT_RATE;

							//Now We Have Got a keypress
							//Add it to Queue
				
							//Step1:Check of Q full
							if((KeypadQEnd==(KEYPAD_QMAX-1) && KeypadQFront==0)||((KeypadQEnd+1)==KeypadQFront))
							{
								KeypadQFront++;
								if(KeypadQFront==(KEYPAD_QMAX)) 
									KeypadQFront=0;
							}

							if(KeypadQEnd==(KEYPAD_QMAX-1))
								KeypadQEnd=0;
							else
								KeypadQEnd++;

							KeypadCmdQ[KeypadQEnd]=i;
							if(KeypadQFront==-1) KeypadQFront=0;

							
						}
					}


				}
			}
			else
			{
				KeyRepeatWait[i]=KEY_REPEAT_WAIT;
			}
		}
	}

}

uint8_t GetRawKeyState(uint8_t KeyCode)
{
	if(KeyCode==KEY_MICRO)
	{
		return ((MICRO_KEY_PIN & (1<<MICRO_KEY_POS)));
	}

	if(KeyCode==KEY_GRILL)
	{
		return ((GRILL_KEY_PIN & (1<<GRILL_KEY_POS)));
	}

	if(KeyCode==KEY_TM)
	{
		return (TM_KEY_PIN & (1<<TM_KEY_POS));
	}

	if(KeyCode==KEY_M)
	{
		return ((M_KEY_PIN & (1<<M_KEY_POS)));
	}

	if(KeyCode==KEY_TS)
	{
		return ((TS_KEY_PIN & (1<<TS_KEY_POS)));
	}

	if(KeyCode==KEY_STOP)
	{
		return ((STOP_KEY_PIN & (1<<STOP_KEY_POS)));
	}	
	
	if(KeyCode==KEY_START)
	{
		return ((START_KEY_PIN & (1<<START_KEY_POS)));
	}

	return RELEASED;
}

uint8_t MajorVote(uint8_t keycode)
{
	if(KeyBuffer[keycode][0]==PRESSED)
	{
		if(KeyBuffer[keycode][1]==PRESSED)
		{
			return PRESSED;
		}
		else
		{
			if(KeyBuffer[keycode][2]==PRESSED)
				return PRESSED;
			else
				return RELEASED;
		}
	}
	else
	{
		if(KeyBuffer[keycode][1]==RELEASED)
		{
			return RELEASED;
		}
		else
		{
			if(KeyBuffer[keycode][2]==PRESSED)
				return PRESSED;
			else
				return RELEASED;
		}
	}
}

uint8_t GetKeypadCmd(char wait)
{
	unsigned char cmd;

	if(wait)
		while(KeypadQFront==-1);
	else
		if(KeypadQFront==-1) return (KEY_NONE);

	cmd=KeypadCmdQ[KeypadQFront];

	if(KeypadQFront==KeypadQEnd) 
		KeypadQFront=KeypadQEnd=-1;
	else
	{
		if(KeypadQFront==(KEYPAD_QMAX-1))
			KeypadQFront=0;
		else
			KeypadQFront++;
	}

	return cmd;
}
	


