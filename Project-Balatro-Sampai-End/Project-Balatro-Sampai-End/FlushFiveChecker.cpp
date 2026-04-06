#include "FlushFiveChecker.h"
#include <iostream>

HandRank FlushFiveChecker::check(const Hand& hand) {
    std::cout << "-> Mengecek Flush Five...\n";
    // Nanti Programmer Mekanik mengisi logikanya di sini.
    if (nextChecker) return nextChecker->check(hand);
    return HandRank::None;
}