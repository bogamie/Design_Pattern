#include <iostream>
#include "User.h"
#include "Book.h"
#include "RentalManager.h"
#include "DiscountDecorator.h"
#include "Observer.h"
#include "MembershipStrategy.h"
#include "BookInventory.h"
#include "WaitingListManager.h"
using namespace std;

int main() {
    BookInventory& inventory = BookInventory::getInstance();
    inventory.initStock(1, 2);
    inventory.initStock(2, 0);

    NotificationSubject notifier;
    EmailNotifier email;
    SMSNotifier sms;
    notifier.attach(&email);
    notifier.attach(&sms);

    User user1("aaa", "1234", "홍길동", new PremiumMember());
    User user2("bbb", "5678", "김철수", new NormalMember());
    User user3("ccc", "9012", "이영희", new NormalMember());

    Book book1(1, "원피스", "오다");
    Book book2(2, "나루토", "키시모토");

    RentalManager rental(&notifier);

    rental.rentBook(&user1, &book1);
    rental.rentBook(&user2, &book1);
    rental.rentBook(&user3, &book1);

    rental.reserveBook(&user3, &book1);

    rental.returnBook(&user1, &book1);

    rental.reserveBook(&user1, &book2);
    rental.reserveBook(&user2, &book2);

    double baseFee = 5000;
    Discount* fee = new MembershipDiscount(new CouponDiscount(new BasicDiscount()));
    cout << "최종 요금: " << fee->applyDiscount(baseFee) << "원" << endl;
    delete fee;

    return 0;
}