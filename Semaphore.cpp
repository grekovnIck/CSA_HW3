//
// Created by greko on 13.12.2021.
//
#include "Semaphore.h"
#include <chrono>

using namespace std::chrono_literals;

void Semaphore::release() {
    // Синхронизирую
    std::lock_guard<decltype(mtx_)> guard(mtx_);
    // Увеличиваю количество свободных потоков на еденицу
    ++count_;
    // Освобождаю поток
    cond_semaphore.notify_one();
}

void Semaphore::acquire() {
    // Синхронизирую
    std::unique_lock<decltype(mtx_)> guard(mtx_);
    // Если значение свободных потоков нет
    while (count_ == 0) {
        // Жду пока не освободиться, то есть не будет вызван метод notify_one
        cond_semaphore.wait(guard);
    }
    --count_;
}

bool Semaphore::tryAcquire() {
    // Синхронизируюсь
    std::unique_lock<std::mutex> guard(mtx_);
    auto now = std::chrono::system_clock::now();
    // Жду до тех пор, пока не пройдет 0.1 секунды или  count_ != 0
    cond_semaphore.wait_until(guard, now + 100ms,  [this]() { return count_ != 0; } );
    if (count_ > 0) {
        --count_;
        return true;
    }
    return false;
}
 Semaphore::Semaphore(int count) {
    count_ = count;
}

