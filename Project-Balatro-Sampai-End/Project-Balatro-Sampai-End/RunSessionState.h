#pragma once
#include <memory>
#include <vector>

// Forward declarations untuk menghindari circular dependency
class BlindState;
struct PendingCommand;

// Sesuai dengan spesifikasi TDD
struct RunSessionState {
    int ante = 1;
    int totalScore = 0;
    int remainingPlays = 4;
    int remainingDiscards = 3;
    int freeRerolls = 0;

    std::unique_ptr<BlindState> currentBlind;
    std::vector<PendingCommand> pendingCommands;
};