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

    // ====================================================================
    // [SISTEM BARU - INJEKSI JOKER MULAI DI SINI]
    // ====================================================================

    // 3A. Pembuatan Wadah (ScoreContext)
    ScoreContext context;

    // 3B. Menjembatani Sistem Lama ke Sistem Baru
    // Karena ScoringRule lama milikmu mengembalikan 'int score', kita jadikan score 
    // tersebut sebagai base Chips. Mult kita set 1, agar (score * 1) = nilai aslinya.
    context.chips = score;
    context.mult = 1;
    context.handType = HandRank::None; // Nilai default, bisa di-update nanti jika ScoringRule dimodifikasi

    // 3C. Eksekusi Stasiun Radio Joker (Decorator Bekerja)
    // GameManager melempar context tadi ke rak Joker untuk dikali-kalikan.
    jokerManager.notifyScoreCalculatedWithLog(context);

    // 3D. Ambil Hasil Akhir
    int finalScore = context.getFinalScore();

    // ====================================================================
    // [SISTEM BARU - INJEKSI JOKER SELESAI]
    // ====================================================================

    // Langkah 4: Cek Win/Lose melawan Blind (Target Skor)
    // [MODIFIKASI KECIL]: Kita ganti 'score' lama dengan 'finalScore' hasil olahan Joker
    bool win = blindRule.checkBlind(finalScore);

    // Langkah 5: Kalkulasi Hadiah (Reward)
    // [MODIFIKASI KECIL]: Sama seperti di atas, kita gunakan 'finalScore'
    int reward = rewardRule.earnMoney(win, finalScore);

    std::cout << "========== RONDE SELESAI ==========\n\n";
}