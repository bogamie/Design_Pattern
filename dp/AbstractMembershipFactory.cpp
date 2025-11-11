#include "AbstractMembershipFactory.h"
//전략 패턴 - 요금 계산 전략들에 대한 정적 멤버 변수 초기화
BasicFee AbstractMembershipFactory::BASIC_FEE{};
LateFee  AbstractMembershipFactory::LATE_FEE{};