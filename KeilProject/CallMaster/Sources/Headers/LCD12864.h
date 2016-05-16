#ifndef __LED_12864_H_
#define __LED_12864_H
void lcd_init();
void lcd_cls(u8 screen);
void lcd_disp_number(u8 screen, u8 page, u8 col, u8 mun);
void lcd_write_char(u8 x, u8 y, u8 c);
void lcd_write_string(u8 x, u8 y, char *ptr);
void lcd_clean_row(u8 row);

#endif