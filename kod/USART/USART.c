/*
 Naslov: MIKRORAÈUNALA - Programiranje mikrokontrolera porodice 
 Atmel u programskom okruženju Atmel Studio 6
 Autori: Zoran Vrhovski, Marko Miletiæ
 
 USART.c
 */

#include "USART.h"


void usart_init(uint32_t baut_rate)
{
	uint16_t ubrr_value;
	ubrr_value = F_CPU / (16. * baut_rate) - 1;

	UBRRL = ubrr_value; // konfiguracija baudrate - a 
	UBRRH = (ubrr_value >> 8);

	UCSRC |= (1 << URSEL) | (3 << UCSZ0); // 8-bitna komunikacija
	UCSRB |= (1 << RXEN) | (1 << TXEN); // Rx i Tx omoguæen
	UCSRB |= (1 << RXCIE); // Prekid Rx omoguæen

}


char usart_read_char()
{
   //Wait untill a data is available
   while(!(UCSRA & (1<<RXC)));
 
   return UDR; 
}



void usart_write_char(char data)
{
   //Wait untill the transmitter is ready
   while(!(UCSRA & (1<<UDRE)));
   UDR=data;
}


char *pok_usart_buffer = usart_buffer;


ISR(USART_RXC_vect) 
{ 
	*pok_usart_buffer = usart_read_char();
	if (*pok_usart_buffer != end_char)
	pok_usart_buffer++;
}



bool usart_read_all(){

	if (*pok_usart_buffer == end_char)
	{
		*pok_usart_buffer = '\0';
		pok_usart_buffer = usart_buffer;
		return true;
	}
	
	else
	
		return false;
}


void usart_write_int(int16_t a){
	usart_write("%d",a);
}

void usart_write_string(char *a){

	while (*a){
		usart_write_char(*a);
		a++;			
	}
}

void usart_write(char *szFormat, ...)
{
	char szBuffer[MESSAGE_LENGTH]; //in this buffer we form the message
	va_list pArgs;
	va_start(pArgs, szFormat);
	vsprintf(szBuffer, szFormat, pArgs);
	va_end(pArgs);
	
	usart_write_string(szBuffer);

}

void usart_write_float(float a){
	
	usart_write("%0.4f",a);
}