/*
 Naslov: MIKRORA�UNALA - Programiranje mikrokontrolera porodice 
 Atmel u programskom okru�enju Atmel Studio 6
 Autori: Zoran Vrhovski, Marko Mileti�
 
 Vje�ba 5.1.7
 */ 

#include "AVR lib/AVR_lib.h"
#include <avr/io.h>
#include "LCD/lcd.h"


void inicijalizacija(){
	
	lcd_init(); // inicijalizacija lcd displeja
	lcd_define_char(); //definiranje novih znakova
}

int main(void){
	
	inicijalizacija();

		
		while (1)
		{
			lcd_clrscr();
			lcd_home();		
			lcd_print("Visoka tehni"); 
			lcd_char(0x00); // znak � na adresi 0x00
			lcd_print("ka");
			lcd_gotoxy(1,2);
			lcd_print("%ckola u Bj", 0x03); // znak � na adresi 0x03
			_delay_ms(2000);

			lcd_clrscr();
			lcd_home();
			lcd_gotoxy(0,1);
			lcd_print("Stru");
			lcd_char(0x00); // znak �
			lcd_print("ni studij");
			lcd_gotoxy(1,2);
			lcd_print("Mehatronika");
			_delay_ms(2000);

		}

	return 0;
}