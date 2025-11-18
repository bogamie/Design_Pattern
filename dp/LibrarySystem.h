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

// Simple in-memory library system to manage books and users for the CLI
class LibrarySystem {
public:
    LibrarySystem();

    // Seed demo data
    void seed();

    // Book management
    bool addBook(int id, const std::string& title, const std::string& author, int quantity);
    bool removeBook(int id);
    bool setBookStock(int id, int quantity);
    bool addBookStock(int id, int delta);
    bool hasBook(int id) const;
    Book* getBook(int id);
    std::vector<Book> listBooks() const; // returns a snapshot copy
    int getStock(int id) const;

    // User management
    bool addUser(const std::string& id, const std::string& pw, const std::string& name, AbstractMembershipFactory* m);
    User* getUser(const std::string& id);
    std::vector<User*> listUsers();

    // Authentication
    User* authenticate(const std::string& id, const std::string& pw);

    // Membership
    bool setUserMembership(const std::string& id, AbstractMembershipFactory* m);

    // Rental interfaces
    RentalManager& rental();

private:
    std::map<int, Book> books_;               // id -> Book
    std::map<std::string, std::unique_ptr<User>> users_; // id -> User

    NotificationSubject notifier_;
    EmailNotifier emailNotifier_;
    SMSNotifier smsNotifier_;

    RentalManager rentalManager_;
    BookInventory& inventory_;
};