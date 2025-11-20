#include "Observer.h"
#include <iostream>
using namespace std;

void NotificationSubject::attach(Observer* o) { observers.push_back(o); }
void NotificationSubject::detach(Observer* o) {
    observers.erase(remove(observers.begin(), observers.end(), o), observers.end());
}
void NotificationSubject::notify(const string& message) {
    for (auto o : observers) o->update(message);
}

// EmailNotifier
void EmailNotifier::update(const string& message) {
    messages_.push_back("[Email] " + message);
}
vector<string> EmailNotifier::getMessages() const {
    return messages_;
}
void EmailNotifier::clearMessages() {
    messages_.clear();
}

// SMSNotifier
void SMSNotifier::update(const string& message) {
    messages_.push_back("[SMS] " + message);
}
vector<string> SMSNotifier::getMessages() const {
    return messages_;
}
void SMSNotifier::clearMessages() {
    messages_.clear();
}
