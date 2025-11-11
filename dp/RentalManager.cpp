#include "RentalManager.h"
#include <iostream>
using namespace std;

RentalManager::RentalManager(NotificationSubject* n) : notifier(n) {
    inventory = &BookInventory::getInstance();
    waitingMgr = &WaitingListManager::getInstance();
}

void RentalManager::rentBook(User* user, Book* book) {
    int bookId = book->getId();

    if (!inventory->isAvailable(bookId)) {
        cout << "재고가 없습니다. 예약을 원하시면 reserveBook()을 호출하세요." << endl;
        return;
    }

    if (inventory->decreaseStock(bookId)) {
        book->rent();
        notifier->notify(user->getName() + "님이 '" + book->getTitle() + "'을(를) 대여했습니다.");
        cout << "현재 재고: " << inventory->getStock(bookId) << "권" << endl;
    }
}

void RentalManager::reserveBook(User* user, Book* book) {
    int bookId = book->getId();

    if (inventory->isAvailable(bookId)) {
        cout << "재고가 있습니다. rentBook()으로 바로 대여하세요." << endl;
        return;
    }

    waitingMgr->addToWaitingList(bookId, user->getName());
    cout << user->getName() + "님이 '" + book->getTitle() + "' 예약 대기 등록되었습니다." << endl;
    cout << "현재 대기 인원: " << waitingMgr->getWaitingCount(bookId) << "명" << endl;
}

void RentalManager::returnBook(User* user, Book* book) {
    int bookId = book->getId();

    if (!book->rented()) {
        cout << "이 도서는 대여 상태가 아닙니다." << endl;
        return;
    }

    book->giveBack();
    inventory->increaseStock(bookId);

    notifier->notify(user->getName() + "님이 '" + book->getTitle() + "'을(를) 반납했습니다.");

    if (waitingMgr->hasWaitingUser(bookId)) {
        string nextUser = waitingMgr->getNextWaitingUser(bookId);
        notifier->notify("[우선 예약 알림] " + nextUser + "님, '" + book->getTitle() + "' 재고가 생겼습니다!");
        cout << "대기자 " << nextUser << "님에게 우선권이 부여되었습니다." << endl;
    }

    cout << "현재 재고: " << inventory->getStock(bookId) << "권" << endl;
}