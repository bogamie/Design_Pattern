#include "Book.h"
using namespace std;

Book::Book(int i, string t, string a) : id(i), title(t), author(a), isRented(false), rentalDays(0) {}

void Book::rent() {
    isRented = true;
}

void Book::giveBack() {
    isRented = false;
}

bool Book::rented() const {
    return isRented;
}

string Book::getTitle() const {
    return title;
}

string Book::getAuthor() const {
    return author;
}

int Book::getId() const {
    return id;
}

void Book::setRentalDays(int days) {
    rentalDays = days;
}

int Book::getRentalDays() const {
    return rentalDays;
}