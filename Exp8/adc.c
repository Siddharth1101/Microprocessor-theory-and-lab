#include "LPC23xx.h"
void TargetResetInit(void)
{
// 72 Mhz Frequency
if ((PLLSTAT & 0x02000000) > 0)
{
/* If the PLL is already running */
PLLCON &= ~0x02; /* Disconnect the PLL */
PLLFEED = 0xAA; /* PLL register update sequence, 0xAA, 0x55 */
PLLFEED = 0x55;
}
PLLCON &= ~0x01; /* Disable the PLL */
PLLFEED = 0xAA; /* PLL register update sequence, 0xAA, 0x55 */
PLLFEED = 0x55;
SCS &= ~0x10; /* OSCRANGE = 0, Main OSC is between 1 and 20 Mhz */
SCS |= 0x20; /* OSCEN = 1, Enable the main oscillator */
while ((SCS & 0x40) == 0);
CLKSRCSEL = 0x01; /* Select main OSC, 12MHz, as the PLL clock source */
PLLCFG = (24 << 0) | (1 << 16); /* Configure the PLL multiplier and divider */
PLLFEED = 0xAA; /* PLL register update sequence, 0xAA, 0x55 */
PLLFEED = 0x55;
PLLCON |= 0x01; /* Enable the PLL */
PLLFEED = 0xAA; /* PLL register update sequence, 0xAA, 0x55 */
PLLFEED = 0x55;
CCLKCFG = 3; /* Configure the ARM Core Processor clock divider */
USBCLKCFG = 5; /* Configure the USB clock divider */
while ((PLLSTAT & 0x04000000) == 0);
PCLKSEL0 = 0xAAAAAAAA; /* Set peripheral clocks to be half of main clock */
PCLKSEL1 = 0x22AAA8AA;
PLLCON |= 0x02; /* Connect the PLL. The PLL is now the active clock source */
PLLFEED = 0xAA; /* PLL register update sequence, 0xAA, 0x55 */
PLLFEED = 0x55;
while ((PLLSTAT & 0x02000000) == 0);
PCLKSEL0 = 0x55555555; /* PCLK is the same as CCLK */
PCLKSEL1 = 0x55555555;
}
/********************* serial Transmission routine***********************************/
void serial_tx(int ch)
{
while ((U0LSR & 0x20)!=0x20);
U0THR = ch;
}
/**************************** Routine for converting hex value to ascii value *****************/
int atoh(int ch)
{
if(ch<=0x09)
ch = ch + 0x30;
else
ch = ch + 0x37;
return(ch);
}
/*********************************** main routine
****************************************************/
int main ()
{
unsigned int Fdiv,value,i,j;
// char value;
TargetResetInit();
// init_timer( ((72000000/100) - 1) );
PCONP |=0X00001000; //switch adc from disable state to enable state
PINSEL0 = 0x00000050; //Pinselection for uart tx and rx lines
PINSEL1 = 0X01554000; //Pinselection for adc0.0
/************** Uart initialization **********************************/
U0LCR = 0x83; // 8 bits, no Parity, 1 Stop bit
Fdiv = ( 72000000 / 16 ) / 19200 ; //baud rate
//Fdiv = ( 72000000 / 16 ) / 2400 ; //baud rate
U0DLM = Fdiv / 256;
U0DLL = Fdiv % 256;
U0LCR = 0x03; // DLAB = 0
AD0CR = 0X01210F01; // Adc initialization
while(1)
{
while((AD0DR0 & 0X80000000)!=0X80000000){}; // Wait here until adc make conversion complete
/************* To get converted value and display it on the serial port****************/
value = (AD0DR0>>6)& 0x3ff ; //ADC value
//serial_tx(value);
serial_tx('\t');
serial_tx(atoh((value&0x300)>>8));
serial_tx(atoh((value&0xf0)>>4));
serial_tx(atoh(value&0x0f));
serial_tx(0x0d);
serial_tx(0x0a);
for(i=0;i<=0xFF;i++)
{
for(j=0;j<=0xFF;j++);
}
}
return 0;
}
