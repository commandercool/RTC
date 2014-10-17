/*
 * rs485adapter.h
 *
 *  Created on: Oct 17, 2014
 *      Author: erohin
 */
#ifndef RS485ADAPTER_H_
#define RS485ADAPTER_H_
#define RS232_MODE              0
#define RS485_2WIRE_MODE        1
#define RS422_MODE              2
#define RS485_4WIRE_MODE        3
#define NOT_SET_MODE			4

#include	<fcntl.h>
#include 	<unistd.h>
#include	<sys/ioctl.h>
#include 	<linux/serial.h>

struct serial_struct DEF_RS485B9600;

int adapter_open_dev (const char* file, int flag);
int adapter_close_dev (int fd);
int adapter_get_serial(int fd, struct serial_struct* serinfo);
int adapter_set_serial(int fd, struct serial_struct* serinfo);

#endif /* RS485ADAPTER_H_ */
