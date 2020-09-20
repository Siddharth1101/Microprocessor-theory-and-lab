#include <avr/io.h>
#include <avr/pgmspace.h>
#include <util/delay.h>
#include <avr/interrupt.h>

#include "C:\Users\students\Downloads\Microwave_oven\AS6_M8_Mircowave_Controller\source\MicrowaveController\MicrowaveController\lib\lcd\lcd_hd44780_avr.h"
#include "C:\Users\students\Downloads\Microwave_oven\AS6_M8_Mircowave_Controller\source\MicrowaveController\MicrowaveController\lib\keypad\keypad.h"
#define MICRO_DDR	DDRD
#define MICRO_PORT	PORTD
#define MICRO_POS	PD0

#define GRILL_DDR	DDRD
#define GRILL_PORT	PORTD
#define GRILL_POS	PD1

#define BUZZER_DDR	DDRB
#define BUZZER_PORT	PORTB
#define BUZZER_POS	PB1

#define ON	1
#define OFF 0

#define TYPE_MICRO	1
#define TYPE_GRILL	2

void Init();
void SetMicro(uint8_t state);
void SetGrill(uint8_t state);

void SetTime();
void CountDown();

void SetBuzzer(uint8_t);
void Beep();

volatile uint8_t m=0;
volatile uint8_t s=0;
volatile uint8_t timer_running=0;

uint8_t type=TYPE_MICRO;

int main(void)
{
	Init();
	
	while(1)
	{
		LCDClear();
		
		LCDWriteFStringXY(3,0,PSTR("* Press *"));
		LCDWriteFStringXY(1,1,PSTR("Micro or Grill"));
		
		uint8_t k=GetKeypadCmd(1);
		
		switch(k)
		{
			case KEY_MICRO:
			{
				Beep();
				type=TYPE_MICRO;
				SetTime();
				timer_running=1;
				
				if(type==TYPE_MICRO)
					SetMicro(ON);
				else
					SetGrill(ON);
				
				CountDown();
				
				break;
			}
			case KEY_GRILL:
			{
				Beep();
				type=TYPE_GRILL;
				SetTime();
				timer_running=1;
				
				if(type==TYPE_MICRO)
					SetMicro(ON);
				else
					SetGrill(ON);
				
				CountDown();
				break;
			}
			case KEY_START:
			{
				Beep();
				//QUICK START
				type=TYPE_MICRO;
				if(!timer_running)
				{
					s=30;
					timer_running=1;	
					SetMicro(ON);
					CountDown();
					break;
				}
				
			}
		}
		
	}
}
void Beep()
{
	SetBuzzer(ON);
	_delay_ms(25);
	SetBuzzer(OFF);
	_delay_ms(25);
}
void Init()
{
	//Set relay io lines as out put
	MICRO_DDR|=(1<<MICRO_POS);	//Microwave relay
	GRILL_DDR|=(1<<GRILL_POS);	//Grill relay
	
	//Set Buzzer line as output
	BUZZER_DDR|=(1<<BUZZER_POS);
	
	//Initialize LCD Module
	LCDInit(LS_NONE);
	
	//Initiallize keypad lib
	KeypadInit();
	
	//Init TIMER1 for main timer operation
	TCCR1B=(1<<WGM12)|(1<<CS12)|(1<<CS10); //CTC Mode prescaller 1024
	OCR1A=976;
	TIMSK|=(1<<OCIE1A);
}
ISR(TIMER1_COMPA_vect)
{
	if(!timer_running)
		return;
	
	if(s==0)
	{
		if(m==0)
		{
			//off
			timer_running=0;
		}
		else
		{
			m--;
			s=59;
		}
	}
	else
	{
		s--;
	}
	
}
void SetMicro(uint8_t state)
{
	if(state==ON)
	{
		MICRO_PORT|=(1<<MICRO_POS);
	}
	else
	{
		MICRO_PORT&=~(1<<MICRO_POS);
	}
}
void SetBuzzer(uint8_t state)
{
	if(state==ON)
	{
		BUZZER_PORT|=(1<<BUZZER_POS);
	}
	else
	{
		BUZZER_PORT&=~(1<<BUZZER_POS);
	}
}
void SetGrill(uint8_t state)
{
	if(state==ON)
	{
		GRILL_PORT|=(1<<GRILL_POS);
	}
	else
	{
		GRILL_PORT&=~(1<<GRILL_POS);
	}
}

