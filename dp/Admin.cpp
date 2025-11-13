#include "Admin.h"

bool Admin::createUser(const std::string& id, const std::string& pw,
    const std::string& name, MembershipStrategy* m) {
    return UserDB::get().addUser(id, pw, name, m);
}

bool Admin::deleteUser(const std::string& id) {
    return UserDB::get().removeUser(id);
}

bool Admin::changeMembership(const std::string& id, MembershipStrategy* m) {
    return UserDB::get().updateMembership(id, m);
}

bool Admin::addBook(int id, const std::string& t, const std::string& a, int stock) {
    return BookDB::get().addBook(id, t, a, stock);
}

bool Admin::removeBook(int id) {
    return BookDB::get().removeBook(id);
}

bool Admin::setBookStock(int id, int qty) {
    return BookDB::get().setStock(id, qty);
}
