//
// Created by greko on 13.12.2021.
//
#include <string>
#include <iostream>
#include "Semaphore.h"

#ifndef SMOKERS_SMOKER_H
#define SMOKERS_SMOKER_H

/// Класс процесс-курильщика
class Smoker {
public:
    /// Конструктор
    Smoker(int default_item, std::string worker_name);

    /// Метод описывающий процесс курения
    void smoking();

    /// Перечисления необходимых объектов для курения
    enum TypeItem {
        TOBACCO = 1,
        PAPER = 2,
        MATCHES = 3
    };

    /// Метод проверяет сможет ли пользователь скрутить сигарету
    bool canCreateCigarette(TypeItem first_item, TypeItem second_item);

private:
    /// Предмет которым по дефолту владеет курильщик
    TypeItem default_item_;
    /// Имя курильщика
    std::string worker_name_;
};

#endif //SMOKERS_SMOKER_H
