//
// Created by greko on 14.12.2021.
//
#include <thread>
#include <condition_variable>
#include <semaphore>
#include "Semaphore.h"
#include "Smoker.h"
#include "MyUtility.h"
#include "Mediator.h"



#ifndef SMOKERS_PROCESS_H
#define SMOKERS_PROCESS_H

/// Класс организующий все процессы
class Process {
public:
    /// Конструктор
    explicit Process(Mediator* mediator, Smoker* first_smoker, Smoker* second_smoker, Smoker* third_smoker);

    ~Process();

    /// Метод который запускает потоки
    void processing();
private:
    Semaphore* semaphore_;
    Mediator* mediator_;
    Smoker* first_smoker_{};
    Smoker* second_smoker_{};
    Smoker* third_smoker_{};
};
#endif //SMOKERS_PROCESS_H
