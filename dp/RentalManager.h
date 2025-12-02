#pragma once
#include "Book.h"
#include "User.h"
#include "Observer.h"
#include "BookInventory.h"
#include "WaitingListManager.h"
using namespace std;

class RentalManager {
    Subject* notifier;  // Subject \uc778\ud130\ud398\uc774\uc2a4\ub85c \ubcc0\uacbd
    BookInventory* inventory;
    WaitingListManager* waitingMgr;
public:
    RentalManager(Subject* n);
    void rentBook(User* user, Book* book);
    void reserveBook(User* user, Book* book);
    void returnBook(User* user, Book* book);
    double calculateRentalFee(User* user, Book* book);
};