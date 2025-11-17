#pragma once
#include <string>
#include <vector>
#include "MembershipStrategy.h"
#include "FeeStrategy.h"
using namespace std;

class User {
    string id, pw, name;
    MembershipStrategy* membership;
    FeeStrategy* feeStrategy;
    vector<int> rentedBooks;    // 대여 중인 책 ID 목록
    vector<int> reservedBooks;  // 예약 중인 책 ID 목록
public:
    User(string id, string pw, string name, MembershipStrategy* m);
    ~User();
    // identity
    string getId() const;
    bool checkPassword(const string& input) const;
    
    string getName() const;
    double getDiscountRate() const;
    string getGrade() const;
    
    // membership management
    void setMembership(MembershipStrategy* m);
    
    // rental management
    bool hasRented(int bookId) const;
    void addRentedBook(int bookId);
    void removeRentedBook(int bookId);
    
    // reservation management
    bool hasReserved(int bookId) const;
    void addReservedBook(int bookId);
    void removeReservedBook(int bookId);
    
    // fee calculation
    double calculateRentalFee(int days) const;
};
