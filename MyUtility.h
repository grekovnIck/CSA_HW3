//
// Created by greko on 13.12.2021.
//
#ifndef SMOKERS_MYUTILITY_H
#define SMOKERS_MYUTILITY_H

/// Класс реализует необходимые утилиты, которые часто используются в программе
class MyUtility{
public:
    /// Перечисления, описывающие статус сообщения
    enum MessageCategory {
        PROGRAMME_STATUS,
        ERROR_STATUS,
        BORDER_LINE,
        LIGHT_BORDER_LINE,
        INFO
    };

    /// Пишет в консоль
    static void writeCurrentStatus(MessageCategory category, const std::string& message) {
        if (category == PROGRAMME_STATUS) {
            std::printf("PROGRAMME STATUS: %s \n", message.c_str());
        } else if (category == ERROR_STATUS) {
            std::printf("ERROR MESSAGE: %s \n", message.c_str());
        } else if (category == BORDER_LINE) {
            std::printf("\n================================================================================\n");
        } else if (category == LIGHT_BORDER_LINE) {
            std::printf("----------------------------------------------------------------------------------\n");
        } else if (category == INFO) {
            std::printf("INFO MESSAGE: %s \n", message.c_str());
        }
    }

    /// Генерирует рандомное значение
    static int getRandomNumber(int banned_value = 0, int min = 1, int max = 4) {
        int random_value = banned_value;
        while (random_value == banned_value) {
            random_value = min + rand() / (RAND_MAX / (max - min + 1) + 1);
        }
        return random_value;
    }
};

#endif //SMOKERS_MYUTILITY_H
