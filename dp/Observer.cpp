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

void EmailNotifier::update(const string& message) {
    cout << "[Email 알림] " << message << endl;
}
void SMSNotifier::update(const string& message) {
    cout << "[SMS 알림] " << message << endl;
}
