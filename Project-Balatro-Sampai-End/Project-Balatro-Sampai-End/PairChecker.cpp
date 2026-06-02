#include "PairChecker.h"
#include <iostream>
#include <map> // Wajib di-include untuk menggunakan Tabel Frekuensi

HandRank PairChecker::check(const ChosenHand& hand) {
    std::cout << "-> Mengecek apakah kartu ini Pair...\n";

    if (hand.cards.size() == 5) {
        // 1. Membuat Tabel Frekuensi
        std::map<int, int> rankCounts;
        for (const Card& c : hand.cards) {
            rankCounts[c.rank]++;
        }

        // 2. Mengecek isi Tabel Frekuensi
        bool isPair = false;
        // Format [rank, count] adalah fitur C++ modern untuk membaca map dengan mudah
        for (auto const& [rank, count] : rankCounts) {
            if (count == 2) {
                isPair = true;
                break; // Ketemu 1 Pair, langsung berhenti mencari
            }
        }

        if (isPair) {
            std::cout << "   [!] MATCH! Kombinasi Pair ditemukan!\n";
            return HandRank::Pair;
        }
    }

    // Jika gagal, lempar ke rantai selanjutnya (High Card)
    if (nextChecker) return nextChecker->check(hand);
    return HandRank::None;
}