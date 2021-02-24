#include "Arduino.hpp"

// Функции класса ArduinoCtrl
/*
 * Конструктор класса, в котором подключаемся к Arduino
 * arduino_port - параметр типа char*, порт, к которому подключена Arduino
 */
ArduinoCtrl::ArduinoCtrl(const char* arduino_port) {
	arduino_fd = -1;
	// Получаем порт, к которому подключена Arduino
	// Открываем соединение с Arduino
	arduino_fd = open(arduino_port, O_RDWR | O_NOCTTY | O_NDELAY);
	if (arduino_fd < 0) {
        printf("Can't open serial port.");
		connection = false;
		return;
	}
	// Задаём параметры для "общения" с Arduino
	struct termios options;                     
	tcgetattr(arduino_fd, &options);	
	// Скорость отправки/чтения данных (115200 бод)							
	cfsetispeed(&options, B115200);
	cfsetospeed(&options, B115200);
	options.c_cflag &= ~PARENB;              
	options.c_cflag &= ~CSTOPB;    	// 1 стоп бит    
	// Режим: 8 бит         
	options.c_cflag &= ~CSIZE;              
	options.c_cflag |= CS8;                 
	options.c_cflag |= (CLOCAL | CREAD);
	// Устаналиваем параметры для "общения" с Arduino
	tcsetattr(arduino_fd, TCSANOW, &options);
	tcflush(arduino_fd, TCIOFLUSH);
	connection = true;
	return;
}
/* 
 * Функция для отправки сообщения на Arduino.
 * message - констатный параметр типа char*, сообщение для отправки,
 * size - параметр типа size_t, размер отправляемого сообщения.
 */
void ArduinoCtrl::SendCommand(const char* message, size_t size) {
	// Отправляет команду на Arduino
	int bytes = write(arduino_fd, message, size);
    // Если данные отправились не польностью, то выводим ошибку
	if (bytes < (int)size) 
        printf("Arduino sending data error.");
	ioctl(arduino_fd, TCSBRK, 1);
	return;
}
// Функция для очищения буфера общения с Arduino
void ArduinoCtrl::Clean() {
	// Очищаем буфер общения с Arduino, посредством считывания 
    // всех данных из буфера
	char data;
    while(true)
		if(read(arduino_fd, &data, 1) <= 0) break;
}
// Функция для закрытия соеденения с Arduino
void ArduinoCtrl::DeInit() {
	// Отключаемся от Arduino, если Arduino подключена
	if (connection)
		connection = close(connection) == 0 ? true : false;
	return;
}
// Функция, которая возвращает статус подключения к Arduino.
bool ArduinoCtrl::IsConnected() {
	return connection;
}
