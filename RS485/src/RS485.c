/*
 * Working with MOXA UPort 1150I via rs485adapter
 *
 *  Created on: Oct 17, 2014
 *      Author: erohin
 */
#include	<stdio.h>
#include	<stdlib.h>
//#include 	<rs485adapter.h>
#include 	"rs485adapter.h"

int	main(int argc, char *argv[])
{
	if (argc != 2){
		perror("Wrong number of arguments\n"
				"Usage: ./RS485 <dev>\n"
				"Where <dev> - device file (e.g. '/dev/ttyUSB0')");
		exit(1);
	}
	int	fd = adapter_open_dev(argv[1], O_RDWR);
	if (fd < 0) {
		perror("Error while opening device");
		exit(1);
	}

	printf("Setting serial to port 1 (rs485)...\n");

	if (adapter_set_serial_def(fd) < 0) {
		perror("Cannot set serial info");
		exit(1);
	} else {
		printf("Serial is set to rs485 mode\n");
	}

	printf("Setting baud rate...\n");

	if (adapter_set_baud_rate(fd, B9600) < 0){
		perror("Cannot set baud for device");
		exit(1);
	} else {
		printf("Serial baud is set to 9600\n");
	}

	printf("Sending message...\n");

	char* msg = "Hello rs485!";
	printf("<< %s\n", msg);

	int result = adapter_write(fd, msg, 12);
	if (result > 0){
		printf("Message was sent\n");
	} else {
		printf("Error while sending message\n");
	}

	printf("Reading message...\n");

	char income_msg[20] = {'\0'};
	adapter_read_msg(fd, income_msg, 11);

	printf(">> %s\n", income_msg);

	result = adapter_close_dev(fd);
	exit(result);
}
