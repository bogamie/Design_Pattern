#include "LibrarySystem.h"
#include <algorithm>

LibrarySystem::LibrarySystem()
    : rentalManager_(&notifier_), inventory_(BookInventory::getInstance()) {
    // Attach notifiers
    notifier_.attach(&emailNotifier_);
    notifier_.attach(&smsNotifier_);
}

void LibrarySystem::seed() {
    // seed books
    addBook(1, "onepiece", "oda", 2);
    addBook(2, "naruto", "kishimoto", 0);

    // seed users
    addUser("aaa", "1234", "junpyo", new PremiumMember());
    addUser("bbb", "5678", "eonho", new NormalMember());
    addUser("ccc", "9012", "hihi", new NormalMember());
}

bool LibrarySystem::addBook(int id, const std::string& title, const std::string& author, int quantity) {
    if (books_.count(id)) return false;
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
    if (!books_.count(id)) return false;
    int current = inventory_.getStock(id);
    int next = std::max(0, current + delta);
    inventory_.initStock(id, next);
    return true;
}

bool LibrarySystem::hasBook(int id) const { return books_.count(id) > 0; }

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

bool LibrarySystem::addUser(const std::string& id, const std::string& pw, const std::string& name, MembershipStrategy* m) {
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
    return u->checkPassword(pw) ? u : nullptr;
}

bool LibrarySystem::setUserMembership(const std::string& id, MembershipStrategy* m) {
    User* u = getUser(id);
    if (!u) { delete m; return false; }
    u->setMembership(m);
    return true;
}

RentalManager& LibrarySystem::rental() { return rentalManager_; }