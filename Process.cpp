//
// Created by greko on 14.12.2021.
//
#include "Process.h"

Process::Process(Mediator *mediator, Smoker* first_smoker, Smoker* second_smoker, Smoker* third_smoker) {
    mediator_ = mediator;
    semaphore_ = new Semaphore(1);
    first_smoker_ = first_smoker;
    second_smoker_ = second_smoker;
    third_smoker_ = third_smoker;
}

Process::~Process() {
    delete semaphore_;
    delete mediator_;
    delete first_smoker_;
    delete second_smoker_;
    delete third_smoker_;
}


/// Метод таки куда проще и меньше чем кажется, просто здесь вставлено огромное кол-во комментариев программы
/// Это сделано для лучшего мониторинга действий программы
/// По сити в этом метода вызывает три потока:
///                             1. Координатор-процесс вытягивает два предмета (инициализируется предметы)
///                             2. Координатор-процесс кладет на стол (предметы становятся известны курильщикам)
///                             3. Курильщики-процессы курят
/// А между процессами стоят семафоры, которые ждут пока действия потоки не завершат сво
void Process::processing() {
    int i = 1;
    while (mediator_->canRead()) {
        MyUtility::writeCurrentStatus(MyUtility::PROGRAMME_STATUS, "Iteration " + std::to_string(i));
        MyUtility::writeCurrentStatus(MyUtility::BORDER_LINE,"");

        MyUtility::writeCurrentStatus(MyUtility::PROGRAMME_STATUS, "Semaphore checks "
                                                                   "if mediator_take_thread new thread can be started");
        if (!semaphore_->tryAcquire()) {
            MyUtility::writeCurrentStatus(MyUtility::PROGRAMME_STATUS, "Ooh, he is busy, wait mediator_take_thread moment");
            semaphore_->acquire();
        }
        MyUtility::writeCurrentStatus(MyUtility::PROGRAMME_STATUS, "Yep, it is ready "
                                                                   "to start mediator_take_thread new thread");
        std::thread mediator_take_thread(&Mediator::ReadItems, mediator_);


        semaphore_->release();

        mediator_take_thread.join();
        MyUtility::writeCurrentStatus(MyUtility::PROGRAMME_STATUS, "Semaphore released");

        MyUtility::writeCurrentStatus(MyUtility::PROGRAMME_STATUS, "Semaphore checks "
                                                                   "if mediator_take_thread new thread can be started");
        if (!semaphore_->tryAcquire()) {
            MyUtility::writeCurrentStatus(MyUtility::PROGRAMME_STATUS, "Ooh, he is busy, wait mediator_take_thread moment");
            semaphore_->acquire();
        }
        MyUtility::writeCurrentStatus(MyUtility::PROGRAMME_STATUS, "Yep, it is ready "
                                                                   "to start mediator_take_thread new thread");
        std::pair<Smoker::TypeItem, Smoker::TypeItem> items;
        std::thread mediator_give_thread([&items, this]() { items = mediator_->getItems(); });
        mediator_give_thread.join();
        MyUtility::writeCurrentStatus(MyUtility::PROGRAMME_STATUS, "Semaphore released");
        semaphore_->release();

        MyUtility::writeCurrentStatus(MyUtility::PROGRAMME_STATUS, "Semaphore checks "
                                                                   "if mediator_take_thread new thread can be started");

        if (!semaphore_->tryAcquire()) {
            MyUtility::writeCurrentStatus(MyUtility::PROGRAMME_STATUS, "Ooh, he is busy, wait mediator_take_thread moment");
            semaphore_->acquire();
        }
        MyUtility::writeCurrentStatus(MyUtility::PROGRAMME_STATUS, "Yep, it is ready "
                                                                   "to start mediator_take_thread new thread");

        if (first_smoker_->canCreateCigarette(items.first, items.second)) {
            std::thread smoker_thread(&Smoker::smoking, first_smoker_);
            smoker_thread.join();
        } else if (second_smoker_->canCreateCigarette(items.first, items.second)) {
            std::thread smoker_thread(&Smoker::smoking, second_smoker_);
            smoker_thread.join();
        } else if (third_smoker_->canCreateCigarette(items.first, items.second)) {
            std::thread smoker_thread(&Smoker::smoking, third_smoker_);
            smoker_thread.join();
        }
        MyUtility::writeCurrentStatus(MyUtility::PROGRAMME_STATUS, "Semaphore released\n");
        semaphore_->release();
        i++;

        /// Здесь было бы правильней джоинить потоки, однако выполнение потоков будет хоть и правильным, но вывод
        /// будет не последовательным
        //mediator_take_thread.join();
        //mediator_give_thread.join();

    }
}