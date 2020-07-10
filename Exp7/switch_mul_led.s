/* ARM C program to read DIP switch and display its value on LEDs*/
#include "LPC23xx.h"
int main ()
{
int a,b,c,d;
FIO3DIR=0xFF; // LEDs are connected to lower 8 bits of
// Fast IO port 3 (FIO3PIN). Hence set the lower 8 bits
// as output in the corresponding direction
// register (FIO3DIR)
FIO4DIR=0x00; // Similarly switches are connected to the lower 8 bits of
// of Fast IO Port 4 (FIO4PIN). Hence set it as input inthe
// direction register (FIO4DIR)
while(1)
	{

		a=FIO4PIN; // read switch value from the IO port into variable
		b = a&0x0000000F;
		c=(a&0x000000F0)/(0x10);
		d = b*c;
		
		FIO3PIN=d; // send the variable value to IO port of leds
	}
	
return 0;

}