#include "DiscountDecorator.h"

double BasicDiscount::applyDiscount(double baseFee) { return baseFee; }
DiscountDecorator::DiscountDecorator(Discount* d) : discount(d) {}
double DiscountDecorator::applyDiscount(double baseFee) { return discount->applyDiscount(baseFee); }
MembershipDiscount::MembershipDiscount(Discount* d) : DiscountDecorator(d) {}
double MembershipDiscount::applyDiscount(double baseFee) {
    double base = DiscountDecorator::applyDiscount(baseFee);
    return base * 0.9;
}
CouponDiscount::CouponDiscount(Discount* d) : DiscountDecorator(d) {}
double CouponDiscount::applyDiscount(double baseFee) {
    double base = DiscountDecorator::applyDiscount(baseFee);
    return base - 500;
}
