#pragma once
#include <string>
#include <vector>
#include <algorithm>
using namespace std;

class Subject {
public:
    virtual ~Subject() = default;
    virtual void attach(class Observer* o) = 0;
    virtual void detach(Observer* o) = 0;
    virtual void notify(const string& message) = 0;
};

class Observer {
public:
    virtual ~Observer() = default;
    virtual void update(const string& message) = 0;
    virtual vector<string> getMessages() const = 0;
    virtual void clearMessages() = 0;
};

class NotificationSubject : public Subject {
    vector<Observer*> observers_;
public:
    void attach(Observer* o) override;
    void detach(Observer* o) override;
    void notify(const string& message) override;
};

class EmailNotifier : public Observer {
    vector<string> messages_;
    NotificationSubject* subject_;  // 구체 클래스끼리 의존!
public:
    EmailNotifier(NotificationSubject* subject);
    ~EmailNotifier();
    void update(const string& message) override;
    vector<string> getMessages() const override;
    void clearMessages() override;
};

class SMSNotifier : public Observer {
    vector<string> messages_;
    NotificationSubject* subject_;  // 구체 클래스끼리 의존!
public:
    SMSNotifier(NotificationSubject* subject);
    ~SMSNotifier();
    void update(const string& message) override;
    vector<string> getMessages() const override;
    void clearMessages() override;
};