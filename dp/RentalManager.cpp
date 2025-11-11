#include "RentalManager.h"
#include <iostream>
using namespace std;

RentalManager::RentalManager(NotificationSubject* n) : notifier(n) {}
void RentalManager::rentBook(User* user, Book* book) {
    if (book->rented()) {
        cout << "이미 대여 중입니다." << endl;
        return;
    }
    book->rent();
    notifier->notify(user->getName() + "님이 '" + book->getTitle() + "'을(를) 대여했습니다.");
}
void RentalManager::returnBook(User* user, Book* book) {
    if (!book->rented()) {
        cout << "이 도서는 대여 상태가 아닙니다." << endl;
        return;
    }
    book->giveBack();
    notifier->notify(user->getName() + "님이 '" + book->getTitle() + "'을(를) 반납했습니다.");
}
