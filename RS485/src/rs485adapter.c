/*
 * rs485adapter.c
 *
 *  Created on: Oct 17, 2014
 *      Author: erohin
 */
#include "rs485adapter.h"

struct serial_struct DEF_RS485B9600 = {.type = 4, .line = 1, .port = 1, .irq = 0,
		.flags = 0, .xmit_fifo_size = 1024, .custom_divisor = 0, .baud_base = 9600,
		.close_delay = 0, .io_type = '\0', .reserved_char = "", .hub6 = 0,
		.closing_wait = 61440, .closing_wait2 = 0, .iomem_base = 0x0, .iomem_reg_shift = 0,
		.port_high = 0, .iomap_base = 0};

struct serial_struct DEF_RS485B115200 = {.type = 4, .line = 1, .port = 1, .irq = 0,
		.flags = 0, .xmit_fifo_size = 1024, .custom_divisor = 0, .baud_base = 115200,
		.close_delay = 0, .io_type = '\0', .reserved_char = "", .hub6 = 0,
		.closing_wait = 61440, .closing_wait2 = 0, .iomem_base = 0x0, .iomem_reg_shift = 0,
		.port_high = 0, .iomap_base = 0};

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

int adapter_write(int fd, const void* msg, ssize_t len){
	return write(fd, msg, len);
}

int adapter_read(int fd, void* buf, ssize_t len){
	return read(fd, buf, len);
}
