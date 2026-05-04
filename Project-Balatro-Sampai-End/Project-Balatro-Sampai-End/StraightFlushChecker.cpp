#include "StraightFlushChecker.h"
#include <iostream>
#include <vector>
#include <algorithm>

HandRank StraightFlushChecker::check(const Hand& hand) {
    std::cout << "-> Mengecek apakah kartu ini Straight Flush...\n";

    if (hand.cards.size() == 5) {
        // Syarat 1: Cek Flush (Warna sama semua)
        bool isFlush = true;
        char firstSuit = hand.cards[0].suit;
        for (size_t i = 1; i < hand.cards.size(); ++i) {
            if (hand.cards[i].suit != firstSuit) {
                isFlush = false;
                break;
            }
        }

        // Jika dia Flush, mari kita lanjut Syarat 2: Cek Straight (Berurutan)
        if (isFlush) {
            std::vector<int> ranks;
            for (const Card& c : hand.cards) ranks.push_back(c.rank);

            std::sort(ranks.begin(), ranks.end());

            bool isStraight = true;
            for (size_t i = 1; i < ranks.size(); ++i) {
                if (ranks[i] != ranks[i - 1] + 1) {
                    isStraight = false;
                    break;
                }
            }

            // Jika lulus keduanya, maka ini adalah Straight Flush!
            if (isStraight) {
                std::cout << "   [!] MATCH! Kombinasi Straight Flush ditemukan!\n";
                return HandRank::StraightFlush;
            }
        }
    }

    if (nextChecker) return nextChecker->check(hand);
    return HandRank::None;
}