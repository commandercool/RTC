/*
 ============================================================================
 Name        : RS485.c
 Author      : commandercool
 Version     :
 Copyright   : Your copyright notice
 Description : Hello World in C, Ansi-style
 ============================================================================
 */

#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <sys/ioctl.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>
#include <asm/ioctls.h>
#include <errno.h>
#include <termios.h>
#include <linux/serial.h>

// Control struct for setting the port in 485 mode
struct rs485_ctrl {
  unsigned short rts_on_send;
  unsigned short rts_after_sent;
  unsigned int  delay_rts_before_send;
  unsigned short enabled;
};

// his struct is only needed if we would like to write with ioctl()
struct rs485_wrt {
  unsigned short outc_size;
  unsigned char *outc;
};

int main(void) {
	char dev[] = {"/dev/ttyUSB1"};
	struct rs485_ctrl ctrl485;
	int status;
	int  baudrate = B9600;
	struct termios ti;
	struct termios ti_prev;
	int port = open(dev, O_RDWR);//|O_NONBLOCK);

	if (port < 0) {
		printf("ERROR! Failed to open %s\n", dev);
	    return -1;
	} else {
		printf("SUCCESS: open device\n");
	}

	struct serial_rs485 rs485conf;
	/* Enable RS485 mode: */
	rs485conf.flags |= SER_RS485_ENABLED;

	/* Set logical level for RTS pin equal to 1 when sending: */
	rs485conf.flags |= SER_RS485_RTS_ON_SEND;
	/* or, set logical level for RTS pin equal to 0 when sending: */
	rs485conf.flags &= ~(SER_RS485_RTS_ON_SEND);

	/* Set logical level for RTS pin equal to 1 after sending: */
	rs485conf.flags |= SER_RS485_RTS_AFTER_SEND;
	/* or, set logical level for RTS pin equal to 0 after sending: */
	rs485conf.flags &= ~(SER_RS485_RTS_AFTER_SEND);

	/* Set rts delay before send, if needed: */
	rs485conf.delay_rts_before_send = 0;

	/* Set rts delay after send, if needed: */
	rs485conf.delay_rts_after_send = 0;

	/* Set this flag if you want to receive data even whilst sending data */
	//rs485conf.flags |= SER_RS485_RX_DURING_TX;

	  status = ioctl(port, TIOCSRS485, &rs485conf);
	  if (status) {
	    printf("ERROR PORT 1! TIOCSERSETRS485 failed %i", status);
	    return -1;
	  } else {
		  printf("SUCCESS: setting rs485 mode on\n");
		  return -1;
	  }

//	  tcgetattr(port, &ti_prev);    // Save the previous serial config
//	  tcgetattr(port, &ti);         // Read the previous serial config
//	  cfsetospeed(&ti,baudrate);  // Set the TX baud rate
//	  cfsetispeed(&ti,baudrate);  // Set the RX baud rate
//
//	  cfmakeraw(&ti);
//	  tcsetattr(port, TCSANOW, &ti);  // Set the new serial config

	return EXIT_SUCCESS;
}
