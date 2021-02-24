#pragma once
// Библиотеки C++
#include <string>
#include <memory>
#include <fcntl.h>
#include <errno.h>
#include <stdlib.h>
#include <assert.h>
#include <unistd.h>
#include <string.h>
#include <stdexcept>
#include <sys/stat.h>
#include <sys/time.h>
#include <sys/mman.h>
#include <sys/types.h>
#include <sys/ioctl.h>
#include <linux/videodev2.h>

// Структура, которая хранит буфер для кадра
struct buffer {
    // Буфер
    void   *data;
    // Размер буфера в байтах
    size_t  size;
};


// Класс реализует чтение видео потока с вебкамеры
class Webcam {
private:
    // Порт, к которому подключена вебкамера
    std::string device;
    // Дескриптор вебкамеры
    int fd;
    // Массив, который хранит BGR изображение
    unsigned char* data;
    int*** frame_array;
    // Массив с буферами, которые хранят кадр с вебкамеры в формате YUYV
    struct buffer* buffers;
    // Количество буферов, которые хранят кадр с вебкамеры
    unsigned int n_buffers;
    // Разрешение кадра
    size_t xres,            // Ширина кадра
            yres;           // Высота кадра
    // Количество байтов на одну строку кадра
    size_t stride;

    // Функция инициализирует массив для хранения кадра
    void init_mmap();
    // Функция открывает вебкамеру для дальнейшей работы
    void open_device();
    // Функция закрывает вебкамеру
    void close_device();
    // Функция устаналивает параметры считывания кадров с вебкамеры
    void init_device();
    // Функция освобождает память занятую буферами
    void uninit_device();
    // Функция запускает вебкамеру для считывания кадров с вебкамеры
    void start_capturing();
    // Функция завершает работу с вебкамерой
    void stop_capturing();
    // Функция считывает кадр с вебкамеры
    bool read_frame();

public:
    /*
     * Конструктор класса.
     * device - константный параметр  типа std::string, порт, к которому подключена вебкамера,
     * width - параметр типа int, ширина кадров, считанных с вебкамеры,
     * height - параметр типа int, высота кадров, считанных с вебкамеры.
     */
    Webcam(const std::string& device = "/dev/video0",
           int width = 640, int height = 480);

    // Дескриптор класса
    ~Webcam();

    /*
     * Захватывает и возвращает кадр с вебкамеры.
     * Функция возвращает кадр в формате BGR (Blue-Green-Red).
     * И имеет размер (ширина * высота * 3).
     * Ширина и высота указывается в конструкторе класса.
     */
    int*** frame(int timeout = 1);

};




