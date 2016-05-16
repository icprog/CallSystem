#include "./Headers/PreMacro.h"
void delay_ms(u8 t){
	u8 i = 110;
	while(t--){
		while(i--);
	}
}

void delay_us(u16 t){
	while(t--);
}