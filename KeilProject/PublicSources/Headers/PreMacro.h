#ifndef __PRE_MACRO_H_
#define __PRE_MACRO_H_

#define u8   	 unsigned char
#define u16    unsigned int
#define bool	 bit
#define true   1
#define false  0
#define NULL   0

#define SERIAL_START	0xff
#define SERIAL_END	0xfe
#define CALL_ADD 0xfc
#define CALL_CLS 0xfb
#define CALL_NULL 0x00
#define CALL_DEL 0xfa

#define MAX_SIZE 20
#define SERIAL_CHACHE_SIZE	8

typedef void (*action)(void);


void itostr(u16 source, u8 *dest);
void del_array_elm(u8 *ptr, u8 del_index, u8 all_num);
void delay_ms(u8 t);
void delay_us(u16 t);

#endif