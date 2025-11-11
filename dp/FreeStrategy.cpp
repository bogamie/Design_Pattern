#include "FeeStrategy.h"

double StandardFee::calculateFee(int days) const { return days * 1000; }
double LateFee::calculateFee(int days) const { return days * 1500; }
