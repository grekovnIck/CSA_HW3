//
// Created by greko on 13.12.2021.
//

#include "Mediator.h"
#include "MyUtility.h"

Mediator::Mediator(std::vector<std::pair<Smoker::TypeItem, Smoker::TypeItem>> &items) {
    items_ = items;
    current_pair_ = 0;
}

void Mediator::ReadItems() {
    MyUtility::writeCurrentStatus(MyUtility::LIGHT_BORDER_LINE, "");
    MyUtility::writeCurrentStatus(MyUtility::PROGRAMME_STATUS, "Process locked\nThe mediator put hands under the stand"
                                                               "and grab two items");
    first_item_ = items_[current_pair_].first;
    second_item_ = items_[current_pair_].second;
    ++current_pair_;
    MyUtility::writeCurrentStatus(MyUtility::PROGRAMME_STATUS, "Process unlocked");
    MyUtility::writeCurrentStatus(MyUtility::LIGHT_BORDER_LINE, "");
}

bool Mediator::canRead() {
    return current_pair_ < items_.size();
}


std::pair<Smoker::TypeItem, Smoker::TypeItem> Mediator::getItems() {
    //mtx.lock();
    MyUtility::writeCurrentStatus(MyUtility::LIGHT_BORDER_LINE, "");
    MyUtility::writeCurrentStatus(MyUtility::PROGRAMME_STATUS, "Process locked\nThe mediator "
                                                               "put items on the stand");
    std::pair<Smoker::TypeItem, Smoker::TypeItem> items(first_item_, second_item_);
    MyUtility::writeCurrentStatus(MyUtility::PROGRAMME_STATUS, "Process unlocked");
    MyUtility::writeCurrentStatus(MyUtility::LIGHT_BORDER_LINE, "");
    //mtx.unlock();
    return items;
}
