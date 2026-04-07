#include "FlushHouseChecker.h"
#include <iostream>

HandRank FlushHouseChecker::check(const Hand& hand) {
    std::cout << "-> Mengecek apakah kartu ini Flush House...\n";
    if (hand.forcedRank == HandRank::FlushHouse) {
        std::cout << "   [!] MATCH! Kombinasi Flush House ditemukan!\n";
        return HandRank::FlushHouse;
    }
    if (nextChecker) return nextChecker->check(hand);
    return HandRank::None;
}