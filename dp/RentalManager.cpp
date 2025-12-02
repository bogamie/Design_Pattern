#include "RentalManager.h"
#include "DiscountDecorator.h"
#include <iostream>
using namespace std;

RentalManager::RentalManager(NotificationSubject* n) : notifier(n) {
    inventory = &BookInventory::getInstance();
    waitingMgr = &WaitingListManager::getInstance();
}

void RentalManager::rentBook(User* user, Book* book) {
    int bookId = book->getId();

    if (!inventory->isAvailable(bookId)) {
        cout << "재고가 없습니다. 예약하시려면 예약 메뉴를 이용하세요." << endl;
        return;
    }

    if (inventory->decreaseStock(bookId)) {
        book->rent();
        notifier->notify(user->getName() + " 님이 '" + book->getTitle() + "' 책을 대여했습니다.");
        cout << "남은 재고: " << inventory->getStock(bookId) << endl;
    }
}

void RentalManager::reserveBook(User* user, Book* book) {
    int bookId = book->getId();

    if (inventory->isAvailable(bookId)) {
        cout << "재고가 있습니다. 대여 메뉴를 이용하세요." << endl;
        return;
    }

    waitingMgr->addToWaitingList(bookId, user->getName());
    cout << user->getName() << " 님이 '" << book->getTitle() << "' 을(를) 예약했습니다." << endl;
    cout << "현재 대기 인원: " << waitingMgr->getWaitingCount(bookId) << endl;
}

void RentalManager::returnBook(User* user, Book* book) {
    int bookId = book->getId();

    if (!book->rented()) {
        cout << "이 책은 현재 대여 중이 아닙니다." << endl;
        return;
    }

    book->giveBack();
    inventory->increaseStock(bookId);

    notifier->notify(user->getName() + " 님이 '" + book->getTitle() + "' 책을 반납했습니다.");

    if (waitingMgr->hasWaitingUser(bookId)) {
        string nextUser = waitingMgr->getNextWaitingUser(bookId);
        notifier->notify("예약 우선 알림: " + nextUser + " 님, '" + book->getTitle() + "' 책 대여 가능합니다.");
        cout << "예약 대기자: " << nextUser << endl;
    }

    cout << "남은 재고: " << inventory->getStock(bookId) << endl;
}
