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
 * [key_scan 反线法扫描键盘]
 * @return  [按键的坐标]
 */
u8 key_scan( void )
{
    u8 x, y, key, tmp,i; 
		u8 num = 0;
    tmp = 0x0f; 
    P1 = tmp;                   //P1口：4列送0000、4行送1111；
    if (P1 != tmp)              //1判断是否有按键按下；
    {
        delay_ms(10);            //延时10毫秒消抖动；
        P1 = tmp;               //P1口：列送0000、行送1111；
        if (P1 != tmp)          //2次判断是否有按键按下；
        {
            x = P1 & tmp;      //取按下矩阵键盘的行坐标
            tmp = ~tmp;       //按位取反，线反转使用；
            P1 = tmp;          //线反转P1口：4列送高电平、4行送低电平；
            y = P1 & tmp;      //取按下矩阵键盘的列坐标
            key = x | y;        //行坐标x、列坐标y 进行或运算组合在一起。
            while(P1 != tmp);  //按键释放检测语句
            P1 = key;           //用流水灯显示当前的P1口状态
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