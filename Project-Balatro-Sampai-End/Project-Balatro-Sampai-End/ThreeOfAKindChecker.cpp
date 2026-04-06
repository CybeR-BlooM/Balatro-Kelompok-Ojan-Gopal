#include "ThreeOfAKindChecker.h"
#include <iostream>

HandRank ThreeOfAKindChecker::check(const Hand& hand) {
    std::cout << "-> Mengecek Three of a Kind...\n";
    if (nextChecker) return nextChecker->check(hand);
    return HandRank::None;
}