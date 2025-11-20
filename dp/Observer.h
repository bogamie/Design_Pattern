#pragma once
#include <string>
#include <vector>
#include <algorithm>
using namespace std;

class Observer {
public:
    virtual ~Observer() = default;
    virtual void update(const string& message) = 0;
    virtual vector<string> getMessages() const = 0;
    virtual void clearMessages() = 0;
};

class NotificationSubject {
    vector<Observer*> observers;
public:
    void attach(Observer* o);
    void detach(Observer* o);
    void notify(const string& message);
};

class EmailNotifier : public Observer {
    vector<string> messages_;
public:
    void update(const string& message) override;
    vector<string> getMessages() const override;
    void clearMessages() override;
};

class SMSNotifier : public Observer {
    vector<string> messages_;
public:
    void update(const string& message) override;
    vector<string> getMessages() const override;
    void clearMessages() override;
};
