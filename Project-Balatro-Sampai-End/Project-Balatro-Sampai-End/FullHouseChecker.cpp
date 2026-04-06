#include "FullHouseChecker.h"
#include <iostream>

HandRank FullHouseChecker::check(const Hand& hand) {
    std::cout << "-> Mengecek Full House...\n";
    if (nextChecker) return nextChecker->check(hand);
    return HandRank::None;
}