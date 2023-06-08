/*
 Naslov: MIKRORAÈUNALA - Programiranje mikrokontrolera porodice 
 Atmel u programskom okruženju Atmel Studio 6
 Autori: Zoran Vrhovski, Marko Miletiæ
 
 Vježba adc.h
 */ 


#ifndef ADC_H
#define ADC_H

// defines

// adc clock prescaler select
//		*selects how much the CPU clock frequency is divided
//		to create the adc clock frequency
//		*lower division ratios make conversion go faster
//		*higher division ratios make conversions more accurate

// definirani djelitelji frekvencije
#define ADC_PRESCALE_DIV2		0x00	// F_CPU/2
#define ADC_PRESCALE_DIV4		0x02	// F_CPU/4
#define ADC_PRESCALE_DIV8		0x03	// F_CPU/8
#define ADC_PRESCALE_DIV16		0x04	// F_CPU/16
#define ADC_PRESCALE_DIV32		0x05	// F_CPU/32
#define ADC_PRESCALE_DIV64		0x06	// F_CPU/64
#define ADC_PRESCALE_DIV128		0x07	// F_CPU/128

// odabir djelitelja frkevencije
#define ADC_PRESCALE			ADC_PRESCALE_DIV128

// do not change the mask value
#define ADC_PRESCALE_MASK		0x07

// adc voltage reference select
// *this determines what is used as the
// full-scale voltage point for adc conversions

// definirane konstante za odabir referentnog iznosa napona
#define ADC_REFERENCE_AREF		0x00	// AREF pin
#define ADC_REFERENCE_AVCC		0x01	// AVCC pin
#define ADC_REFERENCE_RSVD		0x02	// Rezervirana
#define ADC_REFERENCE_256V		0x03	// unutatnjih 2.56V

// odabir referentnog iznosa napona od prethodnih tri moguæih
#define ADC_REFERENCE			ADC_REFERENCE_AVCC

// do not change the mask value
#define ADC_REFERENCE_MASK		0xC0

// bit mask for adc channel multiplexer
#define ADC_MUX_MASK			0x1F

// channel defines (for reference and use in code)
// these channels supported by all AVRs with adc

#define ADC_CH_ADC0			0x00
#define ADC_CH_ADC1			0x01
#define ADC_CH_ADC2			0x02
#define ADC_CH_ADC3			0x03
#define ADC_CH_ADC4			0x04
#define ADC_CH_ADC5			0x05
#define ADC_CH_ADC6			0x06
#define ADC_CH_ADC7			0x07
#define ADC_CH_122V			0x1E	///< 1.22V voltage reference
#define ADC_CH_AGND			0x1F	///< AGND

#define ADC_CH_MASK			0x07



// function prototypes

//! Initializes the A/D converter.
/// Turns ADC on and prepares it for use.
void adc_init(void);

//! Starts a conversion on A/D channel# ch,
/// returns the 10-bit value of the conversion when it is finished.
unsigned short adc_read_10bit(uint8_t ch);

//! Starts a conversion on A/D channel# ch,
/// returns the 8-bit value of the conversion when it is finished.
unsigned char adc_read_8bit(uint8_t ch);

#endif
//@}
