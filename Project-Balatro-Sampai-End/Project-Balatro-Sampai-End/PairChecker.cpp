#include "PairChecker.h"
#include <iostream>

HandRank PairChecker::check(const Hand& hand) {
    std::cout << "-> Mengecek Pair...\n";
    if (nextChecker) return nextChecker->check(hand);
    return HandRank::None;
}