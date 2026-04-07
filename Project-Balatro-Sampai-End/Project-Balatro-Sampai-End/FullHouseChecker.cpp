#include "FullHouseChecker.h"
#include <iostream>

HandRank FullHouseChecker::check(const Hand& hand) {
    std::cout << "-> Mengecek apakah kartu ini Full House...\n";
    if (hand.forcedRank == HandRank::FullHouse) {
        std::cout << "   [!] MATCH! Kombinasi Full House ditemukan!\n";
        return HandRank::FullHouse;
    }
    if (nextChecker) return nextChecker->check(hand);
    return HandRank::None;
}