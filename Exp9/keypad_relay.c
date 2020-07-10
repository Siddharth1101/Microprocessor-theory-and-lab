#include "LPC23xx.h"

void delay(void)
{
	int i,j;
	for(i=0;i<0xff;i++)
		for( j=0;j<0xff;j++);
}

void key_routine(void)
{
	unsigned int key;
	FIO3DIR = 0x050000FF;
	while(1)
	{
		//First Row
		FIO4SET = 0X00000e00;
		key = FIO4PIN;
		key = (key & 0xf000) >> 12 ;
		if(key!=0x0F)
		{
			FIO3SET =0X050000FF; // Set the relay and LED pins to logic 1
			delay();
			FIO3CLR =0x050000FF; // Clear the relay and LED pins (by assigning 1)
			FIO4CLR = 0X00000e00;
			delay();
		}
	}
}
int main ()
{
	unsigned int Fdiv;
	FIO4DIR = 0XFF000fff;
	FIO3DIR = 0x050000FF;
	PINSEL0 = 0x00000050;
	key_routine();
	return(0);
}