#include "ThreeOfAKindChecker.h"
#include <iostream>
#include <map>

HandRank ThreeOfAKindChecker::check(const ChosenHand& hand) {
    std::cout << "-> Mengecek apakah kartu ini Three of a Kind...\n";

    // --- [PERBAIKAN] ---
    // Butuh minimal 3 kartu untuk bisa membentuk Three of a Kind
    if (hand.cards.size() >= 3) {
        // 1. Membuat Tabel Frekuensi
        std::map<int, int> rankCounts;
        for (const Card& c : hand.cards) {
            rankCounts[c.rank]++;
        }

        // 2. Mengecek isi Tabel Frekuensi
        bool hasThree = false;
        for (auto const& [rank, count] : rankCounts) {
            // --- [PERBAIKAN] ---
            // Jika ada angka yang muncul 3 kali atau lebih
            if (count >= 3) {
                hasThree = true;
                break; // Ketemu Three of a Kind, berhenti mencari
            }
        }

        if (hasThree) {
            std::cout << "   [!] MATCH! Kombinasi Three of a Kind ditemukan!\n";
            return HandRank::ThreeOfAKind;
        }
    }

    // Jika gagal, lempar ke rantai selanjutnya (biasanya Two Pair)
    if (nextChecker) return nextChecker->check(hand);
    return HandRank::None;
}