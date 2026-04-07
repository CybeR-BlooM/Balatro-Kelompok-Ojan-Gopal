#include "StraightChecker.h"
#include <iostream>

HandRank StraightChecker::check(const Hand& hand) {
    std::cout << "-> Mengecek apakah kartu ini Straight...\n";
    if (hand.forcedRank == HandRank::Straight) {
        std::cout << "   [!] MATCH! Kombinasi Straight ditemukan!\n";
        return HandRank::Straight;
    }
    if (nextChecker) return nextChecker->check(hand);
    return HandRank::None;
}