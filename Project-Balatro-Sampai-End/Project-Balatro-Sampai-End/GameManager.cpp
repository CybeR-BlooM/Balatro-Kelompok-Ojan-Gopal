#include "GameManager.h"
#include <iostream>

GameManager::GameManager() {
    // Inisialisasi awal sesuai spesifikasi RunSessionState
    sessionState.ante = 1;
    sessionState.totalScore = 0;
    sessionState.remainingPlays = 4;
    sessionState.remainingDiscards = 3;
    sessionState.freeRerolls = 0;
    sessionState.money = 0; // Uang awal pemain

    // Set awal permainan dimulai dari Small Blind State
    sessionState.currentBlind = std::make_unique<SmallBlindState>();

    // Siapkan deck di awal game
    deck.initialize();
    deck.shuffle();
}

void GameManager::executePendingCommands(CommandTiming timing) {
    // Melakukan looping ke semua command yang disimpan di vector state
    for (auto& pending : sessionState.pendingCommands) {
        if (!pending.executed && pending.timing == timing) {
            if (pending.command) {
                std::cout << "[REWARD] Mengaktifkan efek: " << pending.command->getName()
                    << " (" << pending.command->getDescription() << ")\n";
                pending.command->execute(sessionState);
            }
            pending.executed = true; // Tandai agar tidak dieksekusi dua kali
        }
    }
}

void GameManager::startNewBlind() {
    // Cek apakah ada reward tertunda yang tipenya "NextBlind" untuk dieksekusi sekarang
    executePendingCommands(CommandTiming::NextBlind);

    // Tarik kartu sampai tangan penuh (8 kartu)
    int cardsNeeded = static_cast<int>(8 - currentHand.cards.size());
    if (cardsNeeded > 0) {
        drawService.drawCardsToHand(deck, currentHand, cardsNeeded);
    }
}

void GameManager::displayUI() {
    int targetScore = sessionState.currentBlind->getTargetScore(sessionState.ante);

    std::cout << "\n=========================================================\n";
    std::cout << " ANTE: " << sessionState.ante << " | " << sessionState.currentBlind->getName() << "\n";
    std::cout << " [ TARGET SKOR: " << targetScore << " ] | [ SKOR KAMU: " << sessionState.totalScore << " ] \n";
    std::cout << " [ DOMPET: $" << sessionState.money << " ] | [ REROLL GRATIS: " << sessionState.freeRerolls << " ]\n";
    std::cout << "=========================================================\n";
    std::cout << " TANGAN KAMU (Sisa Plays: " << sessionState.remainingPlays
        << " | Sisa Discards: " << sessionState.remainingDiscards << "):\n";

    // Menampilkan isi HandState
    for (size_t i = 0; i < currentHand.cards.size(); ++i) {
        std::cout << " " << (i + 1) << ". [" << currentHand.cards[i].rank << " of " << currentHand.cards[i].suit << "]\n";
    }

    std::cout << "=========================================================\n";
    std::cout << " COMMAND GUIDE:\n";
    std::cout << " - P <nomor> = PLAY kartu    (Contoh: P 1 3 4)\n";
    std::cout << " - D <nomor> = DISCARD kartu (Contoh: D 2 5)\n";
    std::cout << " - S         = SKIP Blind & Ambil Tag Reward\n";
    std::cout << "---------------------------------------------------------\n";
}

