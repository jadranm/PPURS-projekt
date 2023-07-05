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
#include <stdbool.h>


#define BROJ_ZUJANJA 2
#define BROJ_UZORKOVANJA 10
#define TEMP_TOLERANCIJA 2	//u postotku


uint16_t duty_duljina;


void alarm(bool buzz){
	uint8_t i;
	
	for (i = 0;i<BROJ_ZUJANJA;i++){
		
		if (buzz == true)
			BUZZ (0.5 , 1000);
		
		PORTB |= 0xF0;
		_delay_ms(500);
		PORTB &= ~0xF0;
		_delay_ms(500);
	}
	return 0;
}

float usrednjavanje(uint8_t pin){
	
	float ADC_zbroj = 0, ADC_prosjek = 0;
	uint8_t i;
	
	for(i = 0; i < BROJ_UZORKOVANJA; i++){		//usrednjavanje rezultata
		ADC = adc_read_10bit(pin);
		ADC_zbroj = ADC_zbroj + ADC;
		_delay_ms(10);
		}
		
	ADC_prosjek = ADC_zbroj / BROJ_UZORKOVANJA;
	return ADC_prosjek;
}


ISR(INT1_vect){		// INT1 rastuci brid
	
	TCNT1 = 0;
}


ISR(INT2_vect){		// INT2 padajuci brid 
	
	duty_duljina = TCNT1;
}


ISR(TIMER1_OVF_vect){  //prekid timera1
	
	lcd_clrscr();
	lcd_home();
	lcd_print("greska pwm-a");
	
	alarm(false);
}


void inicijalizacija(){
	
	lcd_init();
	adc_init();
	sei();
	timer1_init();
	
	
	set_port(PORTB ,PB0 ,1);	//PB0 tipkalo
	output_port(DDRB,PB4);		//PB4 ledica
	
	
	//omoguceni prekidi na INT1 i INT2
	set_bit_reg(GICR ,INT1);
	set_bit_reg(GICR ,INT2); 
	
	
	//INT1 okida na rastuci bit
	set_bit_reg(MCUCR,ISC10); // ISC10 = 1
	set_bit_reg(MCUCR,ISC11); // ISC11 = 1


	//INT2 okida na padajuci bit
	//specijalni slucaj konfiguracije
	reset_bit_reg(MCUCR,ISC2); // ISC2 = 0


	TCNT1=0;
}


int main(void){
	inicijalizacija();
	
		//za ADC
		const float VREF_temp = 5.0;
		float Vout0;
		float Temp, Temp_stara, rezultat0;
		
		//za CO2
		float CO2, duty_cycle, postotak_duty;
		uint8_t brojac_ekrana = 0;
		
		
	while (1){
		
		duty_cycle = duty_duljina * 0.001;
		postotak_duty = (duty_cycle/1.002)*100;  //1.002 je sirina impulsa
		CO2 = 2000 * (postotak_duty/100);
		
		if (CO2>1000){
			alarm(true);
		}
		
		
		if(debounce (&PINB , PB0 , 0) == 0){
			set_port(PORTB , PB0 , 1);
			brojac_ekrana++;
						
			if(brojac_ekrana == 3)
				brojac_ekrana = 0;
				
		}else{
			set_port(PORTB , PB7 , 0);
		}
		
	
		
		if (brojac_ekrana == 0){
			
			lcd_clrscr();
			lcd_home();
			//lcd_print("%0.2f ", postotak_duty);
			lcd_print("CO2:");
			lcd_gotoxy(1,0);
			lcd_print("%0.0f ppm", CO2);
			
			_delay_ms(500);
			
		
		}else if (brojac_ekrana == 1){
			
			//za ADC0 za LM35
			rezultat0 = usrednjavanje(0);

			Vout0 = (rezultat0) * VREF_temp / 1023;
			Temp = Vout0 * 100;
			
				if (Temp_stara > Temp * (1 - (TEMP_TOLERANCIJA/100)) && Temp_stara < Temp * (1 + (TEMP_TOLERANCIJA/100))){
					
					lcd_clrscr();
					lcd_home();
					lcd_print("Temperatura55:");
					lcd_gotoxy(1,0);
					lcd_print("%0.2f%cC", Temp_stara, 178);
					
					_delay_ms(500);
					
				}else{
				
					lcd_clrscr();
					lcd_home();
					lcd_print("Temperatura:");
					lcd_gotoxy(1,0);
					lcd_print("%0.2f%cC", Temp, 178);
					Temp_stara = Temp;
					
					_delay_ms(500);
				}
				
			
			}else if(brojac_ekrana == 2){
				
				lcd_clrscr();
				lcd_home();
				lcd_print("Kvaliteta zraka:");
				//lcd_print("%0.0f ppm", CO2);
				lcd_gotoxy(1,0);
				
				
				if (CO2<600){
					lcd_print("odlicna");
					
				}else if(CO2>601 && CO2<800){
					lcd_print("jako dobra");
					
				}else if(CO2>801 && CO2<1000){
					lcd_print("dobra");
					
				}else if (CO2>1001 && CO2<1500){
					lcd_print("losa");
					
				}else{
					lcd_print("jako losa");
				} 
				
				_delay_ms(300);
			}
	}
	return 0;
}