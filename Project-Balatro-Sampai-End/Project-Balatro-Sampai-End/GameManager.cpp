#include "GameManager.h"
#include <iostream>

void GameManager::runSession() {
    std::cout << "========== MEMULAI RONDE BARU ==========\n";

    // Invariant Core Loop (Urutan ini tidak boleh diubah)
    Hand currentHand = handGenerator.generateHand();
    Hand playedHand = handPlayer.generateHand();

    int score = scoringRule.scoreHand(playedHand);

    bool isWin = blindRule.checkBlind(score);
    rewardRule.earnMoney(isWin, score);

    std::cout << "========== RONDE SELESAI ==========\n\n";
}