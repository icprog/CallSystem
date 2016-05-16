#include "../PublicSources/Headers/PreMacro.h"
#include "./Headers/DS1302.h"
#include <reg52.h>

sbit  ACC0 = ACC ^ 0;
sbit  ACC7 = ACC ^ 7;
sbit RST = P3 ^ 2;
sbit SCLK = P3 ^ 3;
sbit IO = P3 ^ 4;

#define AM(X)	X
#define PM(X)	(X+12)            	  
#define DS_SECOND	0x80              
#define DS_MINUTE	0x82
#define DS_HOUR		0x84
#define DS_WEEK		0x8A
#define DS_DAY		0x86
#define DS_MONTH	0x88
#define DS_YEAR		0x8C

/**
 * [ds_write_byte 给DS1302写一字节]
 * @param dat [待写入的字节]
 */
void ds_write_byte(u8 dat) 	
{
    u8 i;
    ACC = dat;
    for(i = 8; i > 0; i--)
    {
        IO = ACC0;           
        SCLK = 1;
        SCLK = 0;
        ACC = ACC >> 1;
    }
}

/**
 * [ds_read_byte 从DS1302中读取一字节]
 * @return  [读取的数据]
 */
u8 ds_read_byte(void) 	
{
    u8 i;
    for(i = 8; i > 0; i--)
    {
        ACC = ACC >> 1;         		
        ACC7 = IO;
        SCLK = 1;
        SCLK = 0;
    }
    return(ACC);
}

/**
 * [ds_write 给DS1302的某地址写入数据]
 * @param addr  [地址]
 * @param dat   [数据]
 */
void ds_write(u8 addr, u8 dat)	
{
    RST = 0;
    SCLK = 0;
    RST = 1;
    ds_write_byte(addr);       	
    ds_write_byte(dat);       	
    SCLK = 1;
    RST = 0;
}

/**
 * [ds_read 从DS1302的的某个地址中读取一字节数据]
 * @param  addr [地址]
 * @return      [读取的数据]
 */
u8 ds_read(u8 addr)	//读取DS1302某地址的数据
{
    u8 dat;
    RST = 0;
    SCLK = 0;
    RST = 1;
    ds_write_byte(addr | 0x01);      // 地址，命令
    dat = ds_read_byte();         // 读1Byte数据
    SCLK = 1;
    RST = 0;
    return(dat);
}

/**
 * [ds_get_time [获取DS1302中的时间]
 * @param Time  [时间]
 */
void ds_get_time(SysTime *Time)  //获取时钟芯片的时钟数据到自定义的结构型数组
{
    u8 read_value;
    read_value = ds_read(DS_SECOND);
    Time->second = ((read_value & 0x70) >> 4) * 10 + (read_value & 0x0F);
    read_value = ds_read(DS_MINUTE);
    Time->minute = ((read_value & 0x70) >> 4) * 10 + (read_value & 0x0F);
    read_value = ds_read(DS_HOUR);
    Time->hour = ((read_value & 0x70) >> 4) * 10 + (read_value & 0x0F);
    read_value = ds_read(DS_DAY);
    Time->day = ((read_value & 0x70) >> 4) * 10 + (read_value & 0x0F);
    read_value = ds_read(DS_WEEK);
    Time->week = ((read_value & 0x70) >> 4) * 10 + (read_value & 0x0F);
    read_value = ds_read(DS_MONTH);
    Time->month = ((read_value & 0x70) >> 4) * 10 + (read_value & 0x0F);
    read_value = ds_read(DS_YEAR);
    Time->year = ((read_value & 0x70) >> 4) * 10 + (read_value & 0x0F);
}


/**
 * [ds_init DS1302初始化]
 */
void ds_init(void)   
{
    u8 second = ds_read(DS_SECOND);
    if(second & 0x80)	    
    {
        ds_write(0x8e, 0x00); 
        ds_write(0x8c, 0x07); 
        ds_write(0x88, 0x07);
        ds_write(0x86, 0x25);
        ds_write(0x8a, 0x07);
        ds_write(0x84, 0x23);
        ds_write(0x82, 0x59);
        ds_write(0x80, 0x55);
        ds_write(0x8e, 0x80); 
    }

}
