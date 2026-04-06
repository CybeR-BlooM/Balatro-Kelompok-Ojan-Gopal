#include "StraightChecker.h"
#include <iostream>

HandRank StraightChecker::check(const Hand& hand) {
    std::cout << "-> Mengecek Straight...\n";
    if (nextChecker) return nextChecker->check(hand);
    return HandRank::None;
}