#include "RestrictedFactory.h"
#include "MembershipBenefit.h"

std::unique_ptr<MembershipBenefit> RestrictedFactory::createMembershipBenefit() const {
    return std::make_unique<RestrictedMembershipBenefit>();
}