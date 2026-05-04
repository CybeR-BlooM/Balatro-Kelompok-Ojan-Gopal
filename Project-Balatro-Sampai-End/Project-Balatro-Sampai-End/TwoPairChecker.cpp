#include "TwoPairChecker.h"
#include <iostream>
#include <map>

HandRank TwoPairChecker::check(const Hand& hand) {
    std::cout << "-> Mengecek apakah kartu ini Two Pair...\n";

    if (hand.cards.size() == 5) {
        std::map<int, int> rankCounts;
        for (const Card& c : hand.cards) {
            rankCounts[c.rank]++;
        }

        int pairCount = 0; // Penghitung jumlah pasangan
        for (auto const& [rank, count] : rankCounts) {
            if (count == 2) {
                pairCount++;
            }
        }

        if (pairCount == 2) { // Syarat Two Pair: Harus ada tepat 2 pasangan
            std::cout << "   [!] MATCH! Kombinasi Two Pair ditemukan!\n";
            return HandRank::TwoPair;
        }
    }

    if (nextChecker) return nextChecker->check(hand);
    return HandRank::None;
}