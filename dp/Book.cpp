#include "Book.h"

Book::Book(int i, string t, string a) 
	: id(i), title(t), author(a), isRented(false) {
}
void Book::rent() { isRented = true; }
void Book::giveBack() { isRented = false; }
bool Book::rented() const { return isRented; }
string Book::getTitle() const { return title; }

