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
	switch (digit)
	{
		case 0: PORTB = Numbers[0];
		break;
		case 1: PORTB = Numbers[1];
		break;
		case 2: PORTB = Numbers[2];
		break;
		case 3: PORTB = Numbers[3];
		break;
		case 4: PORTB = Numbers[4];
		break;
		case 5: PORTB = Numbers[5];
		break;
		case 6: PORTB = Numbers[6];
		break;
		case 7: PORTB = Numbers[7];
		break;
		case 8: PORTB = Numbers[8];
		break;
		case 9: PORTB = Numbers[9];
		break;
		case 10: PORTB = Numbers[10];
		break;
		case 11: PORTB = Numbers[11];
		break;
		case 12: PORTB = Numbers[12];
		break;
		case 13: PORTB = Numbers[13];
		break;
		case 14: PORTB = Numbers[14];
		break;
		case 15: PORTB = Numbers[15];
		break;
	}
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
}

