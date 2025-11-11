#pragma once
#include "Book.h"
#include "User.h"
#include "Observer.h"

class RentalManager {
    NotificationSubject* notifier;
public:
    RentalManager(NotificationSubject* n);
    void rentBook(User* user, Book* book);
    void returnBook(User* user, Book* book);
};
