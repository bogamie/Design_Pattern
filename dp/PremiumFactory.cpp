#include "PremiumFactory.h"

double PremiumFactory::getMonthlyFee() const {
    return 20000.0;
}

double PremiumFactory::getDiscountRate() const {
    return 0.20;
}

const FeeStrategy* PremiumFactory::getFeeStrategy() const {
    return &BASIC_FEE;
}

std::string PremiumFactory::getGradeName() const {
    return "Premium";
}