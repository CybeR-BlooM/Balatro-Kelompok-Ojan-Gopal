#pragma once

#include "Card.h"
#include "GameTypes.h" // Asumsi HandRank milikmu disimpan di file ini
#include <vector>

struct ScoreContext {
    // 1. Data Input (Bahan Baku)
    std::vector<Card> cards;
    HandRank handType = HandRank::None; // Disamakan dengan sistem 13 Checker-mu

    // 2. Data Modifikasi (Bumbu yang akan diubah Joker)
    int level = 0;
    int chips = 0;
    int mult = 0;

    // 3. Fungsi Output (Hasil Akhir)
    int getFinalScore() const {
        return chips * mult;
    }
};