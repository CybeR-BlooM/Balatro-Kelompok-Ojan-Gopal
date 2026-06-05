#pragma once
#include <string>
#include <memory>
#include "RewardCommand.h"

class BlindState {
public:
    virtual ~BlindState() = default;
    virtual std::string getName() const = 0;
    virtual int getTargetScore(int ante) const = 0;
    virtual int getRewardMoney() const = 0;

    // Mengembalikan command jika pemain melakukan SKIP
    virtual PendingCommand createSkipRewardCommand() const = 0;

    // Fungsi transisi untuk lanjut ke Blind berikutnya
    virtual std::unique_ptr<BlindState> nextState(int& ante) const = 0;
};