/*
 Naslov: MIKRORAÈUNALA - Programiranje mikrokontrolera porodice 
 Atmel u programskom okruženju Atmel Studio 6
 Autori: Zoran Vrhovski, Marko Miletiæ
 
 Vježba 5.1.8
 */ 

#include "AVR lib/AVR_lib.h"
#include <avr/io.h>
#include "LCD/lcd.h"

void inicijalizacija(){
	
	lcd_init(); // inicijalizacija lcd displeja
}

int main(void){
	
	inicijalizacija();
	

	lcd_clrscr(); 
	lcd_home(); 
	lcd_print("Materijali se nalaze na web stranici:\n");
	lcd_print("www.vtsbj.hr/mikroracunala");
		
	while (1)
	{
		lcd_instr(LCD_ENTRY_INC_SHIFT);
		lcd_instr(LCD_MOVE_DISP_LEFT); 
		_delay_ms(1000);
	}

	return 0;
}