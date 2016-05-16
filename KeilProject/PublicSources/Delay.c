#include "./Headers/PreMacro.h"

/**
 * [delay_ms 毫秒延时]
 * @param t [毫秒数]
 */
void delay_ms(u8 t)
{
    u8 i = 110;
    while(t--)
    {
        while(i--);
    }
}

/**
 * [delay_us 微秒延时]
 * @param t [微秒数]
 */
void delay_us(u16 t)
{
    while(t--);
}

/**
 * [itostr int转成string (u8的数组)]
 * @param source [待转换的数据]
 * @param dest   [转换后的数据]
 */
void itostr(u16 source, u8 *dest)
{
    u16 tmp = source;
    u8 bits = 0, i;
    for(i = 0; i < 5; i++)
    {
        dest[i] = NULL;
    }
    do
    {
        ++bits;
        tmp /= 10;
    }
    while(tmp != 0);


    for (i = bits; i > 0; i--)
    {
        dest[i - 1] = (source % 10) + 0x30;
        source /= 10;
    }

}

/**
 * [del_array_elm 删除数组中的一元素]
 * @param ptr       [数组指针]
 * @param del_index [删除的下标]
 * @param all_num   [数组的元素个数]
 */
void del_array_elm(u8 *ptr, u8 del_index, u8 all_num)
{
    u8 i = 0, tmp = 0;
    if(del_index >= all_num)
        return;
    for(i = del_index; i < all_num - 1; ++i)
    {
        ptr[i] = ptr[i + 1];
    }
    ptr[all_num - 1] = NULL;
}