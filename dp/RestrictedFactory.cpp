#include "RestrictedFactory.h"
using namespace std;

double RestrictedFactory::getMonthlyFee() const {
    return 5000.0;
}

double RestrictedFactory::getDiscountRate() const {
    return 0.0;
}

const FeeStrategy* RestrictedFactory::getFeeStrategy() const {
    return &LATE_FEE;
}

string RestrictedFactory::getGradeName() const {
    return "Restricted";
}