#include "User.h"

User::User(string id, string pw, string name, MembershipStrategy* m)
    : id(id), pw(pw), name(name), membership(m) {
}
User::~User() { delete membership; }
string User::getId() const { return id; }
bool User::checkPassword(const string& input) const { return pw == input; }
string User::getName() const { return name; }
double User::getDiscountRate() const { return membership->getDiscountRate(); }
string User::getGrade() const { return membership->getGradeName(); }
void User::setMembership(MembershipStrategy* m) {
    if (membership == m) return;
    delete membership;
    membership = m;
}
