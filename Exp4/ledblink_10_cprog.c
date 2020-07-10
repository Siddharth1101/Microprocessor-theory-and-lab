/*
 * ledblink_10_cprog.c
 *
 * Created: 9/3/2019 3:34:25 PM
 *  Author: students
 */ 

#define F_CPU 1000000
#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>

ISR (INT1_vect)
{
	// Write your ISR here to blink the LED 10 times
	// with ON and OFF interval of 1 second each
	for(int i=0;i<10;i++)
	{PORTB=0x01;
	_delay_ms(1000);
	PORTB=0x00;
	_delay_ms(1000);
	}
}
int main(void)
{
	DDRD = 0x00 ;
	DDRB = 0x01;
	MCUCR = 0x08;
	GICR = 0x80;
	PORTB =0x00  ;
	
	sei();
	

	while (1)
	{
	}
}