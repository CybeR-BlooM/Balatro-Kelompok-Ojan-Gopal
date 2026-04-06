#pragma once
#include "Hand.h"
#include "GameTypes.h"
#include "PokerHandChecker.h"

class ScoringRule {
private:
    PokerHandChecker* chainRoot; // Menyimpan ujung pertama dari rantai

public:
    ScoringRule();  // Constructor
    ~ScoringRule(); // Destructor

    int scoreHand(const Hand& hand);
    int convertRankToScore(HandRank rank);
};