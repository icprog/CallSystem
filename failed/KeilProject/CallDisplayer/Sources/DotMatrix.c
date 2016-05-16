#include <reg52.h>
#include "../PublicSources/Headers/PreMacro.h"
#include "./Headers/DotMatrix.h"
#include "./Headers/DotMatrixMod.h"

#define ON 0
#define OFF 1

sbit	SH_CP		= P2 ^ 0;
sbit	DS	   	= P2 ^ 1;
sbit	ST_CP		= P2 ^ 2;
sbit	ROW_EN	= P2 ^ 3;


void delay(u16 z)    
{
 u8 i,j;
 for(i=z;i>0;i--)
   for(j=4;j>0;j--);
}

void hc595_out( void )
{
	ST_CP = 0;
	delay(1);
	ST_CP = 1;
	delay(1);
}


void hc595_write_byte( u8 byte )
{
	u8 tmp;
	for ( tmp = 0; tmp < 8; tmp++ )
	{
		if ( byte & 0x80 )
		{
			DS = 1;
		}else{
			DS = 0;
		}
		SH_CP = 0;
		delay(1);
		SH_CP = 1;
		delay(1);
		byte <<= 1;
	}
}


void dm_write_char (char date,u8 site){
	u8 i = 0,j=0;
	if(site > 7)
		return;
	P1 &= 0x0f;
	P1 |= (site<<=5);
	for(i=0;i<16;i++){
		P1 &=0xf0;
		P1 |= i;
		ROW_EN = OFF;
		P0 = dm_ascii[date - 32][i];
		//	delay_us(10);
		ROW_EN = ON;
		delay_us(10);
	}

}

//void dm_write_char(char date,u8 site)
//{
//	u8 i = 0,j=0;
//	if(site>7)
//		return;

//	for ( i = 0; i < 16; i++ )
//	{
//	  P1 = i;
//		for(j=site;j<8;j++){
//				hc595_write_byte( 0x00 );
//		}
//		hc595_write_byte( dm_ascii[date - 32][i] );
//		for(j=0;j<site -1 ;++j){
//				hc595_write_byte( 0x00 );
//		}
//		ROW_EN = OFF;
//		hc595_out();
//		ROW_EN = ON;
//		delay_us(200);
//	}
//}






