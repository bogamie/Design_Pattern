#include "User.h"
#include "AbstractMembershipFactory.h"

using namespace std;

User::User(string id, string pw, string name, AbstractMembershipFactory* factory)
    : id(id), pw(pw), name(name), membershipBenefit(factory->createMembershipBenefit()) {
}

User::~User() { 
}

string User::getName() const { return name; }
string User::getId() const { return id; }
string User::getPw() const { return pw; }
string User::getMembershipName() const { return membershipBenefit->getGradeName(); }
double User::getDiscountRate() const { return membershipBenefit->getDiscountRate(); }
const FeeStrategy* User::getFeeStrategy() const { return membershipBenefit->getFeeStrategy(); }

string User::getGrade() const { return getMembershipName(); }
double User::calculateRentalFee(int days) const {
	return getFeeStrategy()->calculateFee(days, getDiscountRate());
}

void User::setMembership(AbstractMembershipFactory* factory) {
    membershipBenefit = factory->createMembershipBenefit();
}