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
/**
* Функция открытия файла устройства. Функция открывает файл заданного устройства с параметрами, задаваемыми флагом
* \param file имя файла устройства
* \param flag параметры открытия файла
* \return дескриптор открытого устройства
*/
int adapter_open_dev (const char* file, int flag);

/**
* Функция закрытия файла устройства. Функция закрывает файл заданного устройства
* \param fd дескриптор устройства
* \return положительное значение при успешном выполнении операции, иначе -1
*/
int adapter_close_dev (int fd);

/**
* Функция задания предустановленной конфигурации для открытого устройства. Под 
* предустановленной конфигурацией понимается: режим устройства - RS485; скорость 
* передачи данных: 9600Kbs
* \see adapter_set_serial
* \param fd дескриптор устройства
* \return положительное значение при успешном выполнении операции, иначе -1
*/
int adapter_set_serial_def(int fd);

/**
* Получение конфигурации устройства.
* \param fd дескриптор устройства
* \param serinfo структура с параметрами устройства
* \return положительное значение при успешном выполнении операции, иначе -1
*/
int adapter_get_serial(int fd, struct serial_struct* serinfo);

/**
* Функция задания предустановленной конфигурации для открытого устройства.
* \param fd дескриптор устройства
* \param serinfo структура с параметрами устройства
* \return положительное значение при успешном выполнении операции, иначе -1
*/
int adapter_set_serial(int fd, struct serial_struct* serinfo);

/**
* Функция задания скорости передачи данных.
* \param fd дескриптор устройства
* \param boud_const константа скорости передачи
* \return положительное значение при успешном выполнении операции, иначе -1
*/
int adapter_set_baud_rate(int fd, unsigned int boud_const);

/**
* Функция записи данных в устройство. Функция производит последовательную запись 
* данных, находящихся по указателю в устройсво
* \param fd дескриптор устройства
* \param msg указатель на облать памяти с данными
* \param len размер области памяти с данными
* \return положительное значение при успешном выполнении операции, иначе -1
*/
int adapter_write(int fd, const void* msg, ssize_t len);

/**
* Функция чтения буфера данных из устройства. Функция производит последовательное чтение 
* данных из устройства в буфер памяти, находящийся по указателю
* \param fd дескриптор устройства
* \param buf указатель на область памяти для записи данных
* \param len размер области памяти
* \return факртический размер считанного буфера
*/
int adapter_read_buf(int fd, void* buf, ssize_t len);

/**
* Функция чтения сообщения из устройства. Cчитывает полное сообщение указанной длины
* \see adapter_read_buf 
* \param fd дескриптор устройства
* \param msg указатель на область памяти для записи данных
* \param full_len полный размер оожидаемого сообщения
* \return положительное значение при успешном выполнении операции, иначе -1
*/
int adapter_read_msg(int fd, char* msg, ssize_t full_len);

#endif /* RS485ADAPTER_H_ */
