#pragma once
#include "MembershipStrategy.h"

class NormalMember : public MembershipStrategy {
public:
    double getDiscountRate() const override { return 0.0; }
    string getGradeName() const override { return "Normal"; }
};
