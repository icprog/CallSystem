#include "../PublicSources/Headers/PreMacro.h"
#include "./Headers/LcdCharacters.h"
#include "./Headers/LCD12864.h"
#include <reg52.h>

#define ON	0
#define OFF	1

sbit	LCD_CS_LEFT	= P2 ^ 0;       /* LCD����Ļ */
sbit	LCD_CS_RIGHT	= P2 ^ 1;       /* LCD����Ļ */
sbit	LCD_RS		= P2 ^ 2;       /* LCD���ݡ�ָ��Ĵ��� */
sbit	LCD_RW		= P2 ^ 3;       /* LCD����д���� */
sbit	LCD_EN		= P2 ^ 4;       /* LCDʹ���źţ��½�����Ч */

/*ѡ������ */
typedef enum _SCREEN
{
    ALL = 0, LEFT, RIGHT
} SCREEN;


/**
 * [lcd_write_cmd LCDд������]
 * @param cmd [����]
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
 * [lcd_write_byte LCDд��һ�ֽ�����]
 * @param byte [����]
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
 * [select_screen LCDѡ��]
 * @param screen [ѡ������]
 */
void select_screen( SCREEN screen )
{
    switch ( screen )
    {
    case ALL:       /*ѡ��ȫ�� */
        LCD_CS_LEFT	= ON;
        LCD_CS_RIGHT	= ON;
        break;
    case LEFT:      /*ѡ������ */
        LCD_CS_LEFT	= ON;
        LCD_CS_RIGHT	= OFF;
        break;
    case RIGHT:     /*ѡ������ */
        LCD_CS_LEFT	= OFF;
        LCD_CS_RIGHT	= ON;
        break;
    default:        /* �ر���Ļ */
        LCD_CS_LEFT	= OFF;
        LCD_CS_RIGHT	= OFF;
        break;
    }
}





/**
 * [lcd_cls LCD��������]
 * @param screen [ѡ������]
 */
void lcd_cls( SCREEN screen )
{
    int x, y;
    select_screen( screen );        /* screen:0-ѡ��ȫ����1-ѡ���������2-ѡ���Ұ��� */
    for ( x = 0xb8; x < 0xc0; x++ ) /* ��0xb8-0xbf,��8ҳ */
    {
        lcd_write_cmd( x );
        lcd_write_cmd( 0x40 );  /* �еĳ�ʼ��ַ��0x40 */
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
        lcd_write_cmd( 0x40 );  /* �еĳ�ʼ��ַ��0x40 */

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
 * [lcd_init LCD��ʼ��]
 */
void lcd_init()
{
    lcd_write_cmd( 0x3f );  /* LCD����ʾ */
    lcd_write_cmd( 0xc0 );  /* LCD�г�ʼ��ַ����64�� */
    lcd_write_cmd( 0xb8 );  /* LCDҳ��ʼ��ַ����8ҳ */
    lcd_write_cmd( 0x40 );  /* LCD�г�ʼ��ַ����64�� */
}


/**
 * [lcd_set_coords LCD������ʾ����]
 * @param row [������]
 * @param col [������]
 */
void lcd_set_coords( u8 row, u8 col )
{
    lcd_write_cmd( 0xb8 + row );
    lcd_write_cmd( 0x40 + (col * 8) );
}


/**
 * [lcd_write_char LCDд��һ���ֽ�]
 * @param row [������]
 * @param col [������]
 * @param c   [��д����ֽ�]
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
 * [lcd_write_string LCDд�����ַ���]
 * @param row [������]
 * @param col [������]
 * @param ptr [��д����ַ���]
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


