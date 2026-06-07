#pragma once
// HAPUS #include "Hand.h" karena kita tidak menggunakannya lagi di sini
#include "ChosenHand.h" // TAMBAHKAN struktur data yang baru
#include "GameTypes.h"
#include "PokerHandChecker.h"

class ScoringRule {
private:
    PokerHandChecker* chainRoot; // Menyimpan ujung pertama dari rantai

    // --- [TAMBAHAN BARU: MEMORI EVALUASI] ---
    HandRank lastHandRank = HandRank::None;

public:
    ScoringRule();  // Constructor
    ~ScoringRule(); // Destructor

    // UBAH parameter dari 'const Hand&' menjadi 'const ChosenHand&'
    int scoreHand(const ChosenHand& hand);

    int convertRankToScore(HandRank rank);

    // --- [TAMBAHAN BARU: FUNGSI GETTER] ---
    HandRank getLastEvaluatedHandRank() const {
        return lastHandRank;
    }
};