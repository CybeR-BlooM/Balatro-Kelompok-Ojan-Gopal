#pragma once
#include "CoreComponents.h"
#include "ScoringRule.h"

class GameManager {
private:
    HandGenerator handGenerator;
    HandPlayer handPlayer;
    ScoringRule scoringRule;
    BlindRule blindRule;
    RewardRule rewardRule;

public:
    void runSession();
};