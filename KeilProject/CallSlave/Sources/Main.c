#include <reg52.h>
#include "../PublicSources/Headers/PreMacro.h"
#include "../PublicSources/Headers/Serial.h"
#include "./Headers/Keyboard.h"

u8  COM_ADDR = SLAVE_ADDR;
u8  NEXT_ADDR = MASTER_ADDR;

void main(void)
{
    u8 i = 0,maker = 0;
    serial_init();

    while(1)
    {
        maker = key_scan();
        if(maker != 0)
        {
            P0 = maker;
            serial_send(MASTER_ADDR, CALL_ADD, maker);
					  serial_send(DISP_ADDR, CALL_ADD, maker);
            maker = 0;
        }
				if(cmd_is_valid()){
					// do something
				}
    }
}

