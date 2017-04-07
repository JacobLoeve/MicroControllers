#define F_CPU 8000000

#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>

#define LCD_E 	3
#define LCD_RS	2

#define COMP1 117
#define COMP2 195

void strobeLCD(void);
void initLCD(void);
void displayText(char *str);
void lcd_write_data(unsigned char byte);
void lcd_write_command(unsigned char byte);
void setCursor(int position);
void clearLCD(void);
void initCounter(void);

//opgave B2
volatile int count = 0;
static char str[10];

void strobeLCD(void)
{
	PORTC |= (1<<LCD_E);	// E high
	_delay_ms(1);			// needed
	PORTC &= ~(1<<LCD_E);  	// E low
	_delay_ms(1);			// not really needed, but just to be sure
}

void initLCD(void)
{
	// PORTC output mode and all low (also E and RS pin)
	DDRC = 0xFF;
	PORTC = 0x00; 

	// Step 2 (table 12) 
	PORTC = 0x20;	// function set
	strobeLCD();	

	// Step 3 (table 12)
	PORTC = 0x20;   // function set
	strobeLCD();		
	PORTC = 0x80;
	strobeLCD();	

	// Step 4 (table 12)
	PORTC = 0x00;   // Display on/off control
	strobeLCD();		
	PORTC = 0xF0;
	strobeLCD();	

	// Step 4 (table 12)
	PORTC = 0x00;   // Entry mode set
	strobeLCD();		
	PORTC = 0x60;
	strobeLCD();	
}

void displayText(char *str)
{
	for(;*str; str++){
		lcd_write_data(*str);
	}
}

// shift cursor to the given position
void setCursor(int position)
{
	for(int i = 0; i < position; i++)
	{
		lcd_write_command(0x83);
	}
}

void lcd_write_data(unsigned char byte)
{
	// First nibble. 
	PORTC = byte;
	PORTC |= (1<<LCD_RS);
	strobeLCD();

	// Second nibble
	PORTC = (byte<<4);
	PORTC |= (1<<LCD_RS);
	strobeLCD();
}

void lcd_write_command(unsigned char byte)
{
	// First nibble. 
	PORTC = byte;
	PORTC &= ~(1<<LCD_RS);
	strobeLCD();

	// Second nibble
	PORTC = (byte<<4);
	PORTC &= ~(1<<LCD_RS);
	strobeLCD();
}

//clear the lcd by writing all empty
void clearLCD( void )
{
	lcd_write_command(0x00);
	_delay_ms(100);
}

int opdrachtB1( void )
{
	_delay_ms(1000);
	DDRD = 0xFF;
	initLCD();

	clearLCD();

	displayText("ABCDEFGAY__BOOBS");

	//setCursor(2);
	//lcd_write_command(0x14); // shift cursor 1 pos to right
	lcd_write_command(0xC8);  // or use 0b11001000

	while (1)
	{
		PORTD ^= (1<<7);
		_delay_ms( 250 );
	}

	return 1;
}

// this function makes LED PB0 blink every second, just for fun
int blinkingled( void )
{
	initLCD();
	displayText("");
	DDRB = 0xFF;
	TCCR1B |= ((1 << CS10) | (1 << CS11));
	for(;;)
	{
		if(TCNT1 >= 15624)
		{
			PORTB ^= (1 << 0);
			TCNT1 = 0;
		}
	}
	return 0;
}

//opgave B2
void initCounter( void )
{
	TIMSK |= (1 << TOIE2);	//enable TIMSK
	TCNT2 = 0xFF;			//TCNT2 all high to initialize
	TCCR2 = 0b00011111;		//TCCR2 first 5 bits high, last 3 bit low
}
//opgave B2
ISR( TIMER2_OVF_vect )
{
	TCNT2 = 0xFF;
	count++;		//count 1 on interrupt
}
//opgave B2
int opdrachtB2( void )
{
		// Init I/O
		DDRB = 0xFF;			//DDRB all output
		PORTB = 0x00;			//PORTB all input, thus LEDs off
		DDRD = 0x00;			//DDRD all input

		initLCD();				//initialize LCD
		clearLCD();				//clear LCD to be sure there are no chars on it
		_delay_ms(50);

		initCounter();
		sei();					//enable global interrupts

		while (1)
		{
			clearLCD();

			sprintf(str, "%d", count);		// show value in output
			displayText(str);				// write value to LCD
			memset(str, 0, 10);				// write str to memory

			_delay_ms(1000);				//wait 1 second
		}

		return 0;
}

//opgave B3
void timerInit()
{
	TIMSK |= 0xFF;			//TIMSK all high
	TCNT2 = 0;				//TCNT2=0 to initialize
	OCR2 = COMP1;			//initialize compare value
	TCCR2 = 0x1D;			//initialize TCCR2
}
//opgave B3
ISR(TIMER2_COMP_vect)
{
	if(OCR2 == COMP1) 
	{
		OCR2 = COMP2;
		PORTC = 0x80; //PORTC has high value, LEDs turn on
	}
	else if(OCR2 == COMP2)
	{
		OCR2 = COMP1;
		PORTC = 0x00; //PORTC has low value, LEDs turn off
	}
}
// opgave B3
int main(void)
{
	DDRC = 0xFF;		//DDRC to output
	DDRD = 0x00;		//DDRD to input
	timerInit();		//initialize the timer
	sei();				//enable global interrupts
	while(1)
	{
						// do nothing, the interrupt will handle stuff if there is input
	}

	return 0;
}