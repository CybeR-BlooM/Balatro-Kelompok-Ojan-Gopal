#include "RoyalFlushChecker.h"
#include <iostream>
#include <vector>
#include <algorithm>

HandRank RoyalFlushChecker::check(const ChosenHand& hand) {
    std::cout << "-> Mengecek apakah kartu ini Royal Flush...\n";

    if (hand.cards.size() == 5) {
        bool isFlush = true;
        char firstSuit = hand.cards[0].suit;
        for (size_t i = 1; i < hand.cards.size(); ++i) {
            if (hand.cards[i].suit != firstSuit) {
                isFlush = false;
                break;
            }
        }

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

            // Syarat Tambahan (Royal): Karena sudah disortir, index ke-0 (paling kecil) harus 10
            if (isStraight && ranks[0] == 10) {
                std::cout << "   [!] MATCH! Kombinasi ROYAL FLUSH ditemukan!\n";
                return HandRank::RoyalFlush;
            }
        }
    }

    if (nextChecker) return nextChecker->check(hand);
    return HandRank::None;
}