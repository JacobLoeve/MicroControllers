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
  
  // data determines if the LED is on or off, the delay determines the waiting period
typedef struct {
	char data;
	int delay ;
} step;


//array with the pattern for B5
step steps[] = {
	{0x81,1000},{0x42,1000},{0x24,1000},{0x18,1000},
	{0x81,500},{0x42,500},{0x24,500},{0x18,500},
	{0x81,250},{0x42,250},{0x24,250},{0x18,250}
};

  int B5( void )
  {
	int index=0;
	DDRD = 0xFF;	//PORTD to OUTPUT
	while (1)
	{
		PORTD= steps[index].data;						//write value from array to PORTD
		index++;
		wait(steps[index].delay);			`			//wait for a bit so the pattern doesnt move like crazy
		if((sizeof(steps)/sizeof(steps[0])) < index)		//check if end of array is reached
			index = 0;					
	}
  }
  
  int B6( void )
  {
	DDRD = 0xFF;					// D to output
	DDRC = 0x00;					// C to input
	PORTD = 0x0;					// zet port D op 0
	int toggle = 0;					
	int waittime = 10;
	int pressed = 0;
	while (1)
	{
		if (PINC & 0x1)		{			// register button press
			if(toggle == 0)
			{
				toggle = 1;
				waittime = 500;				// 1 blink per second
			}
			else
			{
				toggle = 0;
				waittime = 250;				// 2 blinks per second
			}
		}
		wait(waittime);
		PORTD ^= 0x40;					// toggle portD bit7
	}
	return -1;
  }
