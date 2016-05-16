#ifndef __DS1302_H_
#define __DS1302_H_

typedef struct __SysTime__
{
    u8 second;
    u8 minute;
    u8 hour;
    u8 week;
    u8 day;
    u8 month;
    u8  year;

} SysTime;	//定义的时间类型


void ds_init();
void ds_get_time(SysTime *Time);


#endif