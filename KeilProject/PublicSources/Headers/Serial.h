#ifndef __SERIAL_H_
#define __SERIAL_H_


#define MASTER_ADDR 0x01
#define DISP_ADDR 0x02
#define SLAVE_ADDR 0x03

void serial_init(void);

void serial_send(u8 addr, u8 cmd, u8 dat);
bool cmd_is_valid(void);

#endif