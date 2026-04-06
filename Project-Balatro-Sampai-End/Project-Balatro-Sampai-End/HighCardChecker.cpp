#include "HighCardChecker.h"
#include <iostream>

HandRank HighCardChecker::check(const Hand& hand) {
    std::cout << "-> Mengecek High Card...\n";
    // Ujung rantai: Selalu me-return High Card tanpa melempar ke nextChecker
    return HandRank::HighCard;
}