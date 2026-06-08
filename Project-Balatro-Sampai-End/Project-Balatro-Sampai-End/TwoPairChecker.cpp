#include "TwoPairChecker.h"
#include <iostream>
#include <map>

HandRank TwoPairChecker::check(const ChosenHand& hand) {
    std::cout << "-> Mengecek apakah kartu ini Two Pair...\n";

    // --- [PERBAIKAN] ---
    // Ubah syarat menjadi >= 4 (karena Two Pair butuh minimal 4 kartu)
    if (hand.cards.size() >= 4) {
        std::map<int, int> rankCounts;
        for (const Card& c : hand.cards) {
            rankCounts[c.rank]++;
        }

        int pairCount = 0;
        for (auto const& [rank, count] : rankCounts) {
            if (count >= 2) {
                pairCount++;
            }
        }

        // Jika menemukan 2 pasang angka yang berbeda
        if (pairCount >= 2) {
            std::cout << "   [!] MATCH! Kombinasi Two Pair ditemukan!\n";
            return HandRank::TwoPair;
        }
    }

    // Jika gagal, lempar ke rantai selanjutnya
    if (nextChecker) return nextChecker->check(hand);
    return HandRank::None;
}