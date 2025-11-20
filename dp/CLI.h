#pragma once
#include <string>
#include <vector>
#include "LibrarySystem.h"

using namespace std;

class CLI {
public:
    explicit CLI(LibrarySystem& system);
    void run();

private:
    LibrarySystem& sys_;

    // main
    int promptInt(const string& label);
    string promptStr(const string& label);
    void pause();
    void clearScreen();
    void printHeader();
    void printNotifications();
    void printSeparator(const string& title = "");

    void roleMenu();
    void userMenu();
    void adminMenu();

    // user flows
    void userBrowse();
    void userRent();
    void userReserve();
    void userReturn();

    // admin flows
    void adminListBooks();
    void adminAddBook();
    void adminRemoveBook();
    void adminSetStock();
    void adminListUsers();
    void adminChangeMembership();

    // session
    User* currentUser_ = nullptr;
};
