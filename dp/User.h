#pragma once
#include <string>
#include "AbstractMembershipFactory.h"

class User {
private:
    std::string id;
    std::string pw;
    std::string name;

    const AbstractMembershipFactory* membership;
    bool hasCoupon;

public:
    User(const std::string& id,
        const std::string& pw,
        const std::string& name,
        const AbstractMembershipFactory* m);

    const std::string& getId() const;
    const std::string& getName() const;
    const std::string& getPassword() const;

    bool checkPassword(const std::string& pw) const;

    std::string getGrade() const;
    double getDiscountRate() const;
    const FeeStrategy* getFeeStrategy() const;
    double getMonthlyFee() const;

    void setMembership(const AbstractMembershipFactory* m);
    
    bool getCoupon() const;
    void setCoupon(bool has);
};
