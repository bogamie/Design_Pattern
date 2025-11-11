#pragma once
#include "Book.h"
#include "User.h"
#include "Observer.h"
#include "BookInventory.h"
#include "WaitingListManager.h"
using namespace std;

class RentalManager {
    NotificationSubject* notifier;
    BookInventory* inventory;
    WaitingListManager* waitingMgr;
public:
    RentalManager(NotificationSubject* n);
    void rentBook(User* user, Book* book);
    void reserveBook(User* user, Book* book);
    void returnBook(User* user, Book* book);
};