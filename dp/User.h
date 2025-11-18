#pragma once
#include <string>
#include "AbstractMembershipFactory.h"
using namespace std;

class User {
    string id, pw, name;
    const AbstractMembershipFactory* membership;
public:
    User(string id, string pw, string name, AbstractMembershipFactory* m);
    ~User();
    string getName() const;
    string getId() const;
    string getPw() const;
    string getMembershipName() const;
    double getDiscountRate() const;
    const FeeStrategy* getFeeStrategy() const;
};
