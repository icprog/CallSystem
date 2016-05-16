#include "../PublicSources/Headers/PreMacro.h"
#include "./Headers/LcdCharacters.h"
#include "./Headers/LCD12864.h"
#include <reg52.h>

#define ON	0
#define OFF	1

sbit	LCD_CS_LEFT	= P2 ^ 0;       /* LCD右屏幕 */
sbit	LCD_CS_RIGHT	= P2 ^ 1;       /* LCD左屏幕 */
sbit	LCD_RS		= P2 ^ 2;       /* LCD数据、指令寄存器 */
sbit	LCD_RW		= P2 ^ 3;       /* LCD读、写操作 */
sbit	LCD_EN		= P2 ^ 4;       /* LCD使能信号，下降沿有效 */

/*选屏参数 */
typedef enum _SCREEN
{
    ALL = 0, LEFT, RIGHT
} SCREEN;


/**
 * [lcd_write_cmd LCD写入命令]
 * @param cmd [命令]
 */
void lcd_write_cmd( u8 cmd )
{
    LCD_RW	= 0;
    LCD_RS	= 0;
    LCD_EN	= 1;
    P0	= cmd;
    LCD_EN	= 0;
}


/**
 * [lcd_write_byte LCD写入一字节数据]
 * @param byte [数据]
 */
void lcd_write_byte( u8 byte )
{
    LCD_RW	= 0;
    LCD_RS	= 1;
    LCD_EN	= 1;
    P0	= byte;
    LCD_EN	= 0;
}


/**
 * [select_screen LCD选屏]
 * @param screen [选屏参数]
 */
void select_screen( SCREEN screen )
{
    switch ( screen )
    {
    case ALL:       /*选择全屏 */
        LCD_CS_LEFT	= ON;
        LCD_CS_RIGHT	= ON;
        break;
    case LEFT:      /*选择左屏 */
        LCD_CS_LEFT	= ON;
        LCD_CS_RIGHT	= OFF;
        break;
    case RIGHT:     /*选择右屏 */
        LCD_CS_LEFT	= OFF;
        LCD_CS_RIGHT	= ON;
        break;
    default:        /* 关闭屏幕 */
        LCD_CS_LEFT	= OFF;
        LCD_CS_RIGHT	= OFF;
        break;
    }
}





/**
 * [lcd_cls LCD清屏操作]
 * @param screen [选屏参数]
 */
void lcd_cls( SCREEN screen )
{
    int x, y;
    select_screen( screen );        /* screen:0-选择全屏，1-选择左半屏，2-选择右半屏 */
    for ( x = 0xb8; x < 0xc0; x++ ) /* 从0xb8-0xbf,共8页 */
    {
        lcd_write_cmd( x );
        lcd_write_cmd( 0x40 );  /* 列的初始地址是0x40 */
        for ( y = 0; y < 64; y++ )
        {
            lcd_write_byte( 0x00 );
        }
    }
}

void lcd_clean_row(u8 row)
{
    u8 col, x;
    row *= 2;
    row += 0xb8;
    for(x = row; x <= row + 1; ++x)
    {
        lcd_write_cmd( x );
        lcd_write_cmd( 0x40 );  /* 列的初始地址是0x40 */

        for(col = 0; col < 64; ++col)
        {
            lcd_write_byte(0x00);
        }
    }
}

void lcd_row_up()
{

}


/**
 * [lcd_init LCD初始化]
 */
void lcd_init()
{
    lcd_write_cmd( 0x3f );  /* LCD开显示 */
    lcd_write_cmd( 0xc0 );  /* LCD行初始地址，共64行 */
    lcd_write_cmd( 0xb8 );  /* LCD页初始地址，共8页 */
    lcd_write_cmd( 0x40 );  /* LCD列初始地址，共64列 */
}


/**
 * [lcd_set_coords LCD设置显示坐标]
 * @param row [横坐标]
 * @param col [纵坐标]
 */
void lcd_set_coords( u8 row, u8 col )
{
    lcd_write_cmd( 0xb8 + row );
    lcd_write_cmd( 0x40 + (col * 8) );
}


/**
 * [lcd_write_char LCD写入一个字节]
 * @param row [横坐标]
 * @param col [纵坐标]
 * @param c   [待写入的字节]
 */
void lcd_write_char( u8 row, u8 col, u8 c )
{
    u8 i, calc_col;
    calc_col = col;

    if ( col <= 7 )
        select_screen( LEFT );
    else
    {
        calc_col = col - 8;
        select_screen( RIGHT );
    }
    lcd_set_coords( row, calc_col );

    c -= 32;
    lcd_set_coords( row, calc_col );
    for ( i = 0; i < 16; i++ )
    {
        if ( i == 8 )
        {
            lcd_set_coords( row + 1, calc_col );
        }
        lcd_write_byte( font8x16[c][i] );
    }
}


/**
 * [lcd_write_string LCD写入以字符串]
 * @param row [横坐标]
 * @param col [纵坐标]
 * @param ptr [待写入的字符串]
 */
void lcd_write_string( u8 row, u8 col, char *ptr )
{
    row *= 2;
    while ( *ptr != NULL )
    {
        if ( col > 15 )
        {
            row	+= 2;
            col	= 0;
            if ( row > 7 )
            {
                row = 0;
            }
        }
        lcd_write_char( row, col++, *ptr );
        ++ptr;
    }
}


