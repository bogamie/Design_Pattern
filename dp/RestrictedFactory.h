#pragma once
#include "AbstractMembershipFactory.h"
#include "RestrictedMember.h"
class RestrictedFactory : public AbstractMembershipFactory {
public:
    MembershipStrategy* create() const override {
        return new RestrictedMember();
    }


    double getMonthlyFee() const override { return 0.0; }
    double getDiscountRate() const override { return 0.0; }
    const FeeStrategy* getFeeStrategy() const override { return &LATE_FEE; }
	string getGradeName() const override { return "Restricted"; }
};