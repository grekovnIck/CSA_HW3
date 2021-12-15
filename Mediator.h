//
// Created by greko on 13.12.2021.
//
#include "Smoker.h"
#include <iostream>
#include <vector>
//#include "Process.h"

#ifndef SMOKERS_MEDIATOR_H
#define SMOKERS_MEDIATOR_H

/// Класс процесс-координатор
class Mediator {
public:
    /// Конструктор
    explicit Mediator(std::vector<std::pair<Smoker::TypeItem, Smoker::TypeItem>> &items);

    /// Присваивает переменным first_item_, second_item_ новые значения
    void ReadItems();

    /// Возвращает последние элементы в items_
    std::pair<Smoker::TypeItem, Smoker::TypeItem> getItems();

    /// Проверяет если в списке еще предметы
    bool canRead();

private:
    /// Список пар элементов
    std::vector<std::pair<Smoker::TypeItem, Smoker::TypeItem>> items_;
    /// Элементы которые "процесс менеджер готов отдать процесс-курильщикам"
    Smoker::TypeItem first_item_;
    Smoker::TypeItem second_item_;
    /// Индекс пар элементов
    int current_pair_;
};

#endif //SMOKERS_MEDIATOR_H
