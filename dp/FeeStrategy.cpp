#include "FeeStrategy.h"

double BasicFee::calculateFee(int days, double discountRate) const {
    if (days < 0) days = 0;
    double fee = 1000.0 * days;
    return fee * (1.0 - discountRate);
}

double LateFee::calculateFee(int days, double discountRate) const {
    if (days < 0) days = 0;
    double fee = 1000.0 * days;
    
    double longTermDiscount = 0.0;
    if (days > 7) {
        longTermDiscount = (days - 7) * 100.0;
    }
    
    return (fee - longTermDiscount) * (1.0 - discountRate);
}