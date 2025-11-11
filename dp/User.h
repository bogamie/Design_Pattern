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
    string getName() const;
    double getDiscountRate() const;
    string getGrade() const;
};
