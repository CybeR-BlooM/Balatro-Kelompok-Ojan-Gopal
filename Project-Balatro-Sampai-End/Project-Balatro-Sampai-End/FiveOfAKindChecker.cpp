#include "FiveOfAKindChecker.h"
#include <iostream>
#include <map>

// === [PERUBAHAN HANYA DI BARIS INI] ===
HandRank FiveOfAKindChecker::check(const ChosenHand& hand) {
    std::cout << "-> Mengecek apakah kartu ini Five of a Kind...\n";

    if (hand.cards.size() == 5) {
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
            std::cout << "   [!] MATCH! Kombinasi Five of a Kind ditemukan!\n";
            return HandRank::FiveOfAKind;
        }
    }

    if (nextChecker) return nextChecker->check(hand);
    return HandRank::None;
}