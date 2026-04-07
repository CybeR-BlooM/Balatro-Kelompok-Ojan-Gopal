#include "TwoPairChecker.h"
#include <iostream>

HandRank TwoPairChecker::check(const Hand& hand) {
    std::cout << "-> Mengecek apakah kartu ini Two Pair...\n";
    if (hand.forcedRank == HandRank::TwoPair) {
        std::cout << "   [!] MATCH! Kombinasi Two Pair ditemukan!\n";
        return HandRank::TwoPair;
    }
    if (nextChecker) return nextChecker->check(hand);
    return HandRank::None;
}