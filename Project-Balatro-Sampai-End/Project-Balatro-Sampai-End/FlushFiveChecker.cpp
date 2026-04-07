#include "FlushFiveChecker.h"
#include <iostream>

HandRank FlushFiveChecker::check(const Hand& hand) {
    std::cout << "-> Mengecek apakah kartu ini Flush Five...\n";
    if (hand.forcedRank == HandRank::FlushFive) {
        std::cout << "   [!] MATCH! Kombinasi Flush Five ditemukan!\n";
        return HandRank::FlushFive;
    }
    if (nextChecker) return nextChecker->check(hand);
    return HandRank::None;
}