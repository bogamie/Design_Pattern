#include "FeeStrategy.h"

double BasicFee::calculateFee(int days, double discountRate) const {
    if (days < 0) days = 0;
    double fee = 1000.0 * days;
    return fee * (1.0 - discountRate);
}

double LateFee::calculateFee(int days, double discountRate) const {
    if (days < 0) days = 0;
    double fee = 1000.0 * days;
    double late = (days > 7) ? (days - 7) * 500.0 : 0.0;
    return (fee * (1.0 - discountRate)) + late;
}