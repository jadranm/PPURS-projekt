/*
 Autor: Jadran Marinovic
 
 */
#include "AVR lib/AVR_lib.h"
#include "LCD/lcd.h"
#include <avr/io.h>
#include <util/delay.h>
#include "ADC/adc.h"
#include <avr/interrupt.h>
#include "timer/timer.h"


#define BROJ_ZUJANJA 2
#define BROJ_UZORKOVANJA 10

uint16_t duty_duljina;

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


//interupti rade
//tajmer ne radi
ISR(INT1_vect){ // INT1 rastuci brid
	TCNT1 = 0;
}


ISR(INT2_vect){ // INT2 padajuci brid 
	duty_duljina = TCNT1;
}

ISR(TIMER1_OVF_vect){  //prekit timera1
	
	lcd_clrscr();
	lcd_home();
	lcd_print("preljev timera");
	_delay_ms(1000);
}


void inicijalizacija(){
	
	lcd_init();
	adc_init();
	
	
	set_port(PORTB ,PB0 ,1);
	output_port(DDRB,PB4);		//PB4 postavljen kao izlazni pin
	input_port(DDRD,PD3);		// pin PD3 postavljen kao ulazni
	
	
	
	//omoguceni prekidi na INT1 i INT2
	set_bit_reg(GICR ,INT1);
	set_bit_reg(GICR ,INT2); 
	
	//INT1 okida na rastuci bit
	set_bit_reg(MCUCR,ISC10); // ISC10 = 1
	set_bit_reg(MCUCR,ISC11); // ISC11 = 1

	//INT2 okida na padajuci bit
	//specijalni slucaj konfiguracije
	reset_bit_reg(MCUCR,ISC2); // ISC2 = 0
	

	/*
	//koristim counter1 (16 bitni)
	// normalan nacin rada - timer1
	reset_bit_reg(TCCR1A ,WGM10); // WGM10 = 0
	reset_bit_reg(TCCR1A ,WGM11); // WGM11 = 0
	reset_bit_reg(TCCR1B ,WGM12); // WGM12 = 0
	reset_bit_reg(TCCR1B ,WGM13); // WGM13 = 0
	*/
	
	sei();		//omogucavanje prekida
	timer1_init();
	
	TCNT1=0;
}



int main(void){
	inicijalizacija();
	
		//za ADC
		const float VREF_temp = 5.0;
		float Vout0;
		float Temp,CO2;
		float duty_cycle, postotak_duty;
		
		
	while (1)
	{

		duty_cycle = duty_duljina * 0.001;
		postotak_duty = (duty_cycle/1.002)*100;  //1.002 je sirina impulsa
		CO2 = 2000 * (postotak_duty/100);
		lcd_clrscr();
		lcd_home();
		lcd_print("%f", postotak_duty);
		lcd_gotoxy(1,0);							//redak pa stupac
		lcd_print("%0.0f ppm", CO2);
		_delay_ms(500);

		/*

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
		*/	
		}
	return 0;
}