#include "MembershipStrategy.h"

double NormalMember::getDiscountRate() const { return 0.0; }
string NormalMember::getGradeName() const { return "Normal"; }

double PremiumMember::getDiscountRate() const { return 0.2; }
string PremiumMember::getGradeName() const { return "Premium"; }

double RestrictedMember::getDiscountRate() const { return 0.0; }
string RestrictedMember::getGradeName() const { return "Restricted"; }
