#include "MembershipBenefit.h"
#include "AbstractMembershipFactory.h"

double NormalMembershipBenefit::getMonthlyFee() const {
    return 5000.0;
}

double NormalMembershipBenefit::getDiscountRate() const {
    return 0.0;
}

std::string NormalMembershipBenefit::getGradeName() const {
    return "Normal";
}

const FeeStrategy* NormalMembershipBenefit::getFeeStrategy() const {
    return &AbstractMembershipFactory::BASIC_FEE;
}

double PremiumMembershipBenefit::getMonthlyFee() const {
    return 10000.0;
}

double PremiumMembershipBenefit::getDiscountRate() const {
    return 0.2;
}

std::string PremiumMembershipBenefit::getGradeName() const {
    return "Premium";
}

const FeeStrategy* PremiumMembershipBenefit::getFeeStrategy() const {
    return &AbstractMembershipFactory::LATE_FEE;
}

double RestrictedMembershipBenefit::getMonthlyFee() const {
    return 3000.0;
}

double RestrictedMembershipBenefit::getDiscountRate() const {
    return 0.0;
}

std::string RestrictedMembershipBenefit::getGradeName() const {
    return "Restricted";
}

const FeeStrategy* RestrictedMembershipBenefit::getFeeStrategy() const {
    return &AbstractMembershipFactory::BASIC_FEE;
}
