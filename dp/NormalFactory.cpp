#include "NormalFactory.h"

double NormalFactory::getMonthlyFee() const {
    return 10000.0;
}

double NormalFactory::getDiscountRate() const {
    return 0.03;
}

const FeeStrategy* NormalFactory::getFeeStrategy() const {
    return &BASIC_FEE;
}

std::string NormalFactory::getGradeName() const {
    return "Normal";
}