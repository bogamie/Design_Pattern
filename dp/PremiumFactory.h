#pragma once
#include "AbstractMembershipFactory.h"

class PremiumFactory : public AbstractMembershipFactory {
public:
    std::unique_ptr<MembershipBenefit> createMembershipBenefit() const override;
};