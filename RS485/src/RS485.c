
/*
 * To set serial port interface.
 * Usage: setinterface device-node [interface-no]
 * 	  device-node	- must be /dev/ttyM0 or /dev/ttyM1
 * 	  Interface-no - following
 * 	  none - to view now setting
 * 	  0 - RS232
 * 	  1 - RS485-2WIRES
 * 	  2 - RS422
 * 	  3 - RS485-4WIRES
 *
 * History:
 * Date		Author			Comment
 * 03-28-2005	Victor Yu.		Create it.
 */
#include	<stdio.h>
#include	<stdlib.h>
#include	<fcntl.h>
#include	<sys/ioctl.h>
#include <linux/serial.h>

#define RS232_MODE              0
#define RS485_2WIRE_MODE        1
#define RS422_MODE              2
#define RS485_4WIRE_MODE        3
#define NOT_SET_MODE		4

int	main(int argc, char *argv[])
{
	int	fd;
	fd = open(argv[1], O_RDWR);

	if (fd < 0) {
		perror("Error while opening device");
		exit(1);
	}

	struct serial_struct serinfo;

	if (ioctl(fd, TIOCGSERIAL, &serinfo) < 0) {
		perror("Cannot get serial info");
	    exit(1);
	}

	if (serinfo.port != RS485_2WIRE_MODE){
		serinfo.port = RS485_2WIRE_MODE;
		if (ioctl(fd, TIOCSSERIAL, &serinfo) < 0) {
			perror("Cannot set serial info");
			exit(1);
		}
	}

	if ( fd < 0 ) {
		printf("Open device node %s fail !\n", argv[1]);
		exit(1);
	}

	close(fd);
	exit(0);
}
