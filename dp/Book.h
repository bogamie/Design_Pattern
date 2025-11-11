#pragma once
#include <string>
using namespace std;

class Book {
    int id;
    string title;
    string author;
    bool isRented;
    int stock;
	int rentedCount;
public:
    Book(int i, string t, string a);
    void rent();
    void giveBack();
    bool rented() const;
    string getTitle() const;

	int getStock() const;
    int getAvailable() const;
	bool canRent() const;

    void markRented();
	void markReturned();
};
