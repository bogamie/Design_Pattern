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

class LibrarySystem {
public:
    LibrarySystem();

    void seed();

    bool addBook(int id, const std::string& title, const std::string& author, int quantity);
    bool removeBook(int id);
    bool setBookStock(int id, int quantity);
    bool addBookStock(int id, int delta);
    bool hasBook(int id) const;
    Book* getBook(int id);
    std::vector<Book> listBooks() const;
    int getStock(int id) const;

    bool addUser(const std::string& id, const std::string& pw, const std::string& name, AbstractMembershipFactory* m);
    User* getUser(const std::string& id);
    std::vector<User*> listUsers();

    User* authenticate(const std::string& id, const std::string& pw);

    bool setUserMembership(const std::string& id, AbstractMembershipFactory* m);

    RentalManager& rental();

    NotificationSubject& getNotifier();
    void registerObserver(Observer* observer);
    void unregisterObserver(Observer* observer);

    vector<string> getNotifications(Observer* observer) const;
    void clearNotifications(Observer* observer);

    void loadUsersFromFile(const string& filename = "users.txt");
    void saveUsersToFile(const string& filename = "users.txt");
    void loadBooksFromFile(const string& filename = "books.txt");
    void saveBooksToFile(const string& filename = "books.txt");

private:
    std::map<int, Book> books_;
    std::map<std::string, std::unique_ptr<User>> users_;

    NotificationSubject notifier_;
    std::vector<Observer*> managedObservers_;

    RentalManager rentalManager_;
    BookInventory& inventory_;
};