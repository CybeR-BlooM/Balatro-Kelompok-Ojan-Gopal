#include "StraightFlushChecker.h"
#include <iostream>

HandRank StraightFlushChecker::check(const Hand& hand) {
    std::cout << "-> Mengecek Straight Flush...\n";
    if (nextChecker) return nextChecker->check(hand);
    return HandRank::None;
}