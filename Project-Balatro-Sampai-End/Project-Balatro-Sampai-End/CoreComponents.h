#pragma once
// #include "Hand.h" dihapus dari sini karena BlindRule dan RewardRule tidak butuh Hand.

class BlindRule {
public:
    bool checkBlind(int score);
};

class RewardRule {
public:
    int earnMoney(bool win, int score);
};