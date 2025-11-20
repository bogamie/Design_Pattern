#pragma once
#include <map>
#include <memory>
#include <vector>
#include <string>
#include "Book.h"
#include "User.h"
#include "RentalManager.h"
#include "Observer.h"
#include "BookInventory.h"
#include "AbstractMembershipFactory.h"
using namespace std;

// Simple in-memory library system to manage books and users for the CLI
class LibrarySystem {
public:
    LibrarySystem();

    // Seed demo data
    void seed();

    // Book management
    bool addBook(int id, const string& title, const string& author, int quantity);
    bool removeBook(int id);
    bool setBookStock(int id, int quantity);
    bool addBookStock(int id, int delta);
    bool hasBook(int id) const;
    Book* getBook(int id);
    vector<Book> listBooks() const; // returns a snapshot copy
    int getStock(int id) const;

    // User management
    bool addUser(const string& id, const string& pw, const string& name, AbstractMembershipFactory* m);
    User* getUser(const string& id);
    vector<User*> listUsers();

    // Authentication
    User* authenticate(const string& id, const string& pw);

    // Membership
    bool setUserMembership(const string& id, AbstractMembershipFactory* m);

    // Rental interfaces
    RentalManager& rental();

    // Notification helpers
    vector<string> getEmailNotifications() const;
    vector<string> getSMSNotifications() const;
    void clearNotifications();

    // Persistence
    void loadUsersFromFile(const string& filename = "users.txt");
    void saveUsersToFile(const string& filename = "users.txt");

private:
    map<int, Book> books_;               // id -> Book
    map<string, unique_ptr<User>> users_; // id -> User

    NotificationSubject notifier_;
    EmailNotifier emailNotifier_;
    SMSNotifier smsNotifier_;

    RentalManager rentalManager_;
    BookInventory& inventory_;
};
