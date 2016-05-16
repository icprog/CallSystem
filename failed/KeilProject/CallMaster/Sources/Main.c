#include "../PublicSources/Headers/PreMacro.h"

extern void lcd_init();
extern void lcd_cls(u8 screen);
extern void lcd_disp_number(u8 screen,u8 page,u8 col,u8 mun);
void lcd_write_char(u8 x,u8 y,u8 c);
extern void lcd_write_string(u8 x,u8 y,char* ptr);
void main(void){
	lcd_init();
	lcd_cls(0);
	lcd_write_string(0,0,"Call From: Bed 3");

	while(true);
}