#include "RentalManager.h"
#include <iostream>
using namespace std;

RentalManager::RentalManager(NotificationSubject* n) : notifier(n) {
    inventory = &BookInventory::getInstance();
    waitingMgr = &WaitingListManager::getInstance();
}

void RentalManager::rentBook(User* user, Book* book) {
    int bookId = book->getId();

    if (user->hasRented(bookId)) {
        cout << "이미 대여 중인 도서입니다." << endl;
        return;
    }

    if (!inventory->isAvailable(bookId)) {
        cout << "재고가 없습니다. 메뉴에서 '도서 예약'을 이용해주세요." << endl;
        return;
    }

    if (inventory->decreaseStock(bookId)) {
        book->rent();
        user->addRentedBook(bookId);
        user->removeReservedBook(bookId);  // 예약 목록에서 제거
        notifier->notify(user->getName() + "님이 '" + book->getTitle() + "'을(를) 대여했습니다.");
        cout << "현재 재고: " << inventory->getStock(bookId) << "권" << endl;
    }
}

void RentalManager::reserveBook(User* user, Book* book) {
    int bookId = book->getId();

    if (user->hasRented(bookId)) {
        cout << "이미 대여 중인 도서입니다." << endl;
        return;
    }

    if (user->hasReserved(bookId)) {
        cout << "이미 예약 중인 도서입니다." << endl;
        return;
    }

    if (inventory->isAvailable(bookId)) {
        cout << "재고가 있습니다. '도서 대여'를 이용해주세요." << endl;
        return;
    }

    waitingMgr->addToWaitingList(bookId, user->getName());
    user->addReservedBook(bookId);
    cout << user->getName() + "님이 '" + book->getTitle() + "' 예약 대기 등록되었습니다." << endl;
    cout << "현재 대기 인원: " << waitingMgr->getWaitingCount(bookId) << "명" << endl;
}

void RentalManager::returnBook(User* user, Book* book) {
    int bookId = book->getId();

    if (!user->hasRented(bookId)) {
        cout << "이 도서는 회원님이 대여한 도서가 아닙니다." << endl;
        return;
    }

    if (!book->rented()) {
        cout << "이 도서는 대여 상태가 아닙니다." << endl;
        return;
    }

    book->giveBack();
    user->removeRentedBook(bookId);
    inventory->increaseStock(bookId);

    notifier->notify(user->getName() + "님이 '" + book->getTitle() + "'을(를) 반납했습니다.");

    if (waitingMgr->hasWaitingUser(bookId)) {
        string nextUser = waitingMgr->getNextWaitingUser(bookId);
        notifier->notify("[우선 예약 알림] " + nextUser + "님, '" + book->getTitle() + "' 재고가 생겼습니다!");
        cout << "대기자 " << nextUser << "님에게 우선권이 부여되었습니다." << endl;
    }

    cout << "현재 재고: " << inventory->getStock(bookId) << "권" << endl;
}