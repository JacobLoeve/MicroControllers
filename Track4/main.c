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
	_delay_ms(1);			// nodig
	PORTC &= ~(1<<LCD_E);  	// E low
	_delay_ms(1);			// nodig?
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
	lcd_write_command(0b11001000);

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
	//DDRB |= (1 << 0);
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
	TIMSK |= (1 << TOIE2);
	TCNT2 = 0xFF;
	TCCR2 = 0b00011111;
}
//opgave B2
ISR( TIMER2_OVF_vect )
{
	TCNT2 = 0xFF;
	count++;
}
//opgave B2
int opdrachtB2( void )
{
		// Init I/O
		DDRB = 0xFF;			//PORTB all output
		PORTB = 0x00;			//PORTB all LED's off
		DDRD = 0x00;

		initLCD();
		clearLCD();
		_delay_ms(50);

		initCounter();
		sei();

		while (1)
		{
			clearLCD();

			sprintf(str, "%d", count);
			displayText(str);
			memset(str, 0, 10);

			_delay_ms(1000);
		}

		return 0;
}

//opgave B3
void timerInit()
{
	TIMSK |= 0xFF;
	TCNT2 = 0;
	OCR2 = COMP1;
	TCCR2 = 0x1D;
}
//opgave B3
ISR(TIMER2_COMP_vect)
{
	if(OCR2 == COMP1)
	{
		OCR2 = COMP2;
		PORTC = 0x80;
	}
	else if(OCR2 == COMP2)
	{
		OCR2 = COMP1;
		PORTC = 0x00;
	}
}
// opgave B3
int main(void)
{
	DDRC = 0xFF;
	DDRD = 0x00;
	timerInit();
	sei();
	while(1)
	{
		
	}

	return 0;
}