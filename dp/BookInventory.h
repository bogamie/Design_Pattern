#pragma once
#include <string>
#include <map>
#include <mutex>
using namespace std;

class BookInventory {
private:
    map<int, int> stock;
    mutex stockMutex;

    BookInventory() = default;
    BookInventory(const BookInventory&) = delete;
    BookInventory& operator=(const BookInventory&) = delete;

public:
    static BookInventory& getInstance();
    void initStock(int bookId, int quantity);
    bool decreaseStock(int bookId);
    void increaseStock(int bookId);
    int getStock(int bookId);
    bool isAvailable(int bookId);
};