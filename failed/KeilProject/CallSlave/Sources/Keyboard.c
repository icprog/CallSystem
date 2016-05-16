#include <reg51.h>
#include "../PublicSources/Headers/PreMacro.h"


/**
 * [key_scan 按键扫描]
 * @return  [按键值]
 */
u8 key_scan( void )
{
	static u8	num	= 0;
	static u8	temp	= 0;
	P1	= 0xfe;                 /* 初始化P1口，检测键盘第一行 */
	temp	= P1;
	temp	= temp & 0xf0;          /* 检测高四位。 */
	while ( temp != 0xf0 )
	{
		delay_ms( 5 );          /* 消除抖动。 */
		temp	= P1;
		temp	= temp & 0xf0;  /* 检测高四位。 */
		while ( temp != 0xf0 )
		{
			temp = P1;
			switch ( temp )
			{
			case 0xee: num	= 1; break;
			case 0xde: num	= 2; break;
			case 0xbe: num	= 3; break;
			case 0x7e: num	= 4; break;
			}
			while ( temp != 0xf0 )          /* 这就是还处于按住不放， */
			{
				temp	= P1;           /* 如果松开了按键， */
				temp	= temp & 0xf0;  /* 与后的值将会和0xf0相等。从而跳出while循环 */
			}
		}
	}

	P1	= 0xfd;                                 /* 初始化P1口，检测键盘第2行 */
	temp	= P1;
	temp	= temp & 0xf0;                          /* 检测高四位。 */
	while ( temp != 0xf0 )
	{
		delay_ms( 5 );
		temp	= P1;
		temp	= temp & 0xf0;                  /* 检测高四位。 */
		while ( temp != 0xf0 )
		{
			temp = P1;
			switch ( temp )
			{
			case 0xed: num	= 5; break;
			case 0xdd: num	= 6; break;
			case 0xbd: num	= 7; break;
			case 0x7d: num	= 8; break;
			}
			while ( temp != 0xf0 )          /* 这就是还处于按住不放， */
			{
				temp	= P1;           /* 如果松开了按键， */
				temp	= temp & 0xf0;  /* 与后的值将会和0xf0相等。从而跳出while循环 */
			}
		}
	}

	P1	= 0xfb;                                 /* 初始化P1口，检测键盘第3行 */
	temp	= P1;
	temp	= temp & 0xf0;                          /* 检测高四位。 */
	while ( temp != 0xf0 )
	{
		delay_ms( 5 );
		temp	= P1;
		temp	= temp & 0xf0;                  /* 检测高四位。 */
		while ( temp != 0xf0 )
		{
			temp = P1;                      /* ```````````` */
			switch ( temp )
			{
			case 0xeb: num	= 9; break;
			case 0xdb: num	= 10; break;
			case 0xbb: num	= 11; break;
			case 0x7b: num	= 12; break;
			}
			while ( temp != 0xf0 )          /* 这就是还处于按住不放， */
			{
				temp	= P1;           /* 如果松开了按键， */
				temp	= temp & 0xf0;  /* 与后的值将会和0xf0相等。从而跳出while循环 */
			}
		}
	}

	P1	= 0xf7;                                 /* 初始化P1口，检测键盘第4行 */
	temp	= P1;
	temp	= temp & 0xf0;                          /* 检测高四位。 */
	while ( temp != 0xf0 )
	{
		delay_ms( 5 );
		temp	= P1;
		temp	= temp & 0xf0;                  /* 检测高四位。 */
		while ( temp != 0xf0 )
		{
			temp = P1;                      /* ```````````` */
			switch ( temp )
			{
			case 0xe7: num	= 13; break;
			case 0xd7: num	= 14; break;
			case 0xb7: num	= 15; break;
			case 0x77: num	= 16; break;
			}
			while ( temp != 0xf0 )          /* 这就是还处于按住不放， */
			{
				temp	= P1;           /* 如果松开了按键， */
				temp	= temp & 0xf0;  /*按位与后的值将会和0xf0相等。从而跳出while循环 */
			}
		}
	}
	return(num);
}


