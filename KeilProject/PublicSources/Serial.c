#include "./Headers/PreMacro.h"
#include "./Headers/Serial.h"
#include <reg52.h>

u8  call_data[SERIAL_CHACHE_SIZE]   = { NULL };
u8  call_cmd[SERIAL_CHACHE_SIZE] = { NULL };

extern u8 COM_ADDR;
extern u8 NEXT_ADDR;

//�жϷ�����־[�����Լ����ݴ�����ɲ���λ[true]
bool	occur_inrpt		= false;

/**
 * [serial_send_byte ����һ�ֽ�]
 * @param dat [�����͵��ֽ�]
 */
void serial_send_byte( u8 dat )
{
    SBUF = dat;
    while ( !TI )
        ;
    TI = 0;
}


/**
 * [serial_init ���ڳ�ʼ��]
 */
void serial_init( void )
{
    TMOD	= 0x20;       /* ����1��ѡ������ʽ2 */
    TH1	= 0xFD;           /* ������ 9600������11.0592 */
    TL1	= 0xFD;           /* ������=(2^SMOD /32 ) X (fosc/12(256-TH1) ) */
    TR1	= 1;

    SM0	= 1;
    SM1	= 1;              /* ���й�����ʽ ��ʽ�� 11λ �ھ�λ��Ϊ����/�����ж�λ */
    REN	= 1;              /* ����/��ֹ���н��տ���λ */
    ES	= 1;
    EA	= 1;
}

/**
 * [serial_send_string �����ַ���]
 * @param ptr [�ַ����׵�ַ]
 * @param num [�ַ�������]
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
 * [serial_send ���ڷ��������Լ�����]
 * @param addr [���ն˵ĵ�ַ]
 * @param cmd  [�����͵�����]
 * @param dat  [�����͵�����]
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
 * [serial_inrpt �����жϺ���]
 */
void serial_inrpt( void ) interrupt 4 using 1
{
    static u8	di		= 0;
    static u8 ci  = 0;
    u8		j		= 0;
    ES		= 0;
    RI		= 0;
    /* �������� */
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
    else   /*��������*/
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
 * [cmd_is_valid ��������Ƿ���ã�����������ת����NEXT_ADDR]
 * @return  [�Ƿ����]
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



