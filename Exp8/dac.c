#include "LPC23xx.h"

void dLAY(int n)
{
    int i,j;
    for(i=0;i<n;i++);
    for(j=0;j<0x0F;j++);
}

int main (void)
{
    PCLKSEL0=0x00C00000;
    PINMODE1=0x00300000;
    PINSEL1=0x00200000;
    int value;
    int i=0;
    int sin_wave[101]={0x200,0x220,0x240,0x25f,0x27f,
    0x29e,0x2bc,0x2d9,0x2f6,0x312,0x32c,0x346,0x35e,0x374,
    0x38a,0x39d,0x3af,0x3c0,0x3ce,0x3db,0x3e6,0x3ef,0x3f6,
    0x3fb,0x3fe,0x3ff,0x3fe,0x3fb,0x3f6,0x3ef,0x3e6,0x3db,
    0x3ce,0x3c0,0x3af,0x39d,0x38a,0x374,0x35e,0x346,0x32c,
    0x312,0x2f6,0x2d9,0x2bc,0x29e,0x27f,0x25f,0x240,0x220,
    0x200,0x1df,0x1bf,0x1a0,0x180,0x161,0x143,0x126,0x109,
    0xed,0xd3,0xb9,0xa1,0x8b,0x75,0x62,0x50,0x3f,0x31,0x24,
    0x19,0x10,0x9,0x4,0x1,0x0,0x1,0x4,0x9,0x10,0x19,0x24,
    0x31,0x3f,0x50,0x62,0x75,0x8b,0xa1,0xb9,0xd3,0xed,0x109,
    0x126,0x143,0x161,0x180,0x1a0,0x1bf,0x1df,0x200};

    while(1)
    {
            //Sine wave
        /*
        i=0;
        while(i<101)
        {
            value=sin_wave[i];
            DACR=(value<<6);
            dLAY(100);
            i++;
        }
        */
            //Triangular
        /*
        value=0;
        while(value!=1023)
        {
            DACR=((1<<16)|(value<<6));
            value++;
        }
        while (value!= 0)
        {
            DACR=((1<<16)|(value<<6));
            value--;
        }
        */
            //Square
        value=1023;
        DACR=(value<<6);
        dLAY(100);
        value=0;
        DACR=(value<<6);
        dLAY(100);
    }
    return 0;
}