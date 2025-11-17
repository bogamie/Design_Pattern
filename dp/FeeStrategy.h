#pragma once

class FeeStrategy {
public:
    virtual ~FeeStrategy() = default;
    virtual double calculateFee(int days, double discountRate) const = 0;
};

class BasicFee : public FeeStrategy {
public:
    double calculateFee(int days, double discountRate) const override;
};

class LateFee : public FeeStrategy {
public:
    double calculateFee(int days, double discountRate) const override;
};