#pragma once
#include "AbstractMembershipFactory.h"

// 프리미엄 회원: 기본 요금 전략, 10% 할인
class PremiumFactory : public AbstractMembershipFactory {
public:
    double getMonthlyFee() const override { return 15000.0; }
    double getDiscountRate() const override { return 0.10; }
    const FeeStrategy* getFeeStrategy() const override { return &BASIC_FEE; }
};