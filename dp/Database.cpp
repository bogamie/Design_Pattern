#include "Database.h"
#include "BookDB.h"
#include <iostream>

Database::Database() : db(nullptr) {}

Database& Database::get() {
    static Database instance;
    return instance;
}

bool Database::open(const std::string& file) {
    sqlite3_open(file.c_str(), &db);
    BookDB::get().initTable();
    return true;

    std::cerr << "DB Open Failed: " << sqlite3_errmsg(db) << "\n";
    return false;
}

void Database::close() {
    if (db) sqlite3_close(db);
}

bool Database::exec(const std::string& query) {
    char* err = nullptr;
    if (sqlite3_exec(db, query.c_str(), nullptr, nullptr, &err) != SQLITE_OK) {
        std::cerr << "SQL Error: " << err << "\n";
        sqlite3_free(err);
        return false;
    }
    return true;
}

std::string Database::queryString(const std::string& q) {
    sqlite3_stmt* stmt;
    std::string val = "";

    if (sqlite3_prepare_v2(db, q.c_str(), -1, &stmt, nullptr) == SQLITE_OK) {
        if (sqlite3_step(stmt) == SQLITE_ROW) {
            const unsigned char* s = sqlite3_column_text(stmt, 0);
            if (s) val = reinterpret_cast<const char*>(s);
        }
    }
    sqlite3_finalize(stmt);
    return val;
}

int Database::queryInt(const std::string& q) {
    sqlite3_stmt* stmt;
    int v = -1;

    if (sqlite3_prepare_v2(db, q.c_str(), -1, &stmt, nullptr) == SQLITE_OK) {
        if (sqlite3_step(stmt) == SQLITE_ROW)
            v = sqlite3_column_int(stmt, 0);
    }

    sqlite3_finalize(stmt);
    return v;
}
