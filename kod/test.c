/*
 Autor: Jadran Marinovic
 
 */

#include "AVR lib/AVR_lib.h"
#include "LCD/lcd.h"
#include <avr/io.h>
#include <util/delay.h>
#include "USART/USART.h"


#define BROJ_ZUJANJA 2


void zujanje(){
	int i;
	
	for (i=0;i<BROJ_ZUJANJA;i++){
		BUZZ (0.5 , 1000);
		_delay_ms(500);
	}
}

void inicijalizacija(){
	
	lcd_init();
	set_port(PORTB ,PB0 ,1);
	output_port(DDRB,PB4); // PB4 postavljen kao izlazni pin
	
	usart_init (19200);
}

int main(void){
	inicijalizacija();
	while (1)
	{
		/*
		if(( PINB & 0x01) == 0x00){ // ako je pin PB0 u logickoj nuli
			PORTB |= 0xF0;			// uklju£i sve LED diode
			//zujanje();
		}
		else{
			PORTB &= ~0xF0;			// inace ih iskljuci
		}
		*/
		
		lcd_clrscr ();
		lcd_home ();
		lcd_print("Jadran\nMarinovic");
		_delay_ms (2000);
		lcd_clrscr ();
		lcd_home ();
		lcd_gotoxy (0,0);
		lcd_print("TVZ");
		_delay_ms (2000);
		//zujanje();
		
	}
	return 0;
}