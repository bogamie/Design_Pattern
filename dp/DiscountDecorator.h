#pragma once
using namespace std;

class Discount {
public:
    virtual ~Discount() = default;
    virtual double applyDiscount(double baseFee) = 0;
};

class BasicDiscount : public Discount {
public:
    double applyDiscount(double baseFee) override;
};

class DiscountDecorator : public Discount {
protected:
    Discount* discount;
public:
    DiscountDecorator(Discount* d);
    double applyDiscount(double baseFee) override;
};

class MembershipDiscount : public DiscountDecorator {
public:
    MembershipDiscount(Discount* d);
    double applyDiscount(double baseFee) override;
};

class CouponDiscount : public DiscountDecorator {
public:
    CouponDiscount(Discount* d);
    double applyDiscount(double baseFee) override;
};
