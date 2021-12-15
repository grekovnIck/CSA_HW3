#include <iostream>
#include <string>
#include <vector>
#include "MyUtility.h"
#include "Smoker.h"
#include "Process.h"
#include "Mediator.h"

const std::string INFO = "First argument must be <-w> or <-r> (writing values by user, random values)\n"
                         "The argument is one number and three strings with the names of smokers.\n"
                         "The number must be a non-negative integer (if number is float, it will be convert to int)"
                         ", less than 1,000,000 and more\n"
                         "Lines must not be empty and no more than 20 characters in length";

const std::string INSTRUCTION1 = "Enter two values: <first element> <second element>\n"
                                 "\t\t[1] - tobacco\n"
                                 "\t\t[2] - paper\n"
                                 "\t\t[3] - matches";



/// Считывание числа из входного параметра
/// Возвращает считываемое число или код статус, если строку нельзя конвертировать в число
/// \param argv массив char
/// \return
int readNumber(const char* argv) {
    try {
        int num = std::stoi(argv);
        if (num < 0 || num > 1000000) {
            return -2;
        }
        return num;
    } catch (std::invalid_argument ex){
        return -1;
    } catch (std::out_of_range ex){
        return -1;
    }
}

/// Печатает две строки
/// 1-ая строка - это сообщение указывающее на ошибку
/// 2-ая строка - это информация о формате ввода
/// \param message
void combineMessage(const std::string& message) {
    MyUtility::writeCurrentStatus(MyUtility::ERROR_STATUS, message);
    MyUtility::writeCurrentStatus(MyUtility::INFO, INFO);
}

/// Точка входа в программу
/// \param argc кол-во входных параметров
/// \param argv сообщение
/// \return
int main(int argc, char *argv[]) {
    int count_pair, first_item = 0, second_item = 0;
    std::vector<std::pair<Smoker::TypeItem, Smoker::TypeItem>> items;

    /// Проверка кол-ва параметров
    if (argc != 6) {
        combineMessage("Invalid format input parameter");
        return 0;
    }

    count_pair = readNumber(argv[2]);

    /// Обработка статус кодов возвращаемых readNumber
    if (count_pair == -1) {
        combineMessage("Parameter is not a number");
        return 0;
    } else if (count_pair == -2) {
        combineMessage("Number out of range");
        return 0;
    }

    Smoker* first_smoker = new Smoker(Smoker::TOBACCO, argv[3]);
    Smoker* second_smoker = new Smoker(Smoker::PAPER, argv[4]);
    Smoker* third_smoker = new Smoker(Smoker::MATCHES, argv[5]);

    /// Если пользователь выбрал режим самостоятельного ввода
    if (argv[1][1] == 'w') {
        MyUtility::writeCurrentStatus(MyUtility::INFO, INSTRUCTION1);
        for (int i = 0; i < count_pair; ++i) {
            bool is_success_read = false;
            /// Считывание пары предметов до тех пор, пока пользователь не совершит корректный ввод
            while (!is_success_read) {
                std::cin >> first_item >> second_item;
                if (std::cin.fail()) {
                    MyUtility::writeCurrentStatus(MyUtility::ERROR_STATUS,
                                                  "Incorrect character entered, please try again");
                    std::cin.clear();
                    std::cin.ignore(32767, '\n');
                } else if (!(first_item >= 1 && first_item <= 3) || !(second_item >= 1 && second_item <= 3)) {
                    MyUtility::writeCurrentStatus(MyUtility::ERROR_STATUS, "Number out of range, "
                                                                           "please try again");
                    std::cin.clear();
                    std::cin.ignore(32767, '\n');
                } else if (first_item == second_item){
                    MyUtility::writeCurrentStatus(MyUtility::ERROR_STATUS, "Numbers must be different,"
                                                                           " please try again");
                    std::cin.clear();
                    std::cin.ignore(32767, '\n');
                } else {
                    is_success_read = true;
                }
            }
            /// Добывавление в массив
            items.emplace_back(static_cast<Smoker::TypeItem>(first_item), static_cast<Smoker::TypeItem>(second_item));
        }
        /// Режим генерации ПО случайных значений
    } else if (argv[1][1] == 'r') {
        for (int i = 0; i < count_pair; ++i) {
            first_item = MyUtility::getRandomNumber();
            second_item = MyUtility::getRandomNumber(first_item);
            items.emplace_back(static_cast<Smoker::TypeItem>(first_item), static_cast<Smoker::TypeItem>(second_item));
        }
    } else {
        combineMessage("Incorrect argument parameter");
        return 0;
    }

    auto* mediator = new Mediator(items);

    auto* process = new Process(mediator, first_smoker, second_smoker, third_smoker);
    process->processing();


    return 0;
}


