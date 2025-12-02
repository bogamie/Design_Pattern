#include "User.h"

User::User(const std::string& id,
    const std::string& pw,
    const std::string& name,
    const AbstractMembershipFactory* m)
    : id(id), pw(pw), name(name), membership(m), hasCoupon(false) {
}

const std::string& User::getId() const { return id; }
const std::string& User::getName() const { return name; }
const std::string& User::getPassword() const { return pw; }

bool User::checkPassword(const std::string& p) const {
    return pw == p;
}

std::string User::getGrade() const {
    return membership->getGradeName();
}

double User::getDiscountRate() const {
    return membership->getDiscountRate();
}

const FeeStrategy* User::getFeeStrategy() const {
    return membership->getFeeStrategy();
}

double User::getMonthlyFee() const {
    return membership->getMonthlyFee();
}

void User::setMembership(const AbstractMembershipFactory* m) {
    membership = m;
}

bool User::getCoupon() const {
    return hasCoupon;
}

void User::setCoupon(bool has) {
    hasCoupon = has;
}