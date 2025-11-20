#pragma once
#include <string>
#include "AbstractMembershipFactory.h"
using namespace std;

class User {
    string id, pw, name;
    const AbstractMembershipFactory* membership;
public:
    User(string id, string pw, string name, AbstractMembershipFactory* m);
    ~User();
    string getName() const;
    string getId() const;
    string getPw() const;
    string getMembershipName() const; // 등급 명칭
    double getDiscountRate() const;
    const FeeStrategy* getFeeStrategy() const;
    // 기존 CLI 코드 호환용 편의 함수들
    string getGrade() const;              // getMembershipName() 래핑
    double calculateRentalFee(int days) const; // 전략 + 할인율 적용
};
