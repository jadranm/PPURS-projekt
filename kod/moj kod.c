/*
 * moj_kod.c
 *
 *  Author: Jadran Marinovic
 */ 

#include "AVR lib/AVR_lib.h"
#include "LCD/lcd.h"
#include <avr/io.h>
#include <util/delay.h>
#include "USART/USART.h"
#include "ADC/adc.h"


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
	output_port(DDRB,PB4);
	adc_init();
	usart_init(9600);			//tako pise na internetu
	
	sei();						//omogucavanje prekida
}

int main(void){
	inicijalizacija();
	
		uint16_t ADC5; // rezultat AD pretvorbe
		float Vout; // napon na pinu PA0
		float T; // temperatura u okolini senzora LM35
		const float VREF = 5.0; // AVCC
	
	while (1)
	{
		

		if(( PINB & 0x01) == 0x00){ // ako je pin PB0 u logickoj nuli
			
			ADC5 = adc_read_10bit(0);
			Vout = ADC5 * VREF / 1023;
					
			T = Vout * 100;
			
			lcd_clrscr ();
			lcd_home ();
			lcd_print("Temperatura=%0.1f%cC", T, 178);
			_delay_ms(500);
		}
		else{
			PORTB &= ~0xF0;			
		}
		
		//zujanje();
		
		*/
		if(usart_read_all() == 1){
			lcd_clrscr();
			lcd_home();
			lcd_print("test %s",usart_buffer);
			_delay_ms(1000);
		}
		
		}
	return 0;
}