void SetTime()
{
	uint8_t min=0;
	uint8_t sec=0;
	
	LCDClear();
	
	while(1)
	{
		if(type==TYPE_MICRO)
		{
			LCDWriteFStringXY(0,0,PSTR("MICRO"));
		}			
		else
		{
			LCDWriteFStringXY(0,0,PSTR("GRILL"));
		}			
			
		LCDWriteFStringXY(6,0,PSTR("MM:SS      "));
		
		LCDWriteIntXY(6,1,min,2);
		LCDWriteIntXY(9,1,sec,2);
		
		LCDWriteFStringXY(8,1,PSTR(":"));
		
		uint8_t key=GetKeypadCmd(1);
		
		switch(key)
		{
			case KEY_TS:
				if(min<90)
				{
					Beep();
					sec+=10;
					if(sec==60)
					{
						sec=0;
						min++;
						
						if(min==91)
						min=90;
					}
					
				}
				
				break;
			case KEY_M:
			{
				
				if(min<90)
				{
					min++;
					Beep();
				}					
				break;
			}
			
			case KEY_TM:
			{
				if(min<90)
				{
					min+=10;
					if(min>=90)
					{
						min=90;
						sec=0;
					}	
					else
						Beep();
				}
				
				break;
			}
			
			case KEY_STOP:
				Beep();
				min=0;
				sec=0;
			break;
			
			case KEY_GRILL:
				Beep();
				type=TYPE_GRILL;
				break;
			
			case KEY_MICRO:
				Beep();
				type=TYPE_MICRO;
				break;
			
			case KEY_START:
			{
				if(min>0 || sec>0)
				{
					Beep();
					m=min;
					s=sec;
					return;
					
				}
				
			}				
				
		}

		
	}
}

void CountDown()
{
	LCDClear();
	
	while(1)
	{
		uint8_t k=GetKeypadCmd(0);
		
		if(k==KEY_STOP)
		{
			//Pause
			timer_running=0;
			
			SetMicro(OFF);
			SetGrill(OFF);
			
			LCDWriteFStringXY(7,0,PSTR("PAUSED!"));
			LCDWriteFStringXY(6,1,PSTR("Press Start"));
			
			Beep();
			
			while(1)
			{
				k=GetKeypadCmd(1);
				
				if(k==KEY_START)
				{
					Beep();
					break;	
				}					
			}
			
			timer_running=1;
			
			if(type==TYPE_MICRO)
				SetMicro(ON);
			else
				SetGrill(ON);
				
			LCDClear();
		
		}
		else if(k==KEY_START)
		{
				if(m<=89)
				{
					if(s<30)
					{
						s+=30;
						if(s>=60)
						{
							m++;
							s=s-60;
							
						}
						Beep();
						
					}	
					
				}
		}
		
		if(m==0 && s==0)
		{
			LCDClear();
			LCDWriteFStringXY(0,5,PSTR("Ready !"));
			
			
			
			SetMicro(OFF);
			SetGrill(OFF);
			
			//Alert
			for(uint8_t i=0;i<4;i++)
			{
				SetBuzzer(ON);
				_delay_ms(500);
				SetBuzzer(OFF);
				_delay_ms(500);
			}
			
			GetKeypadCmd(1);
			
			Beep();
			
			return;
		}
		LCDWriteIntXY(0,1,m,2);
		if(s%2)
		{
			LCDWriteStringXY(2,1,":");
		}
		else
		{
			LCDWriteStringXY(2,1," ");
		}
		
		LCDWriteIntXY(3,1,s,2);
		
		if(type==TYPE_MICRO)
		{
			LCDWriteFStringXY(0,0,PSTR("MICRO"));
		}
		else
		{
			LCDWriteFStringXY(0,0,PSTR("GRILL"));
		}
	}
	
}
