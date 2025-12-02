#include "PremiumFactory.h"
#include "MembershipBenefit.h"

std::unique_ptr<MembershipBenefit> PremiumFactory::createMembershipBenefit() const {
    return std::make_unique<PremiumMembershipBenefit>();
}