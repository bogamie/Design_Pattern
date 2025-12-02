#pragma once
#include <string>
#include "FeeStrategy.h"

class MembershipBenefit {
public:
    virtual ~MembershipBenefit() = default;
    virtual double getMonthlyFee() const = 0;
    virtual double getDiscountRate() const = 0;
    virtual std::string getGradeName() const = 0;
    virtual const FeeStrategy* getFeeStrategy() const = 0;
};

class NormalMembershipBenefit : public MembershipBenefit {
public:
    double getMonthlyFee() const override;
    double getDiscountRate() const override;
    std::string getGradeName() const override;
    const FeeStrategy* getFeeStrategy() const override;
};

class PremiumMembershipBenefit : public MembershipBenefit {
public:
    double getMonthlyFee() const override;
    double getDiscountRate() const override;
    std::string getGradeName() const override;
    const FeeStrategy* getFeeStrategy() const override;
};

class RestrictedMembershipBenefit : public MembershipBenefit {
public:
    double getMonthlyFee() const override;
    double getDiscountRate() const override;
    std::string getGradeName() const override;
    const FeeStrategy* getFeeStrategy() const override;
};
