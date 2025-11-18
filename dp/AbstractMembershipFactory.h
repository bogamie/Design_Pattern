#pragma once
#include "FeeStrategy.h"
#include "MembershipStrategy.h"

// 멤버십에 대한 팩토리 메소드
// 사용자 등급별 구독료, 할인율, 요금전략 선택
class AbstractMembershipFactory {
protected:
    static BasicFee BASIC_FEE;
    static LateFee  LATE_FEE;

public:
    virtual ~AbstractMembershipFactory() = default;
	virtual MembershipStrategy* create() const = 0;
	virtual string getGradeName() const = 0;
    virtual double getMonthlyFee() const = 0;
    virtual double getDiscountRate() const = 0;
    virtual const FeeStrategy* getFeeStrategy() const = 0;
};