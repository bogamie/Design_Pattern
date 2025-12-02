#pragma once
#include <string>
#include "FeeStrategy.h"

class AbstractMembershipFactory {
protected:
    static BasicFee BASIC_FEE;
    static LateFee  LATE_FEE;

public:
    virtual ~AbstractMembershipFactory() = default;

    virtual double getMonthlyFee() const = 0;
    virtual double getDiscountRate() const = 0;
    virtual const FeeStrategy* getFeeStrategy() const = 0;
    virtual std::string getGradeName() const = 0;
};