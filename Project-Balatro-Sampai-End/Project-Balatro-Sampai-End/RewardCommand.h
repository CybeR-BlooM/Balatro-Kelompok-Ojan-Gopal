#pragma once
#include <string>
#include <memory>
#include "RunSessionState.h"

// Enum untuk menentukan kapan reward dieksekusi
enum class CommandTiming {
    Immediate,
    NextBlind,
    NextShop,
    NextAnte
};

// Interface utama untuk Command
class RewardCommand {
public:
    virtual ~RewardCommand() = default;
    virtual std::string getName() const = 0;
    virtual std::string getDescription() const = 0;

    // Command akan memodifikasi state sesi saat dieksekusi
    virtual void execute(RunSessionState& state) = 0;
};

// Pembungkus Command agar bisa dieksekusi nanti
struct PendingCommand {
    CommandTiming timing;
    bool executed = false;
    std::unique_ptr<RewardCommand> command;
};