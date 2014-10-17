/*
 * rs485adapter.c
 *
 *  Created on: Oct 17, 2014
 *      Author: erohin
 */
#include "rs485adapter.h"

int adapter_open_dev (const char* file, int flag){
	return open(file, flag);
}

int adapter_close_dev (int fd){
	return close(fd);
}

int adapter_get_serial(int fd, struct serial_struct* serinfo) {
	return ioctl(fd, TIOCGSERIAL, serinfo);
}

int adapter_set_serial(int fd, struct serial_struct* serinfo){
	return ioctl(fd, TIOCSSERIAL, serinfo);
}
