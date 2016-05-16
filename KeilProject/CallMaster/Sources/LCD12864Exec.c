#include "../PublicSources/Headers/PreMacro.h"
#include "./Headers/LCD12864.h"
#include "./Headers/LCD12864Exec.h"

#define REQUEST  "Request:"

u8 buf_itostr[5] = {NULL};
u8 buf_maker[MAX_SIZE] = {NULL};
u8 buf_show[4] = {NULL};

u8 page_all = 0;
u8 page_cur = 0;
u8 end_point = 0;

void show_page(void);
void show_data(u8 start, u8 end);
void show_update(void);

extern u8	call_data[SERIAL_CHACHE_SIZE];
extern u8 call_cmd[SERIAL_CHACHE_SIZE];




void call_del_all(void)
{
    u8 i = 0;
    for(i = 0; i < end_point; ++i)
    {
        del_array_elm( buf_maker, i, MAX_SIZE );
    }
    end_point = 0;
    show_update();
}

void call_del_end(void)
{
    if(end_point > 0)
    {
        del_array_elm( buf_maker, --end_point, MAX_SIZE );
        show_update();
    }

}


void call_add_end(void)
{
    buf_maker[end_point++] = call_data[1];
    show_update();
}

void show_update(void)
{
    u8 start = 0, diff = 0;
    if(end_point >= 4)
    {
        diff = end_point % 4;
        start = end_point - ( diff ? diff : 4);
    }
    page_all = page_cur = (end_point - 1) / 4 + 1;
    show_data(start, end_point);
}


void page_up(void)
{
    u8 start, end;
    if(page_cur <= 1)
    {
        return;
    }
    --page_cur;
    start = (page_cur - 1) * 4;
    end = start + 4;
    show_data(start, end);
}

void page_down(void)
{
    u8 start, end;
    if(page_cur == page_all)
        return;
    ++page_cur;
    start = (page_cur - 1) * 4;
    end = end_point ;

    show_data(start, end);
}


void show_data(u8 start, u8 end)
{
    u8 i = 0;
    if(end >= MAX_SIZE || end < start  )
        return;
    for(i = 0; i < end - start; ++i)
    {
        buf_show[i] = buf_maker[start + i];
    }
    lcd_cls(0);
    for(i = 0; i < end - start; ++i)
    {
        itostr(buf_show[i], buf_itostr);
        lcd_write_string(i, 0, REQUEST);
        lcd_write_string(i, 8, buf_itostr);
    }
    show_page();
}

void show_page(void)
{
    itostr(page_cur, buf_itostr);
    lcd_write_string(3, 13, buf_itostr);
    lcd_write_string(3, 14, "/");
    itostr(page_all, buf_itostr);
    lcd_write_string(3, 15, buf_itostr);
}
