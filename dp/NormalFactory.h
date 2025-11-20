#pragma once
#include "AbstractMembershipFactory.h"
using namespace std;

class NormalFactory : public AbstractMembershipFactory {
public:
    double getMonthlyFee() const override;
    double getDiscountRate() const override;
    const FeeStrategy* getFeeStrategy() const override;
    string getGradeName() const override;
};