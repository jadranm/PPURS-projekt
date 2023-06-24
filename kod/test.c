/*
 Autor: Jadran Marinovic
 
 */
#include "AVR lib/AVR_lib.h"
#include "LCD/lcd.h"
#include <avr/io.h>
#include <util/delay.h>
#include "USART/USART.h"
#include "ADC/adc.h"


#define BROJ_ZUJANJA 2
#define BROJ_UZORKOVANJA 10

void zujanje(){
	int i;
	
	for (i=0;i<BROJ_ZUJANJA;i++){
		BUZZ (0.5 , 1000);
		_delay_ms(500);
	}
	return 0;
}

uint16_t usrednjavanje(uint8_t pin){
	uint16_t ADC_zbroj = 0, ADC_prosjek = 0;
			
	for(uint8_t i;i<BROJ_UZORKOVANJA;i++){		//usrednjavanje rezultata
		ADC = adc_read_10bit(pin);
		ADC_zbroj = ADC_zbroj + ADC;
		_delay_ms(100);							//podesite delay
		}
		
	ADC_prosjek = ADC_zbroj / BROJ_UZORKOVANJA;
		return ADC_prosjek;
}

void inicijalizacija(){
	
	lcd_init();
	set_port(PORTB ,PB0 ,1);
	output_port(DDRB,PB4); // PB4 postavljen kao izlazni pin
	adc_init();
	//usart_init(9600);				//tako pise na internetu
	
	sei(); // globalno omogucavanje prekida
}

int main(void){
	inicijalizacija();
	
		uint16_t CO2 = 0;
		
		float Vout0, Vout1; // napon na pinu PA0
		float Temp; // temperatura u okolini senzora LM35
		const float VREF_temp = 5.0, VREF_pwm = 3.3; // AVCC
	
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
		
		
		uint16_t co2=0, high=0, low=0, resp=0;
		
		usart_write_char("\xFE\x44\x00\x08\x02\x9F\x25");		//uzeto iz random videa na youtubu https://youtu.be/395yN1eJKyc
		lcd_clrscr();
		lcd_home();
		lcd_print("usart poslan");
		_delay_ms(2000);
		
		*/
		/*
		resp = usart_buffer();
		high = resp[3];
		low = resp[4];
		co2 = (high*256) + low;
		lcd_print("CO2: %d ppm",co2);
		_delay_ms(100);
		
		
		
		
		if(usart_read_all() == 1){
			lcd_clrscr();
			lcd_home();
			lcd_print("test %s",usart_buffer);
			_delay_ms(1000);
		}else{
			lcd_clrscr();
			lcd_home();
			lcd_print("ne radi");
			_delay_ms(1000);
		}
		
		*/
		//za ADC0 za LM35
		uint16_t rezultat0 = 0;
		rezultat0 = usrednjavanje(0);

		Vout0 = (rezultat0) * VREF_temp / 1023;
		Temp = Vout0 * 100;
		
		lcd_clrscr();
		lcd_home();
		lcd_print("Temperatura:");
		lcd_gotoxy(1,0);							//redak pa stupac
		lcd_print("%0.2f%cC", Temp, 178);
		_delay_ms(500);
		
		
		
		
		//napraviti pwm sa prekidima na brid
		
		//za ADC1 za pwm
		uint16_t rezultat1 = 0;
		rezultat1 = usrednjavanje(1);
		
		Vout1 = (rezultat1) * VREF_pwm / 1023;		//dovrsiti
		CO2 = Vout1 * 100;
		
		lcd_clrscr();
		lcd_home();
		lcd_print("CO2 :");
		lcd_gotoxy(1,0);		
		lcd_print("%d ppm",CO2);
		_delay_ms(500);
		
		}
	return 0;
}