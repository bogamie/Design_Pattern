#pragma once
#include <memory>
#include "MembershipBenefit.h"

class AbstractMembershipFactory {
public:
    static BasicFee BASIC_FEE;
    static LateFee  LATE_FEE;

    virtual ~AbstractMembershipFactory() = default;

    virtual std::unique_ptr<MembershipBenefit> createMembershipBenefit() const = 0;
};