#pragma once
#include "AbstractMembershipFactory.h"

class NormalFactory : public AbstractMembershipFactory {
public:
    std::unique_ptr<MembershipBenefit> createMembershipBenefit() const override;
};