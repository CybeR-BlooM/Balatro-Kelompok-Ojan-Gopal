#include "FlushChecker.h"
#include <iostream>

HandRank FlushChecker::check(const Hand& hand) {
    std::cout << "-> Mengecek apakah kartu ini Flush...\n";
    if (hand.forcedRank == HandRank::Flush) {
        std::cout << "   [!] MATCH! Kombinasi Flush ditemukan!\n";
        return HandRank::Flush;
    }
    if (nextChecker) return nextChecker->check(hand);
    return HandRank::None;
}