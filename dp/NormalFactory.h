#pragma once
#include "AbstractMembershipFactory.h"

class NormalFactory : public AbstractMembershipFactory {
public:
    double getMonthlyFee() const override;
    double getDiscountRate() const override;
    const FeeStrategy* getFeeStrategy() const override;
    std::string getGradeName() const override;
};