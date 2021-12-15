//
// Created by greko on 13.12.2021.
//
#include "Smoker.h"
#include "MyUtility.h"

Smoker::Smoker(int default_item, std::string worker_name) {
    switch (default_item) {
        case 1:
            default_item_ = TOBACCO;
            break;
        case 2:
            default_item_ = PAPER;
            break;
        default:
            default_item_ = MATCHES;
            break;
    }
    worker_name_ = worker_name;
}

void Smoker::smoking() {
    MyUtility::writeCurrentStatus(MyUtility::LIGHT_BORDER_LINE, "");
    MyUtility::writeCurrentStatus(MyUtility::PROGRAMME_STATUS, "Process locked");
    std::string message = worker_name_ + " is smoking";
    MyUtility::writeCurrentStatus(MyUtility::PROGRAMME_STATUS, message);
    MyUtility::writeCurrentStatus(MyUtility::PROGRAMME_STATUS, "Process unlocked");
    MyUtility::writeCurrentStatus(MyUtility::LIGHT_BORDER_LINE, "");
}

bool Smoker::canCreateCigarette(TypeItem first_item, TypeItem second_item) {
    return default_item_ != first_item && default_item_ != second_item;
}
