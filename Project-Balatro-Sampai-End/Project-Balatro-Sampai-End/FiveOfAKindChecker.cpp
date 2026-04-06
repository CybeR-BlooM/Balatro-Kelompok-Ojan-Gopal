#include "FiveOfAKindChecker.h"
#include <iostream>

HandRank FiveOfAKindChecker::check(const Hand& hand) {
    std::cout << "-> Mengecek Five of a Kind...\n";
    if (nextChecker) return nextChecker->check(hand);
    return HandRank::None;
}