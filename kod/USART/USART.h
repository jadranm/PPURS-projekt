/*
 Naslov: MIKRORAÈUNALA - Programiranje mikrokontrolera porodice 
 Atmel u programskom okruženju Atmel Studio 6
 Autori: Zoran Vrhovski, Marko Miletiæ
 
 USART.h
 */ 

#define F_CPU 8000000ul
#include <avr/io.h>
#include <avr/interrupt.h>
#include "stdbool.h"
#include <stdio.h>

void usart_init(uint32_t baut_rate);
void usart_write_int(int16_t a);
void usart_write_char(char data);
void usart_write_string(char *a);
void usart_write_float(float a);
void usart_write(char *szFormat, ...);
char usart_read_char();
bool usart_read_all();

#define end_char 0x0D // zakljuèni znak // 0x0D je znak za poèetak linije
#define MESSAGE_LENGTH 50 // maksimalna duljina poruke
char usart_buffer[MESSAGE_LENGTH];

