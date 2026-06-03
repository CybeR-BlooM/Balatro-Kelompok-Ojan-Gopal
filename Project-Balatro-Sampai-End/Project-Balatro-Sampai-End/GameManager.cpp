#include "GameManager.h"
#include <iostream>

GameManager::GameManager() {
    // Inisialisasi status awal
    playsLeft = 4;
    discardsLeft = 3;
    currentScore = 0;
    blindTarget = 300;

    // Siapkan deck di awal game
    deck.initialize();
    deck.shuffle();
}

void GameManager::displayUI() {
    std::cout << "\n=========================================================\n";
    std::cout << " [ BLIND TARGET: " << blindTarget << " ] | [ CHIPS: " << currentScore << " ] \n";
    std::cout << "=========================================================\n";
    std::cout << " TANGAN KAMU (Sisa Plays: " << playsLeft << " | Sisa Discards: " << discardsLeft << "):\n";

    // Menampilkan isi HandState
    for (size_t i = 0; i < currentHand.cards.size(); ++i) {
        std::cout << " " << (i + 1) << ". [" << currentHand.cards[i].rank << " of " << currentHand.cards[i].suit << "]\n";
    }

    std::cout << "=========================================================\n";
    std::cout << " COMMAND GUIDE:\n";
    std::cout << " - P <nomor> = PLAY kartu    (Contoh: P 1 3 4)\n";
    std::cout << " - D <nomor> = DISCARD kartu (Contoh: D 2 5)\n";
    std::cout << "---------------------------------------------------------\n";
}

void GameManager::runSession() {
    // 1. Tarik 8 kartu di awal sesi sebelum game loop dimulai
    drawService.drawCardsToHand(deck, currentHand, 8);

    bool isGameOver = false;

    // 2. Mulai Game Loop
    while (!isGameOver) {
        // Cek kondisi kalah/menang
        if (currentScore >= blindTarget) {
            std::cout << "\n[!] SELAMAT! KAMU MENGALAHKAN BLIND!\n";
            break;
        }
        if (playsLeft <= 0) {
            std::cout << "\n[!] GAME OVER! Sisa Plays habis dan skor tidak mencapai target.\n";
            break;
        }

        displayUI();

        // 3. Minta input dari pemain (P/D/J)
        PlayerAction action = handPlayer.promptPlayer(currentHand);

        // =======================================================
        // CABANG PLAY
        // =======================================================
        if (action.type == ActionType::PLAY) {
            if (action.selectedIndices.empty()) {
                std::cout << "[!] Pilih minimal 1 kartu untuk dimainkan!\n";
                continue;
            }

            std::cout << "\n--- MEMULAI FASE PLAY ---\n";

            // Pindahkan kartu dari HandState ke ChosenHand (Nampan Eksekusi)
            ChosenHand playedHand = handPlayer.createChosenHand(currentHand, action.selectedIndices);

            // Hitung skor dasar dari kombinasi kartu (Chain of Responsibility)
            int baseScore = scoringRule.scoreHand(playedHand);

            // Masukkan ke konteks untuk di-buff oleh Joker
            ScoreContext context;
            context.chips = baseScore;
            context.mult = 1;

            // --- [PERBAIKAN JOKER] ---
            // Memanggil fungsi Observer milik JokerManager beserta log-nya
            jokerManager.notifyScoreCalculatedWithLog(context);

            // Kalkulasi Final
            int totalScore = context.chips * context.mult;
            std::cout << "=> TOTAL SKOR DIDAPAT: " << totalScore << "\n";
            currentScore += totalScore;

            // Buang kartu yang sudah terpakai dari tangan pemain
            discardService.discardCards(currentHand, action.selectedIndices);

            // Kurangi jatah main & Tarik ulang kartu sampai penuh 8 lagi
            playsLeft--;

            // --- [PERBAIKAN WARNING KUNING] ---
            // Menggunakan static_cast<int> agar C++ tidak komplain soal tipe data size_t
            int cardsNeeded = static_cast<int>(8 - currentHand.cards.size());
            if (cardsNeeded > 0) {
                drawService.drawCardsToHand(deck, currentHand, cardsNeeded);
            }
        }
        // =======================================================
        // CABANG DISCARD
        // =======================================================
        else if (action.type == ActionType::DISCARD) {
            if (discardsLeft <= 0) {
                std::cout << "[!] Jatah DISCARD mu sudah habis!\n";
                continue;
            }
            if (action.selectedIndices.empty()) {
                std::cout << "[!] Pilih minimal 1 kartu untuk dibuang!\n";
                continue;
            }

            std::cout << "\n--- MEMULAI FASE DISCARD ---\n";
            // Buang kartu yang tidak disukai
            discardService.discardCards(currentHand, action.selectedIndices);

            // Kurangi jatah discard & Tarik ulang kartu penggantinya
            discardsLeft--;

            // --- [PERBAIKAN WARNING KUNING] ---
            int cardsNeeded = static_cast<int>(8 - currentHand.cards.size());
            if (cardsNeeded > 0) {
                drawService.drawCardsToHand(deck, currentHand, cardsNeeded);
            }
        }
        // =======================================================
        // INPUT INVALID ATAU JOKER
        // =======================================================
        else if (action.type == ActionType::JOKER_INFO) {
            std::cout << "\n[Info] Fitur lihat Joker belum diimplementasikan.\n";
        }
        else {
            std::cout << "\n[!] Perintah tidak valid. Gunakan huruf P atau D.\n";
        }
    }
}