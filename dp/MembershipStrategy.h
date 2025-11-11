#pragma once
#include <string>
using namespace std;

class MembershipStrategy {
public:
    virtual ~MembershipStrategy() = default;
    virtual double getDiscountRate() const = 0;
    virtual string getGradeName() const = 0;
};

class NormalMember : public MembershipStrategy {
public:
    double getDiscountRate() const override;
    string getGradeName() const override;
};

class PremiumMember : public MembershipStrategy {
public:
    double getDiscountRate() const override;
    string getGradeName() const override;
};

class RestrictedMember : public MembershipStrategy {
public:
    double getDiscountRate() const override;
    string getGradeName() const override;
};
