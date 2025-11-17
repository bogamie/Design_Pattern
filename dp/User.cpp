#include "User.h"
#include <algorithm>

User::User(string id, string pw, string name, MembershipStrategy* m)
    : id(id), pw(pw), name(name), membership(m) {
    // 멤버십에 따른 FeeStrategy 설정
    if (dynamic_cast<PremiumMember*>(m)) {
        feeStrategy = new PremiumFee();
    } else {
        feeStrategy = new StandardFee();
    }
}
User::~User() { 
    delete membership; 
    delete feeStrategy;
}
string User::getId() const { return id; }
bool User::checkPassword(const string& input) const { return pw == input; }
string User::getName() const { return name; }
double User::getDiscountRate() const { return membership->getDiscountRate(); }
string User::getGrade() const { return membership->getGradeName(); }
void User::setMembership(MembershipStrategy* m) {
    if (membership == m) return;
    delete membership;
    membership = m;
}

bool User::hasRented(int bookId) const {
    return find(rentedBooks.begin(), rentedBooks.end(), bookId) != rentedBooks.end();
}

void User::addRentedBook(int bookId) {
    if (!hasRented(bookId)) {
        rentedBooks.push_back(bookId);
    }
}

void User::removeRentedBook(int bookId) {
    auto it = find(rentedBooks.begin(), rentedBooks.end(), bookId);
    if (it != rentedBooks.end()) {
        rentedBooks.erase(it);
    }
}

bool User::hasReserved(int bookId) const {
    return find(reservedBooks.begin(), reservedBooks.end(), bookId) != reservedBooks.end();
}

void User::addReservedBook(int bookId) {
    if (!hasReserved(bookId)) {
        reservedBooks.push_back(bookId);
    }
}

void User::removeReservedBook(int bookId) {
    auto it = find(reservedBooks.begin(), reservedBooks.end(), bookId);
    if (it != reservedBooks.end()) {
        reservedBooks.erase(it);
    }
}

double User::calculateRentalFee(int days) const {
    double baseFee = feeStrategy->calculateFee(days);
    double discountRate = membership->getDiscountRate();
    return baseFee * (1.0 - discountRate);
}
