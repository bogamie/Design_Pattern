#pragma once
#pragma once
#include <queue>
#include <map>
#include <mutex>
#include <string>
using namespace std;

class WaitingListManager {
private:
    map<int, queue<string>> waitingLists;
    mutex waitingMutex;

    WaitingListManager() = default;
    WaitingListManager(const WaitingListManager&) = delete;
    WaitingListManager& operator=(const WaitingListManager&) = delete;

public:
    static WaitingListManager& getInstance();
    void addToWaitingList(int bookId, string userName);
    bool hasWaitingUser(int bookId);
    string getNextWaitingUser(int bookId);
    int getWaitingCount(int bookId);
};