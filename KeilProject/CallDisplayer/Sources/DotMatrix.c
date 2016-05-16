#include <reg52.h>
#include "../PublicSources/Headers/PreMacro.h"
#include "./Headers/DotMatrix.h"
#include "./Headers/DotMatrixMod.h"

#define ON	0
#define OFF	1

sbit	SH_CP	= P2 ^ 0;
sbit	DS	= P2 ^ 1;
sbit	ST_CP	= P2 ^ 2;
sbit	ROW_EN	= P2 ^ 3;

//点阵动态扫描间隔
extern u8 flash_delay;

/**
 * [hc595_out 74HC595输出脉冲]
 */
void hc595_out( void )
{
    ST_CP = 0;
    ST_CP = 1;
}

/**
 * [hc595_in_byte 74H595写入数据]
 * @param byte [待写入字节]
 */
void hc595_in_byte( u8 byte )
{
    u8 tmp;
    for ( tmp = 0; tmp < 8; tmp++ )
    {
        if ( byte & 0x80 )
        {
            DS = 1;
        }
        else
        {
            DS = 0;
        }
        SH_CP = 0;
        SH_CP = 1;
        byte <<= 1;
    }
}

/**
 * [dm_write_string 点阵写入字符串]
 * @param start_pos [待写入的位置以1-8]
 * @param ptr       [待写入的数据首地址]
 */
void dm_write_string( u8 start_pos, char *ptr )
{
    u8	i		= 0, row = 0, col = 0;
    u8	char_array[8]	= { 0 };
    if(start_pos > 0  && start_pos < 9)
    {
        i = start_pos - 1;
    }
    else
    {
        return ;
    }

    ROW_EN = OFF;
    while ( *ptr != NULL )
    {
        char_array[7 - i] = *ptr - 32;
        ++i;
        if ( i >= 8 )
            break;
        ptr++;
    }
    for ( row = 0; row < 16; ++row )
    {
        P1 = row;
        for ( col = 0; col < 8; ++col )
        {
            hc595_in_byte( dm_mod[char_array[col]][row]);
        }
        ROW_EN = OFF;
        hc595_out();
        ROW_EN = ON;
        delay_us( flash_delay );
    }
}



