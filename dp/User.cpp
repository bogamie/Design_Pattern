#pragma once
#include "User.h"

User::User(string id, string pw, string name, AbstractMembershipFactory* m)
    : id(id), pw(pw), name(name), membership(m) {
}
User::~User() { delete membership; }
string User::getName() const { return name; }
string User::getId() const { return id; }
string User::getPw() const { return pw; }
string User::getMembershipName() const {
	return membership->getGradeName();
}
double User::getDiscountRate() const { return membership->getDiscountRate(); }
const FeeStrategy* User::getFeeStrategy() const { return membership->getFeeStrategy(); }