#include <iostream>
#include "User.h"
#include "Book.h"
#include "RentalManager.h"
#include "DiscountDecorator.h"
#include "Observer.h"
#include "MembershipStrategy.h"

using namespace std;

int main() {
    NotificationSubject notifier;
    EmailNotifier email;
    SMSNotifier sms;
    notifier.attach(&email);
    notifier.attach(&sms);

    User user1("aaa", "1234", "홍길동", new PremiumMember());
    Book book1(1, "원피스", "오다");

    RentalManager rental(&notifier);
    rental.rentBook(&user1, &book1);
    rental.returnBook(&user1, &book1);

    double baseFee = 5000;
    Discount* fee = new MembershipDiscount(new CouponDiscount(new BasicDiscount()));
    cout << "최종 요금: " << fee->applyDiscount(baseFee) << "원" << endl;
    delete fee;

    return 0;
}
