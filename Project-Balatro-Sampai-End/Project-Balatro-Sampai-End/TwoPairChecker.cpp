#include "TwoPairChecker.h"
#include <iostream>

HandRank TwoPairChecker::check(const Hand& hand) {
    std::cout << "-> Mengecek Two Pair...\n";
    if (nextChecker) return nextChecker->check(hand);
    return HandRank::None;
}