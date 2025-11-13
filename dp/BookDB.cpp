#include "BookDB.h"

bool BookDB::initTable() {
    return Database::get().exec(
        "CREATE TABLE IF NOT EXISTS books("
        "id INTEGER PRIMARY KEY,"
        "title TEXT,"
        "author TEXT,"
        "stock INTEGER);"
    );
}

bool BookDB::addBook(int id, const std::string& t, const std::string& a, int stock) {
    std::string sql =
        "INSERT INTO books VALUES(" + std::to_string(id) + ",'" +
        t + "','" + a + "'," + std::to_string(stock) + ");";
    return Database::get().exec(sql);
}

bool BookDB::removeBook(int id) {
    return Database::get().exec(
        "DELETE FROM books WHERE id=" + std::to_string(id) + ";"
    );
}

bool BookDB::setStock(int id, int qty) {
    return Database::get().exec(
        "UPDATE books SET stock=" + std::to_string(qty) +
        " WHERE id=" + std::to_string(id) + ";"
    );
}

int BookDB::getStock(int id) {
    return Database::get().queryInt(
        "SELECT stock FROM books WHERE id=" + std::to_string(id) + ";"
    );
}

Book* BookDB::loadBook(int id) {
    std::string t = Database::get().queryString(
        "SELECT title FROM books WHERE id=" + std::to_string(id) + ";"
    );
    if (t == "") return nullptr;

    std::string a = Database::get().queryString(
        "SELECT author FROM books WHERE id=" + std::to_string(id) + ";"
    );

    return new Book(id, t, a);
}

std::vector<Book> BookDB::loadAllBooks() {
    std::vector<Book> list;
    sqlite3_stmt* stmt;

    std::string q = "SELECT id,title,author FROM books;";

    if (sqlite3_prepare_v2(Database::get().db, q.c_str(), -1, &stmt, nullptr) != SQLITE_OK)
        return list;

    while (sqlite3_step(stmt) == SQLITE_ROW) {
        int id = sqlite3_column_int(stmt, 0);
        std::string t = (const char*)sqlite3_column_text(stmt, 1);
        std::string a = (const char*)sqlite3_column_text(stmt, 2);
        list.emplace_back(id, t, a);
    }

    sqlite3_finalize(stmt);
    return list;
}
