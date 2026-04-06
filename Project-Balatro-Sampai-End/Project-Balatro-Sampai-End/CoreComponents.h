#pragma once
#include "Hand.h"

class HandGenerator {
public:
    Hand generateHand();
};

class HandPlayer {
public:
    Hand generateHand();
};

class BlindRule {
public:
    bool checkBlind(int score);
};

class RewardRule {
public:
    int earnMoney(bool win, int score);
};