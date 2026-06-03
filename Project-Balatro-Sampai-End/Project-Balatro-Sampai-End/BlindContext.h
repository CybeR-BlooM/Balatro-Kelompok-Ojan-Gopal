#pragma once
#include "BlindState.h"
#include <memory>
#include <iostream>

class BlindContext {
private:
    std::unique_ptr<BlindState> currentState;
    int currentAnte;

public:
    BlindContext(int startingAnte = 1) : currentAnte(startingAnte) {}

    // Mengganti baju (State) Blind saat ini
    void setState(std::unique_ptr<BlindState> newState) {
        currentState = std::move(newState);
        std::cout << "\n[!] Memasuki " << currentState->getName()
            << " (Target: " << currentState->getTargetScore(currentAnte) << ")\n";
    }

    BlindState* getCurrentState() const {
        return currentState.get();
    }

    int getAnte() const { return currentAnte; }
    void increaseAnte() { currentAnte++; }

    // Lanjut ke Blind berikutnya
    void advanceBlind() {
        if (currentState) {
            currentState->handleNextBlind(this);
        }
    }
};