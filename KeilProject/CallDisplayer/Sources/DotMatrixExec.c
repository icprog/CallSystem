#include "../PublicSources/Headers/PreMacro.h"
#include "./Headers/DotMatrix.h"
#include "./Headers/DotMatrixExec.h"
#include "./Headers/DS1302.h"
#include <reg52.h>


extern bool occur_inrpt;
extern u8	call_data[SERIAL_CHACHE_SIZE];
extern u8	call_cmd[SERIAL_CHACHE_SIZE];
extern bool cmd_is_valid(void);

void update_buf( void );
void deal_with_cmd(u8 cmd);

//呼叫者缓存
u8	buf_maker[MAX_SIZE] = { NULL };
//int to string 缓存
u8	buf_itostr[5] = { NULL };
//显示呼叫者缓存
u8	buf_show_maker[8] = { 'A', 'I', 'D', ':', NULL };
//显示时间缓存
u8  buf_show_time[8] = {NULL};
//呼叫者缓存末尾指针 呼叫者的数量 + 1
u8	end_point	= 0;
//显示标志 用与切换 TIME 与 MAKER
bool	show_flag	= SHOW_TIME;

/**
 * [show_maker 显示呼叫]
 */
void show_maker()
{
    if ( cmd_is_valid() == true )
    {
        deal_with_cmd(call_cmd[2]);
    }
    if ( end_point == 0 )
    {
        show_flag = SHOW_TIME;
    }


    dm_write_string( 1, buf_show_maker );
}

/**
 * [update_buf 更新相关缓存]
 */
void update_buf( void )
{
    u8	 *ptr		= buf_itostr;
    u8 i = 0;
    itostr( buf_maker[end_point - 1], buf_itostr );
    for ( i = 4; i < 8; ++i )
    {
        buf_show_maker[i] = NULL;
    }
    i = 4;
    while ( *ptr != NULL )
    {
        buf_show_maker[i] = buf_itostr[i - 4];
        ++i;
        ptr++;
    }
}

/**
 * [call_add_end 添加一数据到缓存末尾]
 */
void call_add_end(void)
{
    buf_maker[end_point++] = call_data[1];
    update_buf();
}

/**
 * [call_del_end 删除缓存末尾数据]
 */
void call_del_end(void)
{
    del_array_elm(buf_maker, --end_point, MAX_SIZE);
	  update_buf();
}

/**
 * [call_del_all 清空缓存]
 */
void call_del_all(void)
{
    u8 i = 0;
    for(i = 0; i < end_point; ++i)
    {
        del_array_elm(buf_maker, i, MAX_SIZE);
    }
    end_point = 0;
    P0 = end_point;
    update_buf();
}

SysTime time;

/**
 * [show_time 显示时间]
 */
void show_time()
{
    if(cmd_is_valid() == true)
    {
        show_flag = SHOW_MAKER;
        deal_with_cmd(call_cmd[2]);
        return;
    }
    ds_get_time(&time);
    buf_show_time[0] = time.hour / 10 + '0';
    buf_show_time[1] = time.hour % 10 + '0';
    buf_show_time[2] = ':';
    buf_show_time[3] = time.minute / 10 + '0';
    buf_show_time[4] = time.minute % 10 + '0';
    buf_show_time[5] = ':';
    buf_show_time[6] = time.second / 10 + '0';
    buf_show_time[7] = time.second % 10 + '0';
    dm_write_string(1, buf_show_time);
}

/**
 * [deal_with_cmd 命令处理]
 * @param cmd [待处理的命令]
 */
void deal_with_cmd(u8 cmd)
{
    switch(cmd)
    {
    case CALL_ADD:
        call_add_end();
        break;
    case CALL_DEL:
        call_del_end();
        break;
    case CALL_CLS:
        call_del_all();
        break;
    default:
        break;
    }
}