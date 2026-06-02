#include "GameManager.h"
#include "Blueprintjoker.h" // Masukkan gudang Jokermu
#include <iostream>
#include <random>           // Untuk sistem acak
#include <ctime>            // Untuk seed waktu nyata

// ... (Biarkan constructor GameManager() utuh) ...

void GameManager::runSession() {
    std::cout << "========== MEMULAI RONDE BARU ==========\n";

    // [INJEKSI SISTEM RANDOM JOKER]
    // Kita gunakan waktu saat ini (time(0)) agar hasil acaknya selalu berubah setiap kali di-compile/run
    std::srand(static_cast<unsigned int>(std::time(0)));
    
    // Anggaplah pemain mendapat 1 Joker gratis acak di ronde ini
    int randomJokerID = std::rand() % 5; // Menghasilkan angka 0 sampai 4

    std::cout << "[SISTEM] Pemain mendapatkan 1 Joker Misterius secara acak!\n";
    if (randomJokerID == 0) jokerManager.addJoker(std::make_unique<SlyJoker>());
    else if (randomJokerID == 1) jokerManager.addJoker(std::make_unique<JollyJoker>());
    else if (randomJokerID == 2) jokerManager.addJoker(std::make_unique<CavendishJoker>());
    else if (randomJokerID == 3) jokerManager.addJoker(std::make_unique<ZanyJoker>());
    else if (randomJokerID == 4) jokerManager.addJoker(std::make_unique<MysticJoker>());

    // =========================================================
    // Alur Sistem Lama yang sudah kita buat sebelumnya...
    Hand dealtHand = handGenerator.generateHand();
    ChosenHand playedHand = handPlayer.playHand(dealtHand);
    int score = scoringRule.scoreHand(playedHand);

    ScoreContext context;
    context.chips = score;
    context.mult = 1;
    // PENTING: Untuk testing ZanyJoker, pastikan kamu mengoper HandRank dari ScoringRule ke sini.
    // Jika fungsi scoreHand milikmu tidak mengembalikan HandRank, tidak apa-apa, 
    // Zany Joker cukup akan dilewati (tidak aktif).
    
    // GameManager melempar context tadi ke rak Joker
    jokerManager.notifyScoreCalculatedWithLog(context);

    int finalScore = context.getFinalScore();
    
    bool win = blindRule.checkBlind(finalScore);
    int reward = rewardRule.earnMoney(win, finalScore);

    std::cout << "========== RONDE SELESAI ==========\n\n";
}