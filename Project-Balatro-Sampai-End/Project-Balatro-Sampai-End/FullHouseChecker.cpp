#include "FullHouseChecker.h"
#include <iostream>
#include <map>

HandRank FullHouseChecker::check(const Hand& hand) {
    std::cout << "-> Mengecek apakah kartu ini Full House...\n";

    if (hand.cards.size() == 5) {
        std::map<int, int> rankCounts;
        for (const Card& c : hand.cards) {
            rankCounts[c.rank]++;
        }

        bool hasThree = false;
        bool hasPair = false;

        for (auto const& [rank, count] : rankCounts) {
            if (count == 3) {
                hasThree = true;
            } else if (count == 2) {
                hasPair = true;
            }
        }

        // Syarat Full House: Punya 3 kembar DAN 2 kembar di saat bersamaan
        if (hasThree && hasPair) {
            std::cout << "   [!] MATCH! Kombinasi Full House ditemukan!\n";
            return HandRank::FullHouse;
        }
    }

    if (nextChecker) return nextChecker->check(hand);
    return HandRank::None;
}