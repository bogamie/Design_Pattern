#pragma once
#include "MembershipStrategy.h"

class PremiumMember : public MembershipStrategy {
public:

    double getDiscountRate() const override { return 0.2; }
    string getGradeName() const override { return "Premium"; }
};
