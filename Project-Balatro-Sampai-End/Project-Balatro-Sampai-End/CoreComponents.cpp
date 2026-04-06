#include "CoreComponents.h"
#include <iostream>

Hand HandGenerator::generateHand() {
    std::cout << "[Fase 1] Sistem membagikan kartu ke pemain...\n";
    return Hand();
}

Hand HandPlayer::generateHand() {
    std::cout << "[Fase 2] Pemain memilih kartu untuk dimainkan...\n";
    return Hand();
}

bool BlindRule::checkBlind(int score) {
    std::cout << "[Fase 4] Mengecek apakah Skor (" << score << ") mengalahkan Blind (Target: 1000)...\n";
    return score >= 1000;
}

int RewardRule::earnMoney(bool win, int score) {
    if (win) {
        std::cout << "[Fase 5] ROUND WON! Pemain mendapatkan reward $5.\n";
        return 5;
    }
    else {
        std::cout << "[Fase 5] ROUND LOST! Game Over.\n";
        return 0;
    }
}