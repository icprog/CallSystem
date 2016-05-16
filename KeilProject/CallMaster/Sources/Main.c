#include "../PublicSources/Headers/PreMacro.h"
#include "../PublicSources/Headers/Serial.h"
#include "./Headers/LCD12864.h"
#include "./Headers/Keyboard.h"
#include "./Headers/LCD12864Exec.h"
#include <reg52.h>


extern u8	call_data[SERIAL_CHACHE_SIZE];
extern u8	call_cmd[SERIAL_CHACHE_SIZE];
extern bool occur_inrpt;

u8 COM_ADDR = MASTER_ADDR;
u8 NEXT_ADDR = DISP_ADDR;


void exec_up(void);
void exec_down(void);
void exec_cls(void);
void exec_del(void);
void exec_action(u8 action_key);

void main(void)
{
    u8 action_key = 0;
    serial_init();
    lcd_init();
    lcd_cls(0);
    serial_init();

    while(true)
    {
        if(cmd_is_valid() == true)
        {
            switch (call_cmd[2])
            {
            case CALL_ADD:
                call_add_end();
                break;
            default:
                break;
            }
        }
        action_key = check_action();
        if(action_key != ACTION_NULL)
        {
            exec_action(action_key);
        }
    }
}


void exec_action(u8 action_key)
{
    switch(action_key)
    {
    case ACTION_UP:
        exec_up();
        break;
    case ACTION_DOWN:
        exec_down();
        break;
    case ACTION_CLS:
        exec_cls();
        break;
    case ACTION_DEL:
        exec_del();
    default:
        break;
    }
}



void exec_up(void)
{
    page_up();
}

void exec_down(void)
{
    page_down();
}

void exec_cls(void)
{
    serial_send(DISP_ADDR, CALL_CLS, CALL_CLS);
    call_del_all();
}
void exec_del(void)
{
    call_del_end();
    serial_send(DISP_ADDR, CALL_DEL, CALL_DEL);
}
