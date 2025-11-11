#pragma once
#include "AbstractMembershipFactory.h"

class RestrictedFactory : public AbstractMembershipFactory {
public:
    double getMonthlyFee() const override { return 0.0; }
    double getDiscountRate() const override { return 0.0; }
    const FeeStrategy* getFeeStrategy() const override { return &LATE_FEE; }
};