#pragma once
#include "MembershipStrategy.h"

class RestrictedMember : public MembershipStrategy {
public:
    double getDiscountRate() const override { return -1.0; }
    string getGradeName() const override { return "Restricted"; }
};
