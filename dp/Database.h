#pragma once
#include "sqlite3.h"
#include <string>

class Database {
public:
    sqlite3* db;

    Database();

    static Database& get();

    bool open(const std::string& file);
    void close();

    bool exec(const std::string& query);

    std::string queryString(const std::string& q);
    int queryInt(const std::string& q);
};