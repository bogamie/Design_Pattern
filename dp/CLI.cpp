#include "CLI.h"
#include <iostream>
#include <limits>
#include "FactoryRegistry.h"

using std::cin;
using std::cout;
using std::endl;

CLI::CLI(LibrarySystem& system) : sys_(system) {}

int CLI::promptInt(const std::string& label) {
    while (true) {
        cout << label;
        int v;
        if (cin >> v) return v;
        cin.clear();
        cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        cout << "Invalid input. Re-enter." << endl;
    }
}

std::string CLI::promptStr(const std::string& label) {
    cout << label;
    std::string s;
    cin >> s;
    return s;
}

void CLI::pause() {
    cout << "Press Enter to continue..." << endl;
    cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    cin.get();
}

void CLI::run() { roleMenu(); }

void CLI::roleMenu() {
    while (true) {
        cout << "\n===== Library System =====" << endl;
        cout << "1) User" << endl;
        cout << "2) Admin" << endl;
        cout << "0) Exit" << endl;
        int sel = promptInt("Choose: ");
        switch (sel) {
        case 1: userMenu(); break;
        case 2: adminMenu(); break;
        case 0: return;
        default: cout << "Invalid menu." << endl; break;
        }
    }
}

void CLI::userMenu() {
    cout << "\n-- User Login / Register --" << endl;
    std::string id = promptStr("ID: ");
    std::string pw = promptStr("Password: ");

    currentUser_ = sys_.authenticate(id, pw);
    if (!currentUser_) {
        cout << "User not found. Create a new account? (y/n): ";
        char yn; cin >> yn;

        if (yn == 'y' || yn == 'Y') {
            string name = promptStr("Name: ");

            sys_.addUser(id, pw, name, &NORMAL_FACTORY);

            currentUser_ = sys_.authenticate(id, pw);
            cout << "Account created successfully.\n";
        }
        else {
            return;
        }
    }

    while (true) {
        cout << "\n-- User Menu -- (" << currentUser_->getName()
            << ", " << currentUser_->getGrade() << ")" << endl;
        cout << "1) View Books" << endl;
        cout << "2) Rent Book" << endl;
        cout << "3) Reserve Book" << endl;
        cout << "4) Return Book" << endl;
        cout << "0) Back" << endl;
        int sel = promptInt("Select: ");
        switch (sel) {
        case 1: userBrowse(); break;
        case 2: userRent(); break;
        case 3: userReserve(); break;
        case 4: userReturn(); break;
        case 0: return;
        default: cout << "Invalid option." << endl; break;
        }
    }
}

void CLI::adminMenu() {
    cout << "\n-- Admin Login --" << endl;
    std::string pw = promptStr("Admin Password: ");
    if (pw != "admin") { cout << "Authentication failed." << endl; return; }

    while (true) {
        cout << "\n-- Admin Menu --" << endl;
        cout << "1) List Books" << endl;
        cout << "2) Add Book" << endl;
        cout << "3) Remove Book" << endl;
        cout << "4) Set Stock" << endl;
        cout << "5) List Users" << endl;
        cout << "6) Change User Membership" << endl;
        cout << "0) Back" << endl;
        int sel = promptInt("Select: ");
        switch (sel) {
        case 1: adminListBooks(); break;
        case 2: adminAddBook(); break;
        case 3: adminRemoveBook(); break;
        case 4: adminSetStock(); break;
        case 5: adminListUsers(); break;
        case 6: adminChangeMembership(); break;
        case 0: return;
        default: cout << "Invalid option." << endl; break;
        }
    }
}

void CLI::userBrowse() {
    auto books = sys_.listBooks();
    if (books.empty()) {
        cout << "No books available." << endl;
        return;
    }
    cout << "\nID\tTitle\tStock" << endl;
    for (const auto& b : books) {
        cout << b.getId() << "\t" << b.getTitle()
            << "\t" << sys_.getStock(b.getId()) << endl;
    }
}

void CLI::userRent() {
    int id = promptInt("Book ID to rent: ");
    Book* book = sys_.getBook(id);
    if (!book) {
        cout << "Book not found." << endl;
        return;
    }
    sys_.rental().rentBook(currentUser_, book);
}

void CLI::userReserve() {
    int id = promptInt("Book ID to reserve: ");
    Book* book = sys_.getBook(id);
    if (!book) {
        cout << "Book not found." << endl;
        return;
    }
    sys_.rental().reserveBook(currentUser_, book);
}

void CLI::userReturn() {
    int id = promptInt("Book ID to return: ");
    Book* book = sys_.getBook(id);
    if (!book) {
        cout << "Book not found." << endl;
        return;
    }
    sys_.rental().returnBook(currentUser_, book);
}

void CLI::adminListBooks() { userBrowse(); }

void CLI::adminAddBook() {
    int id = promptInt("Book ID: ");
    std::string title = promptStr("Title: ");
    std::string author = promptStr("Author: ");
    int qty = promptInt("Initial Stock: ");
    if (sys_.addBook(id, title, author, qty))
        cout << "Book added." << endl;
    else
        cout << "Book ID already exists." << endl;
}

void CLI::adminRemoveBook() {
    int id = promptInt("Book ID to remove: ");
    if (sys_.removeBook(id))
        cout << "Book removed." << endl;
    else
        cout << "Book not found." << endl;
}

void CLI::adminSetStock() {
    int id = promptInt("Book ID: ");
    int qty = promptInt("New Stock: ");
    if (sys_.setBookStock(id, qty))
        cout << "Stock updated." << endl;
    else
        cout << "Book not found." << endl;
}

void CLI::adminListUsers() {
    auto users = sys_.listUsers();
    if (users.empty()) {
        cout << "No users found." << endl;
        return;
    }
    cout << "\nID\tName\tGrade" << endl;
    for (auto* u : users) {
        cout << u->getId() << "\t"
            << u->getName() << "\t"
            << u->getGrade() << endl;
    }
}

void CLI::adminChangeMembership() {
    string id = promptStr("User ID to modify: ");
    cout << "Membership: 1) Normal  2) Premium  3) Restricted\n";

    int sel = promptInt("Select: ");

    AbstractMembershipFactory* m = nullptr;

    switch (sel) {
    case 1:
        m = &NORMAL_FACTORY;
        break;
    case 2:
        m = &PREMIUM_FACTORY;
        break;
    case 3:
        m = &RESTRICTED_FACTORY;
        break;

    default:
        cout << "Invalid option.\n";
        return;
    }

    if (sys_.setUserMembership(id, m))
        cout << "Membership updated.\n";
    else
        cout << "User not found.\n";
}
