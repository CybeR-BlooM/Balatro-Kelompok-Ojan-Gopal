#pragma once
#include "PokerHandChecker.h"

class FlushFiveChecker : public PokerHandChecker {
public:
    HandRank check(const ChosenHand& hand) override;
};