void GameManager::runSession() {
    std::cout << "=== MEMULAI SESI BALATRO (STATE, COMMAND & SHOP UNIFIED) ===\n";
    startNewBlind();

    while (true) {
        int targetScore = sessionState.currentBlind->getTargetScore(sessionState.ante);

        // Cek kondisi menang Blind normal
        if (sessionState.totalScore >= targetScore) {
            std::cout << "\n[!] BERHASIL! Kamu melewati " << sessionState.currentBlind->getName() << "!\n";

            // --- [LOGIKA UANG & SHOP] ---
            int rewardMoney = sessionState.currentBlind->getRewardMoney();
            sessionState.money += rewardMoney;
            std::cout << "[!] Mendapatkan Uang Hadiah: $" << rewardMoney << "\n";
            std::cout << "[!] Total Uang Sekarang: $" << sessionState.money << "\n";

            std::cout << "\n--- MEMASUKI FASE TOKO/SHOP ---\n";
            // Jalankan command tertunda yang aktif saat masuk Shop (misal: Free Reroll)
            executePendingCommands(CommandTiming::NextShop);

            // Buka Shop UI
            shopSystem.enterShop(sessionState, jokerManager);

            // Transisi ke State Blind Berikutnya melalui State Pattern
            sessionState.currentBlind = sessionState.currentBlind->nextState(sessionState.ante);
            sessionState.totalScore = 0; // Reset skor untuk blind berikutnya

            // Kembalikan resources default setiap ganti blind
            sessionState.remainingPlays = 4;
            sessionState.remainingDiscards = 3;

            startNewBlind();
            continue;
        }

        // --- [PERBAIKAN KONDISI KALAH] ---
        bool outOfPlays = (sessionState.remainingPlays <= 0);
        bool completelyOutOfCards = (currentHand.cards.empty() && deck.isEmpty());

        if (outOfPlays || completelyOutOfCards) {
            std::cout << "\n=========================================================\n";
            std::cout << "[!] GAME OVER!\n";
            if (outOfPlays) std::cout << "=> Jatah Plays kamu sudah habis.\n";
            if (completelyOutOfCards) std::cout << "=> Kamu kehabisan seluruh kartu (Deck dan Tangan kosong).\n";
            std::cout << "=> Skor Akhir: " << sessionState.totalScore << " / Target: " << targetScore << "\n";
            std::cout << "=========================================================\n";
            break;
        }

        displayUI();
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

            // Memanggil fungsi Observer milik JokerManager beserta log-nya
            jokerManager.notifyScoreCalculatedWithLog(context);

            // Kalkulasi Final
            int totalScore = context.chips * context.mult;
            std::cout << "=> TOTAL SKOR DIDAPAT: " << totalScore << "\n";
            sessionState.totalScore += totalScore;

            // Buang kartu yang sudah terpakai dari tangan pemain
            discardService.discardCards(currentHand, action.selectedIndices);

            // Kurangi jatah main & Tarik ulang kartu sampai penuh 8 lagi
            sessionState.remainingPlays--;

            int cardsNeeded = static_cast<int>(8 - currentHand.cards.size());
            if (cardsNeeded > 0) {
                drawService.drawCardsToHand(deck, currentHand, cardsNeeded);
            }
        }
        // =======================================================
        // CABANG DISCARD
        // =======================================================
        else if (action.type == ActionType::DISCARD) {
            if (sessionState.remainingDiscards <= 0) {
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
            sessionState.remainingDiscards--;

            int cardsNeeded = static_cast<int>(8 - currentHand.cards.size());
            if (cardsNeeded > 0) {
                drawService.drawCardsToHand(deck, currentHand, cardsNeeded);
            }
        }
        // =======================================================
        // CABANG SKIP BLIND (COMMAND PATTERN ACTION)
        // =======================================================
        else if (action.type == ActionType::SKIP) {
            if (sessionState.currentBlind->getName() == "Boss Blind") {
                std::cout << "[!] Boss Blind tidak bisa di-skip!\n";
                continue;
            }

            std::cout << "\n[SKIP] Kamu memilih melompati " << sessionState.currentBlind->getName() << "!\n";

            // BlindState menciptakan RewardCommand khusus (Command Pattern)
            PendingCommand skipReward = sessionState.currentBlind->createSkipRewardCommand();

            // Jika reward valid, simpan ke penampungan deferred execution
            if (skipReward.command != nullptr) {
                std::cout << "[!] Reward Diperoleh: " << skipReward.command->getName()
                    << " (Akan aktif pada fase yang tepat)\n";
                sessionState.pendingCommands.push_back(std::move(skipReward));
            }

            // Langsung jalankan Immediate command jika ada
            executePendingCommands(CommandTiming::Immediate);

            // Transisi ke State Blind berikutnya tanpa bermain
            sessionState.currentBlind = sessionState.currentBlind->nextState(sessionState.ante);
            sessionState.totalScore = 0; // Reset skor untuk blind baru

            // Kembalikan resources default setiap ganti blind
            sessionState.remainingPlays = 4;
            sessionState.remainingDiscards = 3;

            startNewBlind();
        }
        // =======================================================
        // INPUT INVALID ATAU JOKER
        // =======================================================
        else if (action.type == ActionType::JOKER_INFO) {
            std::cout << "\n[Info] Fitur lihat Joker belum diimplementasikan.\n";
        }
        else {
            std::cout << "\n[!] Perintah tidak valid. Gunakan huruf P, D, J, atau S (Maksimal 5 angka).\n";
        }
    }
}