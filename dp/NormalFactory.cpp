#include "NormalFactory.h"
#include "MembershipBenefit.h"

std::unique_ptr<MembershipBenefit> NormalFactory::createMembershipBenefit() const {
    return std::make_unique<NormalMembershipBenefit>();
}