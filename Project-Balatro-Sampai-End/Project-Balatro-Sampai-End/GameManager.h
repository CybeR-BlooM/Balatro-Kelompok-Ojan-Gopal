#pragma once
#include "CoreComponents.h" // Berisi BlindRule & RewardRule
#include "ScoringRule.h"    // Berisi Chain of Responsibility (13 Checker)
#include "HandGenerator.h"  // Berisi Randomizer (Pembuat 8 kartu acak)
#include "HandPlayer.h"     // Berisi pengambil 5 kartu otomatis (ChosenHand)

// === [INJEKSI SISTEM JOKER BARU] ===
#include "JokerManager.h"
#include "ScoreContext.h"
// ===================================

class GameManager {
private:
    // [SISTEM LAMA - 100% DIPERTAHANKAN]
    // Instansiasi semua komponen yang akan bekerja di dalam game loop
    HandGenerator handGenerator;
    HandPlayer handPlayer;
    ScoringRule scoringRule;
    BlindRule blindRule;
    RewardRule rewardRule;

    // === [INJEKSI SISTEM JOKER BARU] ===
    // Menambahkan manajer untuk menampung dan mengeksekusi Joker
    JokerManager jokerManager;
    // ===================================

public:
    // Fungsi utama untuk menjalankan satu putaran game
    void runSession();
};