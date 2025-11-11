#pragma once
#include "AbstractMembershipFactory.h"

class NormalFactory : public AbstractMembershipFactory {
public:
    double getMonthlyFee() const override { return 10000.0; }
    double getDiscountRate() const override { return 0.03; }
    const FeeStrategy* getFeeStrategy() const override { return &BASIC_FEE; }
};