//
// Created by greko on 13.12.2021.
//
#include <condition_variable>
#include <mutex>
#include <future>


#ifndef SMOKERS_SEMAPHORE_H
#define SMOKERS_SEMAPHORE_H

/// Класс описывает поведение семафора
class Semaphore {
public:
    /// Конструктор
    explicit Semaphore(int count);

    /// Метод проверяет можно ли начать начать действие
    bool tryAcquire();

    /// Занимает поток
    void acquire();

    /// Освобождает поток
    void release();

private:
    /// Максимально количество потоков
    int count_;
    std::mutex mtx_;
    std::condition_variable cond_semaphore;
};
#endif //SMOKERS_SEMAPHORE_H
