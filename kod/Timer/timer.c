/*
 Naslov: MIKRORA�UNALA - Programiranje mikrokontrolera porodice 
 Atmel u programskom okru�enju Atmel Studio 6
 Autori: Zoran Vrhovski, Marko Mileti�
 
 timer.h
 */

#include "timer.h"
#include <avr/io.h>


void timer0_init(){
	
	TCCR0 &= ~TIMER_PRESCALER_MASK;
	TCCR0 |= TIMER0_PRESCALER; // postavi djelitelj za timer0
	
	TIMSK |= (1 << TOIE0); // omogu�i prekid TOV0
}

void timer1_init(){
	
	TCCR1B &= ~TIMER_PRESCALER_MASK;
	TCCR1B |= TIMER1_PRESCALER; // postavi djelitelj za timer1
	
	TIMSK |= (1 << TOIE1); // omogu�i prekid TOV1
	
}

void timer2_init(){
	
	TCCR2 &= ~TIMER_PRESCALER_MASK;
	TCCR2 |= TIMER2_PRESCALER; // postavi djelitelj za timer2
	
	TIMSK |= (1 << TOIE2); // omogu�i prekid TOV2
}