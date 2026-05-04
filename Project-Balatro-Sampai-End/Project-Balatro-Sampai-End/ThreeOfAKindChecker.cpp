#include "ThreeOfAKindChecker.h"
#include <iostream>
#include <map>

HandRank ThreeOfAKindChecker::check(const Hand& hand) {
    std::cout << "-> Mengecek apakah kartu ini Three of a Kind...\n";

    if (hand.cards.size() == 5) {
        std::map<int, int> rankCounts;
        for (const Card& c : hand.cards) {
            rankCounts[c.rank]++;
        }

        bool hasThree = false;
        for (auto const& [rank, count] : rankCounts) {
            if (count == 3) {
                hasThree = true;
                break;
            }
        }

        if (hasThree) {
            std::cout << "   [!] MATCH! Kombinasi Three of a Kind ditemukan!\n";
            return HandRank::ThreeOfAKind;
        }
    }

    if (nextChecker) return nextChecker->check(hand);
    return HandRank::None;
}