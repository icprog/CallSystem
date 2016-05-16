#include "../PublicSources/Headers/PreMacro.h"
#include "../PublicSources/Headers/Serial.h"
#include "./Headers/DotMatrix.h"
#include "./Headers/DotMatrixExec.h"
#include "./Headers/DS1302.h"

u8 COM_ADDR =  DISP_ADDR;
u8 NEXT_ADDR = SLAVE_ADDR;
u8 flash_delay = 100;

extern bool show_flag;

void main()
{
    serial_init();
    ds_init();
    while(true)
    {
        if(show_flag == SHOW_MAKER)
        {
            show_maker();
        }
        else if(show_flag == SHOW_TIME)
        {
            show_time();
        }

    }
}


