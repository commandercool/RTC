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
#include 	<termios.h>
#include 	<string.h>

struct serial_struct DEF_RS485;

int adapter_open_dev (const char* file, int flag);
int adapter_close_dev (int fd);
int adapter_set_serial_def(int fd);
int adapter_get_serial(int fd, struct serial_struct* serinfo);
int adapter_set_serial(int fd, struct serial_struct* serinfo);
int adapter_set_baud_rate(int fd, unsigned int boud_const);
int adapter_write(int fd, const void* msg, ssize_t len);
int adapter_read_buf(int fd, void* buf, ssize_t len);
int adapter_read_msg(int fd, char* msg, ssize_t full_len);

#endif /* RS485ADAPTER_H_ */
