/*
 Naslov: MIKRORAÈUNALA - Programiranje mikrokontrolera porodice 
 Atmel u programskom okruženju Atmel Studio 6
 Autori: Zoran Vrhovski, Marko Miletiæ
 
AVR_lib.c
 */ 

#include "AVR_lib.h"
#include <util/delay.h>

// debounce 
// funkcija prima tri parametra, prvi je adresa porta, drugi je pozicija pina, a treæi je logièka varijabla (0 ili 1, false ili true)
// funkcija vraæa vrijednost treæeg parametra ako je i stanje pina jednako treæem parametru i nakon èekanja od DEBOUNCE_TIME ms

bool debounce(uint8_t* port, uint8_t pin, bool _value){

	if (get_pin(*port,pin) == _value){
		int a = 0;
		int brojac = 0;
		while(a++ < DEBOUNCE_TIME){
			_delay_ms(1);
		if (get_pin(*port,pin) == _value) brojac++;
		}
		if (brojac >= DEBOUNCE_TIME * 9 /10){
			return _value;
		}
	}
	return !_value;
}

// debounce2
// funkcija prima èetiri parametra, prvi je adresa porta, drugi je pozicija pina, treæi je logièka varijabla (0 ili 1, false ili true),
// a èetvrti je funkcija koja se poziva ukoliko je stanje pina jednako treæem parametru i nakon èekanja od DEBOUNCE_TIME ms


void debounce2(uint8_t* port, uint8_t pin, bool _value, void (*f)()){

	if (get_pin(*port,pin) == _value){
		int a = 0;
		int brojac = 0;
		while(a++ < DEBOUNCE_TIME){
			_delay_ms(1);
			if (get_pin(*port,pin) == _value) brojac++;
		}
		if (brojac >= DEBOUNCE_TIME * 9 /10){
			f();
		}
	
	}
}


// funkcija za zujalicu
// duration - trajanje zvuka u sekundama
// freq - frekvencija
void BUZZ(double duration, int freq) 
{
	long int i,cycles;
	cycles = duration * freq; // Compute the number of cycles to loop toggling the pin
	long int period = 1.0/freq * 100000; // Compute a half cycle period
	long int half_period =  period / 2;
	BUZZER_DDR = (1 << BUZZER_PIN) | BUZZER_DDR;  // Set the port for the buzzer output
	
	for (i=0; i < cycles; i++)   // Toggle the speaker the appropriate number of cycles
	{
		half_period = period/2;
		while(half_period--) {
			_delay_us(10);
		}                       
		
		BUZZER_PORT = (1 << BUZZER_PIN) | BUZZER_PORT;    // Set the port pin
		
		half_period = period/2;
		while(half_period--) {
			_delay_us(10);
		}                       // Wait a half cycle to clear the port pin
		BUZZER_PORT = ~(1 << BUZZER_PIN) & BUZZER_PORT;   // Clear the port pin
	}
	
}