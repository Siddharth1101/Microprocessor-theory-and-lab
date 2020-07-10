#include "LPC23xx.h"

void delay(void)
{
	int i,j;
	for(i=0;i<0xff;i++)
		for( j=0;j<0xff;j++);
}

int main ()
{	
	unsigned int key;
	FIO3DIR = 0x050000FF;
	FIO4DIR=0x00;
	while(1)
	{
		key = FIO4PIN;
		key = key&0xff;
		if(key==0x3C)//PATTERN 00111100
		{
			FIO3SET =0X050000FF; // Set the relay and LED pins to logic 1
			delay();
			FIO3CLR =0x050000FF; // Clear the relay and LED pins (by assigning 1)
			delay();
		}
	}
	return(0);
}