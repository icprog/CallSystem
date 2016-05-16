#include "./Headers/PreMacro.h"
#include "./Headers/Serial.h"
#include <reg52.h>

u8  call_data[SERIAL_CHACHE_SIZE]   = { NULL };
u8  call_cmd[SERIAL_CHACHE_SIZE] = { NULL };

extern u8 COM_ADDR;
extern u8 NEXT_ADDR;

//中断发生标志[命令以及数据传输完成才置位[true]
bool	occur_inrpt		= false;

/**
 * [serial_send_byte 发送一字节]
 * @param dat [待发送的字节]
 */
void serial_send_byte( u8 dat )
{
    SBUF = dat;
    while ( !TI )
        ;
    TI = 0;
}


/**
 * [serial_init 串口初始化]
 */
void serial_init( void )
{
    TMOD	= 0x20;       /* 定器1，选择工作方式2 */
    TH1	= 0xFD;           /* 波特率 9600，晶振11.0592 */
    TL1	= 0xFD;           /* 波特率=(2^SMOD /32 ) X (fosc/12(256-TH1) ) */
    TR1	= 1;

    SM0	= 1;
    SM1	= 1;              /* 串行工作方式 方式三 11位 第九位作为数据/命令判断位 */
    REN	= 1;              /* 允许/禁止串行接收控制位 */
    ES	= 1;
    EA	= 1;
}

/**
 * [serial_send_string 发送字符串]
 * @param ptr [字符串首地址]
 * @param num [字符串长度]
 */
void serial_send_string( u8 *ptr, u8 num )
{
    u8 i = 0;
    TB8 = 0;
    serial_send_byte(SERIAL_START);
    for ( i = 0; i < num; ++i )
    {
        serial_send_byte( *ptr++ );
    }
    serial_send_byte(SERIAL_END);

}


/**
 * [serial_send 串口发送命令以及数据]
 * @param addr [接收端的地址]
 * @param cmd  [待发送的命令]
 * @param dat  [待发送的数据]
 */
void serial_send(u8 addr, u8 cmd, u8 dat)
{
    TB8 = 1;
    serial_send_byte(SERIAL_START);
    serial_send_byte( addr );
    serial_send_byte( cmd );
    serial_send_byte(SERIAL_END);

    TB8 = 0;
    serial_send_byte(SERIAL_START);
    serial_send_byte(dat);
    serial_send_byte(SERIAL_END);
}

/**
 * [serial_inrpt 串口中断函数]
 */
void serial_inrpt( void ) interrupt 4 using 1
{
    static u8	di		= 0;
    static u8 ci  = 0;
    u8		j		= 0;
    ES		= 0;
    RI		= 0;
    /* 传递数据 */
    if ( RB8 == 0 )
    {
        if ( di >= SERIAL_CHACHE_SIZE )
        {
            di = 0;
            return;
        }
        call_data[di++] = SBUF;

        if( SERIAL_END == SBUF)
        {
            di = 0;

            occur_inrpt = true;
        }      
    }
    else   /*传递命令*/
    {
        if ( ci >= SERIAL_CHACHE_SIZE )
        {
            ci = 0;
            return ;
        }
        call_cmd[ci++] = SBUF;
        if(SERIAL_END == SBUF)
        {
            ci = 0;
        }
    }
    ES = 1;
}

/**
 * [cmd_is_valid 检测命令是否可用，若不可用则转发给NEXT_ADDR]
 * @return  [是否可用]
 */
bool cmd_is_valid(void)
{
    if(occur_inrpt == true)
    {
			P0 = 0;
        occur_inrpt  = false;
        if(call_cmd[0] != SERIAL_START || call_data[0] != SERIAL_START)
            return false;

        if(call_cmd[1] == COM_ADDR)
        {
					
            return true;
        }
        else
        {
			     serial_send(NEXT_ADDR, call_cmd[2], call_data[1]);
            return false;
        }
    }
    return false;
}



