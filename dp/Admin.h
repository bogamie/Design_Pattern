#pragma once
#include "UserDB.h"
#include "BookDB.h"

class Admin {
public:
    bool createUser(const std::string& id, const std::string& pw,
        const std::string& name, MembershipStrategy* m);

    bool deleteUser(const std::string& id);

    bool changeMembership(const std::string& id, MembershipStrategy* m);

    bool addBook(int id, const std::string& t, const std::string& a, int stock);

    bool removeBook(int id);

    bool setBookStock(int id, int qty);
};