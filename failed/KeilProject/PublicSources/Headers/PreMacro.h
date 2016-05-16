#ifndef __PRE_MACRO_H_
#define __PRE_MACRO_H_

#define u8   	 unsigned char
#define u16    unsigned int
#define bool	 bit
#define true   1
#define false  0
#define NULL   0
#define action void (*action)(void)

void delay_ms(u8 t);
void delay_us(u16 t);
#endif