/*
 * Working with MOXA UPort 1150I via rs485adapter
 *
 *  Created on: Oct 17, 2014
 *      Author: erohin
 */
#include	<stdio.h>
#include	<stdlib.h>
#include	<fcntl.h>
#include	<sys/ioctl.h>
#include 	<linux/serial.h>
#include "rs485adapter.h"

#define RS232_MODE              0
#define RS485_2WIRE_MODE        1
#define RS422_MODE              2
#define RS485_4WIRE_MODE        3
#define NOT_SET_MODE			4

int	main(int argc, char *argv[])
{
	int	fd;
	struct serial_struct serinfo;

	fd = adapter_open_dev(argv[1], O_RDWR);

	if (fd < 0) {
		perror("Error while opening device");
		exit(1);
	}

	if (adapter_get_serial(fd, &serinfo) < 0) {
		perror("Cannot get serial info");
	    exit(1);
	}

	printf("Setting serial to port 1 (rs485)...\n");

	serinfo.port = RS485_2WIRE_MODE;

	if (adapter_set_serial(fd, &serinfo) < 0) {
		perror("Cannot set serial info");
		exit(1);
	} else {
		printf("Serial is set to rs485 mode\n");
	}

	adapter_close_dev(fd);
	exit(0);
}
