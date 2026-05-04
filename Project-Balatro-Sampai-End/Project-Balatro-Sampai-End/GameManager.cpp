#include "GameManager.h"
#include <iostream>

void GameManager::runSession() {
    std::cout << "========== MEMULAI RONDE BARU ==========\n";

    // Langkah 1: Generate kartu acak 
    // HandGenerator membuat 52 deck, dikocok, lalu membagikan 8 kartu ke pemain
    Hand dealtHand = handGenerator.generateHand();

    // Langkah 2: Player memilih kartu untuk dimainkan
    // GameManager melempar 8 kartu tadi ke HandPlayer. 
    // HandPlayer versi dummy kita akan otomatis mengambil 5 kartu pertama
    // dan menyimpannya di dalam wadah baru bernama ChosenHand.
    ChosenHand playedHand = handPlayer.playHand(dealtHand);

    // Langkah 3: Hitung Base Score (Skor Dasar)
    // GameManager melempar ChosenHand (5 kartu pilihan) ke dalam ScoringRule.
    // Di dalam ScoringRule, kartu ini akan masuk ke Chain of Responsibility (13 Checker).
    int score = scoringRule.scoreHand(playedHand);

    // Langkah 4: Cek Win/Lose melawan Blind (Target Skor)
    // GameManager mengecek apakah skor dari kartu tadi memenuhi target menang
    bool win = blindRule.checkBlind(score);

    // Langkah 5: Kalkulasi Hadiah (Reward)
    // Jika menang (true), beri uang. Jika kalah (false), dapat 0.
    int reward = rewardRule.earnMoney(win, score);

    std::cout << "========== RONDE SELESAI ==========\n\n";
}