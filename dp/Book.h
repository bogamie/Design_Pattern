#pragma once
#include <string>
using namespace std;

class Book {
    int id;
    string title;
    string author;
    bool isRented;
public:
    Book(int i, string t, string a);
    void rent();
    void giveBack();
    bool rented() const;
    string getTitle() const;
    int getId() const;
};