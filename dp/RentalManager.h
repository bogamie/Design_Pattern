#pragma once
#include "Book.h"
#include "User.h"
#include "Observer.h"
#include "BookInventory.h"
#include "WaitingListManager.h"
using namespace std;

class RentalManager {
    Subject* notifier;  
    BookInventory* inventory;
    WaitingListManager* waitingMgr;
public:
    RentalManager(Subject* n);
    void rentBook(User* user, Book* book);
    void reserveBook(User* user, Book* book);
    void returnBook(User* user, Book* book);
    double calculateRentalFee(User* user, Book* book);
};
