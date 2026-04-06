#include "FourOfAKindChecker.h"
#include <iostream>

HandRank FourOfAKindChecker::check(const Hand& hand) {
    std::cout << "-> Mengecek Four of a Kind...\n";
    if (nextChecker) return nextChecker->check(hand);
    return HandRank::None;
}