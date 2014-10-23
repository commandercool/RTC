/*
 * Working with MOXA UPort 1150I via rs485adapter
 *
 *  Created on: Oct 17, 2014
 *      Author: erohin
 */
#include	<stdio.h>
#include	<stdlib.h>
#include 	"rs485adapter.h"

int	main(int argc, char *argv[])
{
	int	fd = adapter_open_dev(argv[1], O_RDWR);
	if (fd < 0) {
		perror("Error while opening device");
		exit(1);
	}

	printf("Setting serial to port 1 (rs485)...\n");

	if (adapter_set_serial(fd, &DEF_RS485B9600) < 0) {
		perror("Cannot set serial info");
		exit(1);
	} else {
		printf("Serial is set to rs485 mode\n");
	}

	printf("Sending message...\n");
	char* msg = "Hello rs485!";
	int result = adapter_write(fd, msg, 12);
	if (result > 0){
		printf("Message was sent\n");
	} else {
		printf("error while sending message\n");
	}

	printf("reading message...\n");
	char buf = 'a';
	printf("after buf %c\n", buf);
	while (1) {
		result = adapter_read(fd, &buf, 1);
			if (result > 0){
				printf(">> %c\n", buf);
			} else {
				printf("error while reading message\n");
			}
	}

	adapter_close_dev(fd);
	exit(0);
}
