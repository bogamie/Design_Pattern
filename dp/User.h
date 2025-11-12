#pragma once
#include <string>
#include "MembershipStrategy.h"
using namespace std;

class User {
    string id, pw, name;
    MembershipStrategy* membership;
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
};
