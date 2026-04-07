#include "FiveOfAKindChecker.h"
#include <iostream>

HandRank FiveOfAKindChecker::check(const Hand& hand) {
    std::cout << "-> Mengecek apakah kartu ini Five of a Kind...\n";
    if (hand.forcedRank == HandRank::FiveOfAKind) {
        std::cout << "   [!] MATCH! Kombinasi Five of a Kind ditemukan!\n";
        return HandRank::FiveOfAKind;
    }
    if (nextChecker) return nextChecker->check(hand);
    return HandRank::None;
}