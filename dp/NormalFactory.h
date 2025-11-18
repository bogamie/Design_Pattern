#pragma once
#include "AbstractMembershipFactory.h"
#include "NormalMember.h"

class NormalFactory : public AbstractMembershipFactory {
public:
    MembershipStrategy* create() const override {
        return new NormalMember();
    }

    string getGradeName() const override { return "Normal"; }
    double getMonthlyFee() const override { return 0.0; }
    double getDiscountRate() const override { return 0.0; }
    const FeeStrategy* getFeeStrategy() const override { return &BASIC_FEE; }
};
