/*
 Autor: Jadran Marinovic
 
 */
#include "AVR lib/AVR_lib.h"
#include "LCD/lcd.h"
#include <avr/io.h>
#include <util/delay.h>
#include "ADC/adc.h"
#include <avr/interrupt.h>


#define BROJ_ZUJANJA 2
#define BROJ_UZORKOVANJA 10

uint8_t brojac_int1;

void zujanje(){
	
	
	for (uint8_t i;i<BROJ_ZUJANJA;i++){
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
		_delay_ms(100);							//podesiti delay
		}
		
	ADC_prosjek = ADC_zbroj / BROJ_UZORKOVANJA;
		return ADC_prosjek;
}

ISR(INT1_vect) // prekidna rutina za INT1
{
	brojac_int1++;
	if (brojac_int1=1){
		
	}
	
}

void inicijalizacija(){
	
	lcd_init();
	adc_init();
	sei();		//omogucavanje prekida
	
	set_port(PORTB ,PB0 ,1);
	output_port(DDRB,PB4);		//PB4 postavljen kao izlazni pin
	input_port(DDRD,PD3);		// pin PD3 postavljen kao ulazni
	
	
	
	//prekidi na oba brida
	set_bit_reg(GICR,INT1); // omogucen vanjski prekid INT1
	
	set_bit_reg(MCUCR,ISC10); // ISC10 = 1
	reset_bit_reg(MCUCR,ISC11); // ISC11 = 0

	timer1_init ();																								//napravi novi branch prije vecih promjena npr. mjerenja pwm-a
		
	//koristim counter1 (16 bitni)
	// normalan nacin rada - timer1
	reset_bit_reg(TCCR1A ,WGM10); // WGM10 = 0
	reset_bit_reg(TCCR1A ,WGM11); // WGM11 = 0
	reset_bit_reg(TCCR1B ,WGM12); // WGM12 = 0
	reset_bit_reg(TCCR1B ,WGM13); // WGM13 = 0
	
	
	
}

int main(void){
	inicijalizacija();
		
		float Vout0; // napon na pinu PA0
		float Temp;
		const float VREF_temp = 5.0;
	
		
	while (1)
	{

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
		
		}
	return 0;
}