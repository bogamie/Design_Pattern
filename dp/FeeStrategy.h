#pragma once
using namespace std;

// 책 요금 계산용 전략 (Strategy Pattern)
class FeeStrategy {
public:
    virtual ~FeeStrategy() = default;
    virtual double calculateFee(int days, double discountRate) const = 0;
};

// 기본 요금 (할인 적용)
class BasicFee : public FeeStrategy {
public:
    double calculateFee(int days, double discountRate) const override;
};

// 연체 요금 (할인 미적용)
class LateFee : public FeeStrategy {
public:
    double calculateFee(int days, double discountRate) const override;
};