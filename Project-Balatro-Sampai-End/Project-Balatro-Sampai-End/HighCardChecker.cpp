#include "HighCardChecker.h"
#include <iostream>

HandRank HighCardChecker::check(const Hand& hand) {
    std::cout << "-> Mengecek apakah kartu ini High Card...\n";
    std::cout << "   [!] Mentok di bawah. Tidak ada kombinasi. Ini adalah High Card!\n";
    return HandRank::HighCard; 
}