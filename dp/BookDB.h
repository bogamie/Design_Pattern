#pragma once
#include <string>
#include <vector>
#include "Database.h"
#include "Book.h"

class BookDB {
private:
    BookDB() = default;

public:
    static BookDB& get() {
        static BookDB instance;
        return instance;
    }

    bool initTable();

    bool addBook(int id, const std::string& t, const std::string& a, int stock);

    bool removeBook(int id);

    bool setStock(int id, int qty);

    int getStock(int id);

    Book* loadBook(int id);

    std::vector<Book> loadAllBooks();
};
