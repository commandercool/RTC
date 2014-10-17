/*
 * Working with MOXA UPort 1150I via rs485adapter
 *
 *  Created on: Oct 17, 2014
 *      Author: erohin
 */
#include	<stdio.h>
#include	<stdlib.h>
#include "rs485adapter.h"

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
