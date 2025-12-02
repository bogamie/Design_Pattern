#include "LibrarySystem.h"
#include "FactoryRegistry.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <algorithm>

LibrarySystem::LibrarySystem()
    : rentalManager_(&notifier_), inventory_(BookInventory::getInstance()) {
    // Attach notifiers
    notifier_.attach(&emailNotifier_);
    notifier_.attach(&smsNotifier_);
    seed();
    // 기존 사용자 로드
    loadUsersFromFile();
}

void LibrarySystem::seed() {
    // seed books
    addBook(1, "onepiece", "oda", 2);
    addBook(2, "naruto", "kishimoto", 0);

    // seed users
    addUser("aaa", "1234", "junpyo", &PREMIUM_FACTORY);
    addUser("bbb", "5678", "eonho", &NORMAL_FACTORY);
    addUser("ccc", "9012", "hihi", &NORMAL_FACTORY);
}

bool LibrarySystem::addBook(int id, const std::string& title, const std::string& author, int quantity) {
    if (!hasBook(id)) return false;
    books_.emplace(id, Book{ id, title, author });
    inventory_.initStock(id, quantity);
    return true;
}

bool LibrarySystem::removeBook(int id) {
    if (!books_.count(id)) return false;
    books_.erase(id);
    // Optional: zero out stock
    inventory_.initStock(id, 0);
    return true;
}

bool LibrarySystem::setBookStock(int id, int quantity) {
    if (!books_.count(id)) return false;
    inventory_.initStock(id, quantity);
    return true;
}

bool LibrarySystem::addBookStock(int id, int delta) {
    if (!hasBook(id)) return false;
    for (int i = 0; i < delta; ++i) inventory_.increaseStock(id);
    return true;
}

bool LibrarySystem::hasBook(int id) const { return books_.count(id) != 0; }

Book* LibrarySystem::getBook(int id) {
    auto it = books_.find(id);
    if (it == books_.end()) return nullptr;
    return &it->second;
}

std::vector<Book> LibrarySystem::listBooks() const {
    std::vector<Book> v;
    v.reserve(books_.size());
    for (const auto& kv : books_) v.push_back(kv.second);
    return v;
}

int LibrarySystem::getStock(int id) const {
    return const_cast<BookInventory&>(inventory_).getStock(id);
}

bool LibrarySystem::addUser(const std::string& id, const std::string& pw, const std::string& name, AbstractMembershipFactory* m) {
    if (users_.count(id)) return false;
    users_[id] = std::unique_ptr<User>(new User(id, pw, name, m));
    return true;
}

User* LibrarySystem::getUser(const std::string& id) {
    auto it = users_.find(id);
    if (it == users_.end()) return nullptr;
    return it->second.get();
}

std::vector<User*> LibrarySystem::listUsers() {
    std::vector<User*> v;
    v.reserve(users_.size());
    for (auto& kv : users_) v.push_back(kv.second.get());
    return v;
}

User* LibrarySystem::authenticate(const std::string& id, const std::string& pw) {
    User* u = getUser(id);
    if (!u) return nullptr;
    return (u->getPw() == pw) ? u : nullptr;
}

bool LibrarySystem::setUserMembership(const string& id, AbstractMembershipFactory* m) {
    auto it = users_.find(id);
    if (it == users_.end()) return false;
    User* old = it->second.release();
    unique_ptr<User> repl(new User(old->getId(), old->getPw(), old->getName(), m));
    delete old; // 기존 membership 포함 소멸
    it->second = std::move(repl);
    saveUsersToFile();
    return true;
}

RentalManager& LibrarySystem::rental() { return rentalManager_; }

// Notification helpers
vector<string> LibrarySystem::getEmailNotifications() const {
    return emailNotifier_.getMessages();
}

vector<string> LibrarySystem::getSMSNotifications() const {
    return smsNotifier_.getMessages();
}

void LibrarySystem::clearNotifications() {
    const_cast<EmailNotifier&>(emailNotifier_).clearMessages();
    const_cast<SMSNotifier&>(smsNotifier_).clearMessages();
}

// --- Persistence helpers ---
static AbstractMembershipFactory* createFactoryByGrade(const string& grade) {
    if (grade == "Normal") return new NormalFactory();
    if (grade == "Premium") return new PremiumFactory();
    if (grade == "Restricted") return new RestrictedFactory();
    return new NormalFactory();
}

void LibrarySystem::saveUsersToFile(const string& filename) {
    ofstream out(filename);
    if (!out.is_open()) return;
    for (auto& kv : users_) {
        User* u = kv.second.get();
        out << "{"
            << "\"id\":\"" << u->getId() << "\","
            << "\"pw\":\"" << u->getPw() << "\","
            << "\"name\":\"" << u->getName() << "\","
            << "\"grade\":\"" << u->getMembershipName() << "\""
            << "}\n";
    }
    out.close();
}

void LibrarySystem::loadUsersFromFile(const string& filename) {
    ifstream in(filename);
    if (!in.is_open()) return;
    string line;
    while (getline(in, line)) {
        if (line.empty()) continue;
        auto parse = [&](const string& key) {
            size_t start = line.find("\"" + key + "\":\"") + key.length() + 4;
            size_t end = line.find("\"", start);
            if (start == string::npos || end == string::npos || end < start) return string("");
            return line.substr(start, end - start);
            };
        string id = parse("id");
        string pw = parse("pw");
        string name = parse("name");
        string grade = parse("grade");
        if (id.empty()) continue;
        if (users_.count(id)) continue;
        AbstractMembershipFactory* f = createFactoryByGrade(grade);
        users_[id] = unique_ptr<User>(new User(id, pw, name, f));
    }
    in.close();
}

RentalManager& LibrarySystem::rental() { return rentalManager_; }