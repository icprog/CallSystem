#include <reg52.h>
#include "../PublicSources/Headers/PreMacro.h"
#include "./Headers/Keyboard.h"



sbit KEY_UP = P1 ^ 0;
sbit KEY_DOWN = P1 ^ 1;
sbit KEY_DEL = P1 ^ 2;
sbit KEY_DO  = P1 ^ 3;

u8 check_action()
{
    if(KEY_UP == 0)
    {
        delay_ms(5);
        while(!KEY_UP);
        return ACTION_UP;
    }
    else if(KEY_DOWN == 0)
    {
        delay_ms(5);
        while(!KEY_DOWN);
        return ACTION_DOWN;
    }
    else if(KEY_DEL == 0)
    {
        delay_ms(5);
        while(!KEY_DEL);
        return ACTION_CLS;
    }
    else if(KEY_DO == 0)
    {
        delay_ms(5);
        while(!KEY_DO);
        return ACTION_DEL;
    }
    else
    {
        return ACTION_NULL;
    }

}