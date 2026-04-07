#include "PairChecker.h"
#include <iostream>

HandRank PairChecker::check(const Hand& hand) {
    std::cout << "-> Mengecek apakah kartu ini Pair...\n";
    if (hand.forcedRank == HandRank::Pair) {
        std::cout << "   [!] MATCH! Kombinasi Pair ditemukan!\n";
        return HandRank::Pair;
    }
    if (nextChecker) return nextChecker->check(hand);
    return HandRank::None;
}