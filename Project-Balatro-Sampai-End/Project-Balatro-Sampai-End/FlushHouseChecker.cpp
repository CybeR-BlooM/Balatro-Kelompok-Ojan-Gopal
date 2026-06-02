#include "FlushHouseChecker.h"
#include <iostream>
#include <map>

HandRank FlushHouseChecker::check(const ChosenHand& hand) {
    std::cout << "-> Mengecek apakah kartu ini Flush House...\n";

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

        // Syarat 2: Cek Full House menggunakan std::map
        if (isFlush) {
            std::map<int, int> rankCounts;
            for (const Card& c : hand.cards) {
                rankCounts[c.rank]++;
            }

            bool hasThree = false;
            bool hasPair = false;

            for (auto const& [rank, count] : rankCounts) {
                if (count == 3) hasThree = true;
                else if (count == 2) hasPair = true;
            }

            if (hasThree && hasPair) {
                std::cout << "   [!] MATCH! Kombinasi Flush House ditemukan!\n";
                return HandRank::FlushHouse;
            }
        }
    }

    if (nextChecker) return nextChecker->check(hand);
    return HandRank::None;
}