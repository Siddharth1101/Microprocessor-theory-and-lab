#ifndef DPAD_H
#define DPAD_H

#include <avr/io.h>

/******************************************************************************

Simple HAL (Hardware Abstraction Layer) for a standard 4 direction + 1 center
DPAD (directional key pad). This DPAD is used as main HID (Human Interface Device)
for our GUI framework. The screen is handled using the ProGFX graphic driver.

******************************************************************************/

/*

Connection Area, Can be used to configure the i/o line of buttons.

*/

//MICRO KEY
#define MICRO_KEY_DDR 	DDRC
#define MICRO_KEY_PORT 	PORTC
#define MICRO_KEY_PIN	PINC
#define MICRO_KEY_POS	PC0

//GRILL KEY
#define GRILL_KEY_DDR 	DDRC
#define GRILL_KEY_PORT 	PORTC
#define GRILL_KEY_PIN	PINC
#define GRILL_KEY_POS	PC1

//TM KEY
#define TM_KEY_DDR 	DDRC
#define TM_KEY_PORT PORTC
#define TM_KEY_PIN	PINC
#define TM_KEY_POS	PC2

//M KEY
#define M_KEY_DDR 	DDRC
#define M_KEY_PORT	PORTC
#define M_KEY_PIN	PINC
#define M_KEY_POS	PC3

//TS KEY
#define TS_KEY_DDR 	DDRC
#define TS_KEY_PORT	PORTC
#define TS_KEY_PIN	PINC
#define TS_KEY_POS	PC4

//STOP KEY
#define STOP_KEY_DDR 	DDRC
#define STOP_KEY_PORT	PORTC
#define STOP_KEY_PIN	PINC
#define STOP_KEY_POS	PC5

//START KEY
#define START_KEY_DDR 	DDRD
#define START_KEY_PORT	PORTD
#define START_KEY_PIN	PIND
#define START_KEY_POS	PD2

#define KEY_MICRO	0
#define KEY_GRILL	1
#define KEY_TM		2
#define KEY_M		3
#define KEY_TS		4
#define KEY_STOP	5
#define KEY_START	6
#define KEY_NONE	99

#define PRESSED		0
#define RELEASED	1

//Queue
#define KEYPAD_QMAX 32


void KeypadInit();
uint8_t GetRawKeyState(uint8_t KeyCode);
uint8_t MajorVote(uint8_t keycode);
uint8_t GetKeypadCmd(char wait);

#endif




