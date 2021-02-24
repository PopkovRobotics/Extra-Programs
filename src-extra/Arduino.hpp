#pragma once
// Библиотеки C++
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <termios.h>
#include <sys/ioctl.h>

// Класс ArduinoCtrl реализует "общения" с Arduino
class ArduinoCtrl {
private:
	// arduino_fd - параметр типа int, сокет для общения с Arduino. 
	int arduino_fd;			
	// connection - параметр типа bool, статус подключения к Arduino 
	// (true - Arduino поделючена, false - Arduino не подключена).
	bool connection;
public:
    /*
     * Конструктор класса, в котором подключаемся к Arduino
     * arduino_port - параметр типа char*, порт, к которому подключена Arduino
     */
	ArduinoCtrl(const char* arduino_port);
	/* 
 	 * Функция для отправки сообщения на Arduino.
 	 * message - констатный указатель на параметр типа char, сообщение для отправки,
 	 * size - параметр типа size_t, размер отправляемого сообщения.
 	 */
	void SendCommand(const char* message, size_t size);
	// Функция для очищения буфера общения с Arduino
	void Clean();
	// Функция для закрытия соеденения с Arduino
	void DeInit();
	// Функция, которая возвращает статус подключения к Arduino.
	bool IsConnected();
};
