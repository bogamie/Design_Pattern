#pragma once
#include <string>
#include <vector>
#include <algorithm>
using namespace std;

class Observer {
public:
    virtual ~Observer() = default;
    virtual void update(const string& message) = 0;
};

class NotificationSubject {
    vector<Observer*> observers;
public:
    void attach(Observer* o);
    void detach(Observer* o);
    void notify(const string& message);
};

class EmailNotifier : public Observer {
public:
    void update(const string& message) override;
};

class SMSNotifier : public Observer {
public:
    void update(const string& message) override;
};
