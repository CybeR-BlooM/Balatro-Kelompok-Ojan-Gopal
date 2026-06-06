#pragma once
#include "RewardCommand.h"

// Command untuk menambah sisa "Play" (Hand) di blind berikutnya
class BonusHandCommand : public RewardCommand {
public:
    std::string getName() const override {
        return "Bonus Hand";
    }
    
    std::string getDescription() const override {
        return "Gain +1 hand next blind.";
    }
    
    void execute(RunSessionState& state) override {
        state.remainingPlays += 1; // Menambah sisa play pemain [cite: 446]
    }
};

// Command untuk mendapatkan Reroll gratis di Shop
class FreeRerollCommand : public RewardCommand {
public:
    std::string getName() const override {
        return "Free Reroll";
    }
    
    std::string getDescription() const override {
        return "Gain 1 free reroll.";
    }
    
    void execute(RunSessionState& state) override {
        state.freeRerolls += 1; // Menambah jatah reroll gratis [cite: 458]
    }
};