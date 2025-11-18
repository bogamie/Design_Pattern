#pragma once
#include <string>
using namespace std;

class MembershipStrategy {
public:
    virtual ~MembershipStrategy() = default;
    virtual double getDiscountRate() const = 0;
    virtual string getGradeName() const = 0;
};

