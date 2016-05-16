#include <reg52.h>
#include <intrins.h>
#include "../PublicSources/Headers/PreMacro.h"


extern void hc595_out(void);
extern hc595_write_byte(u8 byte);
extern void dm_write_char(char date,u8 site);
sbit EN_54 =P2^3;
void main(){

	EN_54 = 0;

	while(1){	
 //dm_write_char('1',1);
		 dm_write_char('2',2);
		 dm_write_char('3',3);

	}
}