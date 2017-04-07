#define f_cpu 8000000
#define _bv(bit) (1 << bit);

#include <avr/io.h>
#include <util/delay.h>

void wait(int ms);
void board_init(void);

void wait( int ms )
{
	for (int i=0; i<ms; i++)
	{
		_delay_ms( 1 );
	}
}

// change name to main to run this code
int track1 (void)
{
	board_init();

	// opdracht B2
	//B2();

	// opdracht B3
	//B3();

	//opdracht B4
	//B4();

	return 0;
}

int B2( void )
{
	DDRD = 0xFF;
	PORTD = 0x00;
	
	board_init();
	while (1)
	{
		PORTD |= 0b01000000;
		PORTD &= 0b11011111;
		wait(500);
		PORTD &= 0b10111111;
		PORTD |= 0b00100000;
		wait(500);
	}
	return 1;
}

 int B3( void )
 {
	 board_init();
	 DDRD = 0xFF;
	 PORTD = 0x00;
	 
	 DDRC &= ~(1 << PC0);
	 
	 while (1)
	 {
		 if(PINC & (1<<PC0))
		 {
			 PORTD |= 0b10000000;
			 wait(500);
			 PORTD &= 0b01111111;
			 wait(500);
		 }
	 }

	 return 1;
 }

  int B4( void )
  {
	  board_init();
	  DDRD = 0xFF;
	  PORTD = 0x00;
	  
	  DDRC &= ~(1 << PC0);
	  
	  while (1)
	  {
		  if(PINC & (1<<PC0))
		  {
			  for(int t = 0; t <= 7; t++)
			  {
				  PORTB = (0x01 << t);
				  PORTD = (0x01 << t);
				  wait(250);
			  }
		  }
	  }

	  return 1;
  }
