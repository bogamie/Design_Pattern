#include "UserDB.h"
#include "FactoryRegistry.h"
#include "AbstractMembershipFactory.h"

bool UserDB::initTable() {
    return Database::get().exec(
        "CREATE TABLE IF NOT EXISTS users("
        "id TEXT PRIMARY KEY,"
        "pw TEXT,"
        "name TEXT,"
        "grade TEXT);"
    );
}

bool UserDB::addUser(const std::string& id, const std::string& pw,
    const std::string& name, AbstractMembershipFactory* m) {

    std::string sql =
        "INSERT INTO users VALUES ('" + id + "','" +
        pw + "','" + name + "','" + m->getGradeName() + "');";

    return Database::get().exec(sql);
}

bool UserDB::removeUser(const std::string& id) {
    return Database::get().exec(
        "DELETE FROM users WHERE id='" + id + "';"
    );
}

bool UserDB::verifyPassword(const std::string& id, const std::string& pw) {
    std::string stored = Database::get().queryString(
        "SELECT pw FROM users WHERE id='" + id + "';"
    );
    return stored == pw;
}

User* UserDB::loadUser(const std::string& id) {
    std::string name = Database::get().queryString(
        "SELECT name FROM users WHERE id='" + id + "';"
    );

    std::string grade = Database::get().queryString(
        "SELECT grade FROM users WHERE id='" + id + "';"
    );

    if (name == "") return nullptr;

    AbstractMembershipFactory* m = nullptr;
    if (grade == "Normal") m = &NORMAL_FACTORY;
    else if (grade == "Premium") m = &PREMIUM_FACTORY;
    else m = &RESTRICTED_FACTORY;

    return new User(id, "?", name, m);
}

std::vector<User*> UserDB::loadAllUsers() {
    std::vector<User*> v;
    sqlite3_stmt* stmt;

    Database& db = Database::get();

    if (sqlite3_prepare_v2(db.db, "SELECT id,name,grade FROM users;", -1, &stmt, nullptr) != SQLITE_OK)
        return v;

    while (sqlite3_step(stmt) == SQLITE_ROW) {
        std::string id = (const char*)sqlite3_column_text(stmt, 0);
        std::string name = (const char*)sqlite3_column_text(stmt, 1);
        std::string grade = (const char*)sqlite3_column_text(stmt, 2);

        AbstractMembershipFactory* m = nullptr;
        if (grade == "Normal") m = &NORMAL_FACTORY;
        else if (grade == "Premium") m = &PREMIUM_FACTORY;
        else m = &RESTRICTED_FACTORY;

        v.push_back(new User(id, "?", name, m));
    }

    sqlite3_finalize(stmt);
    return v;
}

bool UserDB::updateMembership(const std::string& id, AbstractMembershipFactory* m) {
    std::string sql =
        "UPDATE users SET grade='" + m->getGradeName() +
        "' WHERE id='" + id + "';";
    return Database::get().exec(sql);
}
