#include "RoyalFlushChecker.h"
#include <iostream>

HandRank RoyalFlushChecker::check(const Hand& hand) {
    std::cout << "-> Mengecek Royal Flush...\n";
    if (nextChecker) return nextChecker->check(hand);
    return HandRank::None;
}