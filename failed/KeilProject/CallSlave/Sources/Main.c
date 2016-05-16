#include <reg51.h>
#include "../PublicSources/Headers/PreMacro.h"

extern u8 key_scan(void);
u8 num = 0;
void main(void){
	while(1){
		P0 = key_scan();
	}
}