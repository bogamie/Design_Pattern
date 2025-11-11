#include "FeeStrategy.h"

double BasicFee::calculateFee(int days, double discountRate) const {
    if (days < 0) days = 0;
    double fee = 1000.0 * days;               // 기본요금
    return fee * (1.0 - discountRate);        // 할인 적용
}

double LateFee::calculateFee(int days, double discountRate) const {
    if (days < 0) days = 0;
    double fee = 1000.0 * days;               // 기본요금
    double late = (days > 7) ? (days - 7) * 500.0 : 0.0; // 연체요금
    return (fee * (1.0 - discountRate)) + late; // 기본요금만 할인 적용
}