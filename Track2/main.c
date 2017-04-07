/*
 * Track2.c
 *
 * Created: 8-3-2017 16:19:46
 * Author : Jacob
 */ 

#define F_CPU 8000000

#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>

void wait(int ms);
void display(int digit);
int count2 = 0;

const unsigned char Numbers[17] = {
	0b00000001,
	0b00000010,
	0b00000100,
	0b00001000,
	0b00010000,
	0b00100000,
	0b00000000,
	0b01111111,
	0b00000001,
	0b00100010,
	0b00010100,
	0b00001000,
	0b01000000,
	0b00000001,
	0b00000000,
	0b01111111,
	0b00000000,
};

/******************************************************************/
void wait( int ms )
{
	for (int i=0; i<ms; i++)
	{
		_delay_ms( 1 );		// library function (max 30 ms at 8MHz)
	}
}

/******************************************************************/
ISR( INT1_vect )
{
	//wait(10);
	//count2++;
	//if (PIND0 == 0 && PIND1 == 0)
	//{
	//count2 = 0;
	//}
}

/******************************************************************/
ISR( INT2_vect )
{
	//wait(10);
	//count2++;
	//if (PIND0 == 0 && PIND1 == 0)
	//{
	//count2 = 0;
	//}
}


void display(int digit)
{
	PORTB = Numbers[digit];
}

/******************************************************************/
int main( void ) //make this method main to run on itself
/*
short:			main() loop, entry point of executable
inputs:
outputs:
notes:			Slow background task after init ISR
Version :    	DMK, Initial code
*******************************************************************/
{
	// Init I/O
	DDRB = 0xFF;			//PORTB all output
	PORTB = 0x00;			//PORTB all LED's off
	DDRC = 0xFF;			// PORTC all output
	DDRD = 0xF0;			// PORTD(7:4) output, PORTD(3:0) input

	// Init Interrupt hardware
	EICRA |= 0x2C;			// INT1 falling edge, INT0 rising edge
	EIMSK |= 0x06;			// Enable INT2 & INT1
	
	// Enable global interrupt system
	//SREG = 0x80;			// Of direct via SREG of via wrapper
	sei();

	while (1)
	{
		PORTD ^= (1<<7);	// Toggle PORTD.7
		wait( 500 );
		if(count2 >= 18)
		count2 = 0;

		display(count2);
		count2++;
	}

	return 1;
}



typedef struct { 
	unsigned char data;
	int delay ;
} PATTERN_STRUCT; 


PATTERN_STRUCT pattern[] = {
	{0b00000001, 150},
	{0x01, 150},
	{0x40, 150},
	{0x14, 150},
	{0x08, 150}, 
	{0xFF, 0}
};

int  B4 (void)
{
	DDRD = 0xFF;					// PORTD to output 
	
	while (1)
	{
		int index = 0;
		while( pattern[index].delay != 0 ) 
		{
			PORTD = pattern[index].data;	// set PORTD with the value from array	
			wait(pattern[index].delay);		// wait
			index++;
		}
	}

	return -1;
}



