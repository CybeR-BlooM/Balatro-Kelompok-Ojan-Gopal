#include "FourOfAKindChecker.h"
#include <iostream>

HandRank FourOfAKindChecker::check(const Hand& hand) {
    std::cout << "-> Mengecek apakah kartu ini Four of a Kind...\n";
    if (hand.forcedRank == HandRank::FourOfAKind) {
        std::cout << "   [!] MATCH! Kombinasi Four of a Kind ditemukan!\n";
        return HandRank::FourOfAKind;
    }
    if (nextChecker) return nextChecker->check(hand);
    return HandRank::None;
}