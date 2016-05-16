#include <reg51.h>
#include "../PublicSources/Headers/PreMacro.h"


/**
 * [key_scan ����ɨ��]
 * @return  [����ֵ]
 */
u8 key_scan( void )
{
	static u8	num	= 0;
	static u8	temp	= 0;
	P1	= 0xfe;                 /* ��ʼ��P1�ڣ������̵�һ�� */
	temp	= P1;
	temp	= temp & 0xf0;          /* ������λ�� */
	while ( temp != 0xf0 )
	{
		delay_ms( 5 );          /* ���������� */
		temp	= P1;
		temp	= temp & 0xf0;  /* ������λ�� */
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
			while ( temp != 0xf0 )          /* ����ǻ����ڰ�ס���ţ� */
			{
				temp	= P1;           /* ����ɿ��˰����� */
				temp	= temp & 0xf0;  /* ����ֵ�����0xf0��ȡ��Ӷ�����whileѭ�� */
			}
		}
	}

	P1	= 0xfd;                                 /* ��ʼ��P1�ڣ������̵�2�� */
	temp	= P1;
	temp	= temp & 0xf0;                          /* ������λ�� */
	while ( temp != 0xf0 )
	{
		delay_ms( 5 );
		temp	= P1;
		temp	= temp & 0xf0;                  /* ������λ�� */
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
			while ( temp != 0xf0 )          /* ����ǻ����ڰ�ס���ţ� */
			{
				temp	= P1;           /* ����ɿ��˰����� */
				temp	= temp & 0xf0;  /* ����ֵ�����0xf0��ȡ��Ӷ�����whileѭ�� */
			}
		}
	}

	P1	= 0xfb;                                 /* ��ʼ��P1�ڣ������̵�3�� */
	temp	= P1;
	temp	= temp & 0xf0;                          /* ������λ�� */
	while ( temp != 0xf0 )
	{
		delay_ms( 5 );
		temp	= P1;
		temp	= temp & 0xf0;                  /* ������λ�� */
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
			while ( temp != 0xf0 )          /* ����ǻ����ڰ�ס���ţ� */
			{
				temp	= P1;           /* ����ɿ��˰����� */
				temp	= temp & 0xf0;  /* ����ֵ�����0xf0��ȡ��Ӷ�����whileѭ�� */
			}
		}
	}

	P1	= 0xf7;                                 /* ��ʼ��P1�ڣ������̵�4�� */
	temp	= P1;
	temp	= temp & 0xf0;                          /* ������λ�� */
	while ( temp != 0xf0 )
	{
		delay_ms( 5 );
		temp	= P1;
		temp	= temp & 0xf0;                  /* ������λ�� */
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
			while ( temp != 0xf0 )          /* ����ǻ����ڰ�ס���ţ� */
			{
				temp	= P1;           /* ����ɿ��˰����� */
				temp	= temp & 0xf0;  /*��λ����ֵ�����0xf0��ȡ��Ӷ�����whileѭ�� */
			}
		}
	}
	return(num);
}


