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
        cout << "No book left. If you want reservation, call reserveBook()." << endl;
        return;
    }

    if (inventory->decreaseStock(bookId)) {
        book->rent();
        notifier->notify(user->getName() + " has borrowed '" + book->getTitle() + ".");
        cout << "Current status: " << inventory->getStock(bookId) << endl;
    }
}

void RentalManager::reserveBook(User* user, Book* book) {
    int bookId = book->getId();

    if (inventory->isAvailable(bookId)) {
        cout << "Has the book. rentBook() to rent." << endl;
        return;
    }

    waitingMgr->addToWaitingList(bookId, user->getName());
    cout << user->getName() + "님이 '" + book->getTitle() + "'reserving." << endl;
    cout << "현재 대기 인원: " << waitingMgr->getWaitingCount(bookId) << endl;
}

void RentalManager::returnBook(User* user, Book* book) {
    int bookId = book->getId();

    if (!book->rented()) {
        cout << "The book is not on reservation status." << endl;
        return;
    }

    book->giveBack();
    inventory->increaseStock(bookId);

    notifier->notify(user->getName() + " has returned the book : " + book->getTitle() + ".");

    if (waitingMgr->hasWaitingUser(bookId)) {
        string nextUser = waitingMgr->getNextWaitingUser(bookId);
        notifier->notify("[prior reservation notification] " + nextUser + ", '" + book->getTitle() + "' we have the book!");
        cout << "waiting : " << nextUser << "." << endl;
    }

    cout << "Current status: " << inventory->getStock(bookId) << endl;
}