#include "FeeStrategy.h"

double StandardFee::calculateFee(int days) const { return days * 1000; }
double PremiumFee::calculateFee(int days) const { return days * 800; }
double LateFee::calculateFee(int days) const { return days * 1500; }
