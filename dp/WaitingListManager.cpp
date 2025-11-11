#include "WaitingListManager.h"
using namespace std;

WaitingListManager& WaitingListManager::getInstance() {
    static WaitingListManager instance;
    return instance;
}

void WaitingListManager::addToWaitingList(int bookId, string userName) {
    lock_guard<mutex> lock(waitingMutex);
    waitingLists[bookId].push(userName);
}

bool WaitingListManager::hasWaitingUser(int bookId) {
    lock_guard<mutex> lock(waitingMutex);
    return !waitingLists[bookId].empty();
}

string WaitingListManager::getNextWaitingUser(int bookId) {
    lock_guard<mutex> lock(waitingMutex);
    if (!waitingLists[bookId].empty()) {
        string user = waitingLists[bookId].front();
        waitingLists[bookId].pop();
        return user;
    }
    return "";
}

int WaitingListManager::getWaitingCount(int bookId) {
    lock_guard<mutex> lock(waitingMutex);
    return waitingLists[bookId].size();
}