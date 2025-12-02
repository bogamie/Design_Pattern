#include "User.h"

using namespace std;

User::User(string id, string pw, string name, AbstractMembershipFactory* m)
    : id(id), pw(pw), name(name), membership(m) {
}
User::~User() { delete membership; }
string User::getName() const { return name; }
string User::getId() const { return id; }
string User::getPw() const { return pw; }
string User::getMembershipName() const { return membership->getGradeName(); }
double User::getDiscountRate() const { return membership->getDiscountRate(); }
const FeeStrategy* User::getFeeStrategy() const { return membership->getFeeStrategy(); }

// 편의/호환 메서드
string User::getGrade() const { return getMembershipName(); }
double User::calculateRentalFee(int days) const {
	return getFeeStrategy()->calculateFee(days, getDiscountRate());
}