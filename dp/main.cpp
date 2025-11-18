#include <iostream>
#include "User.h"
#include "UserManager.h"
#include "Book.h"
#include "RentalManager.h"
#include "DiscountDecorator.h"
#include "Observer.h"
#include "NormalFactory.h"
#include "PremiumFactory.h"
#include "BookInventory.h"
#include "WaitingListManager.h"

using namespace std;

int main() {
    UserManager um;

    // 파일에서 기존 회원 로드
    um.loadFromFile();

    cout << "\n===== 회원가입 테스트 =====\n";
    um.signup("aaa", "1234", "홍길동", "Normal");
    um.signup("bbb", "5678", "김철수", "Premium");
    um.signup("ccc", "9012", "이영희", "Restricted");

    cout << "\n===== 중복 회원가입 테스트 =====\n";
    um.signup("aaa", "0000", "누군가", "Normal"); // 실패해야 함

    cout << "\n===== 로그인 테스트 =====\n";
    User* user = um.login("bbb", "5678"); // 성공
    if (user) {
        cout << "로그인한 회원 이름: " << user->getName() << endl;
        cout << "멤버십 등급: " << user->getMembershipName() << endl;
    }

    cout << "\n===== 로그인 실패 테스트 =====\n";
    um.login("bbb", "9999"); // 실패

    cout << "\n===== 로그아웃 테스트 =====\n";
    um.logout();

    cout << "\n===== 다시 로그인 & 로그아웃 =====\n";
    um.login("ccc", "9012");
    um.logout();

    cout << "\n===== 종료 전 저장 =====\n";
    um.saveToFile();

    BookInventory& inventory = BookInventory::getInstance();
    inventory.initStock(1, 2);
    inventory.initStock(2, 0);

    NotificationSubject notifier;
    EmailNotifier email;
    SMSNotifier sms;
    notifier.attach(&email);
    notifier.attach(&sms);

    User user1("aaa", "1234", "홍길동", new PremiumFactory());
    User user2("bbb", "5678", "김철수", new NormalFactory());
    User user3("ccc", "9012", "이영희", new NormalFactory());

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