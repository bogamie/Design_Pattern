#pragma once
#include <string>
#include "LibrarySystem.h"

class CLI {
public:
    explicit CLI(LibrarySystem& system);
    void run();

private:
    LibrarySystem& sys_;

    int promptInt(const std::string& label);
    std::string promptStr(const std::string& label);
    void pause();

    void roleMenu();
    void userMenu();
    void adminMenu();

    void userBrowse();
    void userRent();
    void userReserve();
    void userReturn();

    void adminListBooks();
    void adminAddBook();
    void adminRemoveBook();
    void adminSetStock();
    void adminListUsers();
    void adminChangeMembership();

    User* currentUser_ = nullptr;
};