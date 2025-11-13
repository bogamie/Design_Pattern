#pragma once
#include <string>
#include <vector>
#include "Database.h"
#include "User.h"
#include "MembershipStrategy.h"

class UserDB {
private:
    UserDB() = default;

public:
    static UserDB& get() {
        static UserDB instance;
        return instance;
    }

    bool initTable();

    bool addUser(const std::string& id, const std::string& pw,
        const std::string& name, MembershipStrategy* m);

    bool removeUser(const std::string& id);

    User* loadUser(const std::string& id);  // load as User object

    std::vector<User*> loadAllUsers();

    bool updateMembership(const std::string& id, MembershipStrategy* m);

    bool verifyPassword(const std::string& id, const std::string& pw);
};
