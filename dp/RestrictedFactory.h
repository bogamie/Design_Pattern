#pragma once
#include "AbstractMembershipFactory.h"

class RestrictedFactory : public AbstractMembershipFactory {
public:
    std::unique_ptr<MembershipBenefit> createMembershipBenefit() const override;
};