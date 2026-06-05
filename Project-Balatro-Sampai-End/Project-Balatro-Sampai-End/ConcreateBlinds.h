#pragma once
#include "BlindState.h"

// Kita deklarasikan dulu agar bisa saling melempar State
class BigBlindState;
class BossBlindState;

class SmallBlindState : public BlindState {
public:
    std::string getName() const override { return "Small Blind"; }
    int getTargetScore(int ante) const override { return 300 * ante; }
    int getRewardMoney() const override { return 3; }

    // Deklarasi saja, implementasi nanti di .cpp menyesuaikan Command-nya
    PendingCommand createSkipRewardCommand() const override;

    std::unique_ptr<BlindState> nextState(int& ante) const override;
};

class BigBlindState : public BlindState {
public:
    std::string getName() const override { return "Big Blind"; }
    int getTargetScore(int ante) const override { return 450 * ante; }
    int getRewardMoney() const override { return 4; }

    PendingCommand createSkipRewardCommand() const override;

    std::unique_ptr<BlindState> nextState(int& ante) const override;
};

class BossBlindState : public BlindState {
public:
    std::string getName() const override { return "Boss Blind"; }
    int getTargetScore(int ante) const override { return 600 * ante; }
    int getRewardMoney() const override { return 5; }

    PendingCommand createSkipRewardCommand() const override;

    std::unique_ptr<BlindState> nextState(int& ante) const override {
        ante++; // Boss Blind menaikkan ante saat selesai
        return std::make_unique<SmallBlindState>();
    }
};

// Implementasi fungsi nextState untuk Small dan Big
inline std::unique_ptr<BlindState> SmallBlindState::nextState(int& ante) const {
    return std::make_unique<BigBlindState>();
}

inline std::unique_ptr<BlindState> BigBlindState::nextState(int& ante) const {
    return std::make_unique<BossBlindState>();
}