#include "FlushFiveChecker.h"
#include <iostream>
#include <map>

HandRank FlushFiveChecker::check(const Hand& hand) {
    std::cout << "-> Mengecek apakah kartu ini Flush Five...\n";

    if (hand.cards.size() == 5) {
        // Syarat 1: Cek Flush
        bool isFlush = true;
        char firstSuit = hand.cards[0].suit;
        for (size_t i = 1; i < hand.cards.size(); ++i) {
            if (hand.cards[i].suit != firstSuit) {
                isFlush = false;
                break;
            }
        }

        // Syarat 2: Cek Five of a Kind
        if (isFlush) {
            std::map<int, int> rankCounts;
            for (const Card& c : hand.cards) {
                rankCounts[c.rank]++;
            }

            bool hasFive = false;
            for (auto const& [rank, count] : rankCounts) {
                if (count == 5) {
                    hasFive = true;
                    break;
                }
            }

            if (hasFive) {
                std::cout << "   [!] MATCH! Kombinasi Flush Five ditemukan!\n";
                return HandRank::FlushFive;
            }
        }
    }

    if (nextChecker) return nextChecker->check(hand);
    return HandRank::None;
}