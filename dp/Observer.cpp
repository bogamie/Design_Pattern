#include "Observer.h"
#include <iostream>
using namespace std;

void NotificationSubject::attach(Observer* o) { 
    observers_.push_back(o); 
}

void NotificationSubject::detach(Observer* o) {
    observers_.erase(remove(observers_.begin(), observers_.end(), o), observers_.end());
}

void NotificationSubject::notify(const string& message) {
    for (auto o : observers_) o->update(message);
}

EmailNotifier::EmailNotifier(NotificationSubject* subject) : subject_(subject) {
    if (subject_) subject_->attach(this);
}

EmailNotifier::~EmailNotifier() {
    if (subject_) subject_->detach(this);
}

void EmailNotifier::update(const string& message) {
    messages_.push_back("[Email] " + message);
}

vector<string> EmailNotifier::getMessages() const {
    return messages_;
}

void EmailNotifier::clearMessages() {
    messages_.clear();
}

SMSNotifier::SMSNotifier(NotificationSubject* subject) : subject_(subject) {
    if (subject_) subject_->attach(this);
}

SMSNotifier::~SMSNotifier() {
    if (subject_) subject_->detach(this);
}

void SMSNotifier::update(const string& message) {
    messages_.push_back("[SMS] " + message);
}

vector<string> SMSNotifier::getMessages() const {
    return messages_;
}

void SMSNotifier::clearMessages() {
    messages_.clear();
}