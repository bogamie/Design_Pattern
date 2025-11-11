#include "BookInventory.h"
using namespace std;

BookInventory& BookInventory::getInstance() {
    static BookInventory instance;
    return instance;
}

void BookInventory::initStock(int bookId, int quantity) {
    lock_guard<mutex> lock(stockMutex);
    stock[bookId] = quantity;
}

bool BookInventory::decreaseStock(int bookId) {
    lock_guard<mutex> lock(stockMutex);
    if (stock[bookId] > 0) {
        stock[bookId]--;
        return true;
    }
    return false;
}

void BookInventory::increaseStock(int bookId) {
    lock_guard<mutex> lock(stockMutex);
    stock[bookId]++;
}

int BookInventory::getStock(int bookId) {
    lock_guard<mutex> lock(stockMutex);
    return stock[bookId];
}

bool BookInventory::isAvailable(int bookId) {
    lock_guard<mutex> lock(stockMutex);
    return stock[bookId] > 0;
}