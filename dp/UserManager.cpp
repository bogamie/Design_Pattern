#include "UserManager.h"
#include <fstream>
#include <iostream>
#include <sstream>

using namespace std;

UserManager::UserManager() {}

UserManager::~UserManager() {
    for (auto u : users) {
        delete u;
    }
}

bool UserManager::exists(const string& id) {
    for (auto u : users) {
        if (u->getId() == id) return true;
    }
    return false;
}

AbstractMembershipFactory* UserManager::createFactory(const string& grade) {
    if (grade == "Normal") {
        return new NormalFactory();
    }
    else if (grade == "Premium") {
        return new PremiumFactory();
    }
    else if (grade == "Restricted") {
        return new RestrictedFactory();
    }

    return nullptr;
}

bool UserManager::signup(const string& id, const string& pw, const string& name, const string& grade) {

    if (exists(id)) {
        cout << "이미 존재하는 ID입니다.\n";
        return false;
    }

    AbstractMembershipFactory* factory = createFactory(grade);

    if (factory == nullptr) {
        cout << "알 수 없는 멤버십 등급입니다.\n";
        return false;
    }

    User* newUser = new User(id, pw, name, factory);
    users.push_back(newUser);

    saveToFile();

    cout << "회원가입 완료! (" << name << ")\n";
    return true;
}

User* UserManager::login(const string& id, const string& pw) {
    for (auto u : users) {
        if (u->getId() == id && u->getPw() == pw) {
            loggedInUser = u;
            cout << u->getName() << "님 환영합니다!\n";
            return u;
        }
    }

    cout << "로그인 실패: ID 또는 비밀번호 오류\n";
    return nullptr;
}

void UserManager::logout() {
    if (loggedInUser != nullptr) {
        cout << loggedInUser->getName() << "님 로그아웃 되었습니다.\n";
        loggedInUser = nullptr;
    }
}

void UserManager::saveToFile(const string& filename) {
    ofstream out(filename);

    for (auto u : users) {
        out << "{"
            << "\"id\":\"" << u->getId() << "\","
            << "\"pw\":\"" << u->getPw() << "\","
            << "\"name\":\"" << u->getName() << "\","
            << "\"grade\":\"" << u->getMembershipName() << "\""
            << "}\n";
    }

    out.close();
}

void UserManager::loadFromFile(const string& filename) {
    ifstream in(filename);
    if (!in.is_open()) return;

    string line;
    while (getline(in, line)) {
        if (line.empty()) continue;

        auto parse = [&](const string& key) {
            size_t start = line.find("\"" + key + "\":\"") + key.length() + 4;
            size_t end = line.find("\"", start);
            return line.substr(start, end - start);
            };

        string id = parse("id");
        string pw = parse("pw");
        string name = parse("name");
        string grade = parse("grade");

        AbstractMembershipFactory* factory = createFactory(grade);
        if (factory == nullptr) continue;

        User* u = new User(id, pw, name, factory);
        users.push_back(u);
    }

    in.close();
}
