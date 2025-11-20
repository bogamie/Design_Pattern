#pragma once
#include <string>
#include <vector>
#include "User.h"
#include "AbstractMembershipFactory.h"
#include "NormalFactory.h"
#include "PremiumFactory.h"
#include "RestrictedFactory.h"

using namespace std;

class UserManager {
private:
    vector<User*> users;
    User* loggedInUser = nullptr;

    bool exists(const string& id);
    AbstractMembershipFactory* createFactory(const string& grade);

public:
    UserManager();
    ~UserManager();

    bool signup(const string& id, const string& pw, const string& name, const string& grade);
    User* login(const string& id, const string& pw);
    void logout();

    void loadFromFile(const string& filename = "users.txt");
    void saveToFile(const string& filename = "users.txt");

    User* getLoggedInUser() const { return loggedInUser; }
};
