#include "FourOfAKindChecker.h"
#include <iostream>
#include <map>

HandRank FourOfAKindChecker::check(const Hand& hand) {
    std::cout << "-> Mengecek apakah kartu ini Four of a Kind...\n";

    if (hand.cards.size() == 5) {
        std::map<int, int> rankCounts;
        for (const Card& c : hand.cards) {
            rankCounts[c.rank]++;
        }

        bool hasFour = false;
        for (auto const& [rank, count] : rankCounts) {
            if (count == 4) {
                hasFour = true;
                break;
            }
        }

        if (hasFour) {
            std::cout << "   [!] MATCH! Kombinasi Four of a Kind ditemukan!\n";
            return HandRank::FourOfAKind;
        }
    }

    if (nextChecker) return nextChecker->check(hand);
    return HandRank::None;
}