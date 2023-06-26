/*
 Naslov: MIKRORAÈUNALA - Programiranje mikrokontrolera porodice 
 Atmel u programskom okruženju Atmel Studio 6
 Autori: Zoran Vrhovski, Marko Miletiæ
 
 timer.h
 */


#ifndef TIMER_H_
#define TIMER_H_

//za timer0
#define TIMER0_PRESCALER_OFF		0x0
#define TIMER0_PRESCALER_1			0x1
#define TIMER0_PRESCALER_8			0x2
#define TIMER0_PRESCALER_64			0x3
#define TIMER0_PRESCALER_256		0x4
#define TIMER0_PRESCALER_1024		0x5
#define TIMER0_EXTERNAL_FALL_EDGE	0x6
#define TIMER0_EXTERNAL_RISI_EDGE	0x7

//za timer 1
#define TIMER1_PRESCALER_OFF		0x0
#define TIMER1_PRESCALER_1			0x1
#define TIMER1_PRESCALER_8			0x2
#define TIMER1_PRESCALER_64			0x3
#define TIMER1_PRESCALER_256		0x4
#define TIMER1_PRESCALER_1024		0x5
#define TIMER1_EXTERNAL_FALL_EDGE	0x6
#define TIMER1_EXTERNAL_RISI_EDGE	0x7

// za timer 2
#define TIMER2_PRESCALER_OFF		0x0
#define TIMER2_PRESCALER_1			0x1
#define TIMER2_PRESCALER_8			0x2
#define TIMER2_PRESCALER_32			0x3
#define TIMER2_PRESCALER_64			0x4
#define TIMER2_PRESCALER_128		0x5
#define TIMER2_PRESCALER_256		0x6
#define TIMER2_PRESCALER_1024		0x7

#define TIMER0_PRESCALER TIMER0_PRESCALER_1024	 // korisnik odabire djelitelj frekvencije za timer0
#define TIMER1_PRESCALER TIMER1_PRESCALER_64	 // korisnik odabire djelitelj frekvencije za timer1
#define TIMER2_PRESCALER TIMER2_PRESCALER_1024	// korisnik odabire djelitelj frekvencije za timer2

#define TIMER_PRESCALER_MASK		0x7 

// omoguæenje i onemoguæenje prekida timera0,1,2 na jednostavan naèin
#define TIMER0_INTERRUPT_ENABLED TIMSK |= (1 << TOIE0)
#define TIMER0_INTERRUPT_DISABLE TIMSK &= ~(1 << TOIE0)
#define TIMER1_INTERRUPT_ENABLED TIMSK |= (1 << TOIE1)
#define TIMER1_INTERRUPT_DISABLE TIMSK &= ~(1 << TOIE1)
#define TIMER2_INTERRUPT_ENABLED TIMSK |= (1 << TOIE2)
#define TIMER2_INTERRUPT_DISABLE TIMSK &= ~(1 << TOIE2)


void timer0_init();
void timer1_init();
void timer2_init();


#endif /* TIMER_H_ */