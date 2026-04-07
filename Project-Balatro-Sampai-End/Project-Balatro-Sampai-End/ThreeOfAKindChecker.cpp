#include "ThreeOfAKindChecker.h"
#include <iostream>

HandRank ThreeOfAKindChecker::check(const Hand& hand) {
    std::cout << "-> Mengecek apakah kartu ini Three of a Kind...\n";
    if (hand.forcedRank == HandRank::ThreeOfAKind) {
        std::cout << "   [!] MATCH! Kombinasi Three of a Kind ditemukan!\n";
        return HandRank::ThreeOfAKind;
    }
    if (nextChecker) return nextChecker->check(hand);
    return HandRank::None;
}