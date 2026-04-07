#include "StraightFlushChecker.h"
#include <iostream>

HandRank StraightFlushChecker::check(const Hand& hand) {
    std::cout << "-> Mengecek apakah kartu ini Straight Flush...\n";
    if (hand.forcedRank == HandRank::StraightFlush) {
        std::cout << "   [!] MATCH! Kombinasi Straight Flush ditemukan!\n";
        return HandRank::StraightFlush;
    }
    if (nextChecker) return nextChecker->check(hand);
    return HandRank::None;
}