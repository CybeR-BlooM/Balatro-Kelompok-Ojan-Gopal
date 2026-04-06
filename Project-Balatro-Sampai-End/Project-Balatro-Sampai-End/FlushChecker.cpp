#include "FlushChecker.h"
#include <iostream>

HandRank FlushChecker::check(const Hand& hand) {
    std::cout << "-> Mengecek Flush...\n";
    if (nextChecker) return nextChecker->check(hand);
    return HandRank::None;
}