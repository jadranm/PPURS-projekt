/*
 Naslov: MIKRORAÈUNALA - Programiranje mikrokontrolera porodice 
 Atmel u programskom okruženju Atmel Studio 6
 Autori: Zoran Vrhovski, Marko Miletiæ
 
 Vježba adc.c
 */ 



#include <avr/io.h>
#include <avr/interrupt.h>
#include "adc.h"


// inicijalizacija adc pretvorbe
void adc_init()
{
		// postavi referencu
		ADMUX &= ~ADC_REFERENCE_MASK;
		ADMUX |= ADC_REFERENCE << 6;
		
		// postavi djelitelj frekvencije
		ADCSRA &= ~ADC_PRESCALE_MASK;
		ADCSRA |=  ADC_PRESCALE;
		
		// omoguæi adc pretvorbu
		ADCSRA|=(1<<ADEN);
}

// Perform a 10-bit conversion
// starts conversion, waits until conversion is done, and returns result
unsigned short adc_read_10bit(uint8_t ch)
{
	
	ch &= ADC_CH_MASK;
	
	ADMUX &= ~ADC_MUX_MASK;
	ADMUX |= ch;
	
	ADCSRA|=(1<<ADSC);

	//Wait for conversion to complete
	while(!(ADCSRA & (1<<ADIF)));

	//Clear ADIF by writing one to it

	ADCSRA|=(1<<ADIF);

	return(ADC);  // read ADC (full 10 bits);
}

// Perform a 8-bit conversion.
// starts conversion, waits until conversion is done, and returns result
unsigned char adc_read_8bit(uint8_t ch)
{
	// do 10-bit conversion and return highest 8 bits
	return adc_read_10bit(ch)>>2;			// return ADC MSB byte
}
