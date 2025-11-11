#pragma once

class FeeStrategy {
public:
    virtual ~FeeStrategy() = default;
    virtual double calculateFee(int days) const = 0;
};

class StandardFee : public FeeStrategy {
public:
    double calculateFee(int days) const override;
};

class PremiumFee : public FeeStrategy {
public:
    double calculateFee(int days) const override;
};

class LateFee : public FeeStrategy {
public:
    double calculateFee(int days) const override;
};
