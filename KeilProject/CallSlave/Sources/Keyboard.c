#include <reg51.h>
#include "../PublicSources/Headers/PreMacro.h"
#include "./Headers/Keyboard.h"

u8 key_table[16] = {
    0xee,0xde,0xbe,0x7e,
    0xed,0xdd,0xbd,0x7d,
    0xeb,0xdb,0xbb,0x7b,
    0xe7,0xd7,0xb7,0x77

};
/**
 * [key_scan ���߷�ɨ�����]
 * @return  [����������]
 */
u8 key_scan( void )
{
    u8 x, y, key, tmp,i; 
		u8 num = 0;
    tmp = 0x0f; 
    P1 = tmp;                   //P1�ڣ�4����0000��4����1111��
    if (P1 != tmp)              //1�ж��Ƿ��а������£�
    {
        delay_ms(10);            //��ʱ10������������
        P1 = tmp;               //P1�ڣ�����0000������1111��
        if (P1 != tmp)          //2���ж��Ƿ��а������£�
        {
            x = P1 & tmp;      //ȡ���¾�����̵�������
            tmp = ~tmp;       //��λȡ�����߷�תʹ�ã�
            P1 = tmp;          //�߷�תP1�ڣ�4���͸ߵ�ƽ��4���͵͵�ƽ��
            y = P1 & tmp;      //ȡ���¾�����̵�������
            key = x | y;        //������x��������y ���л����������һ��
            while(P1 != tmp);  //�����ͷż�����
            P1 = key;           //����ˮ����ʾ��ǰ��P1��״̬
            for(i = 0;i<16;++i){
                if(key_table[i] == key){
                    num = i+1;
                    break;
                }
            }
        }
    }
    return num;
}