#pragma once
#include <string>
#include <memory>
#include "MembershipBenefit.h"

class AbstractMembershipFactory;

using namespace std;

class User {
private:
    string id, pw, name;

    std::unique_ptr<MembershipBenefit> membershipBenefit;

public:
    User(string id, string pw, string name, AbstractMembershipFactory* factory);
    ~User();
    string getName() const;
    string getId() const;
    string getPw() const;
    string getMembershipName() const;
    double getDiscountRate() const;
    const FeeStrategy* getFeeStrategy() const;
    string getGrade() const;
    double calculateRentalFee(int days) const;
    void setMembership(AbstractMembershipFactory* factory);
};
