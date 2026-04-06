#include "FlushHouseChecker.h"
#include <iostream>

HandRank FlushHouseChecker::check(const Hand& hand) {
    std::cout << "-> Mengecek Flush House...\n";
    if (nextChecker) return nextChecker->check(hand);
    return HandRank::None;
}