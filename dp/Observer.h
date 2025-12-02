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

class Subject {
public:
    virtual ~Subject() = default;
    virtual void attach(Observer* o) = 0;
    virtual void detach(Observer* o) = 0;
    virtual void notify(const string& message) = 0;
};

class NotificationSubject : public Subject {
    vector<Observer*> observers;
public:
    void attach(Observer* o) override;
    void detach(Observer* o) override;
    void notify(const string& message) override;
};

class EmailNotifier : public Observer {
public:
    void update(const string& message) override;
};

class SMSNotifier : public Observer {
public:
    void update(const string& message) override;
};
