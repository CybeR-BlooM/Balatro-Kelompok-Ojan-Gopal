#include "RoyalFlushChecker.h"
#include <iostream>

HandRank RoyalFlushChecker::check(const Hand& hand) {
    std::cout << "-> Mengecek apakah kartu ini Royal Flush...\n";
    if (hand.forcedRank == HandRank::RoyalFlush) {
        std::cout << "   [!] MATCH! Kombinasi Royal Flush ditemukan!\n";
        return HandRank::RoyalFlush;
    }
    if (nextChecker) return nextChecker->check(hand);
    return HandRank::None;
}