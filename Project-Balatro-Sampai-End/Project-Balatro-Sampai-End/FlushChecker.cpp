#include "FlushChecker.h"
#include <iostream>

HandRank FlushChecker::check(const Hand& hand) {
    std::cout << "-> Mengecek apakah kartu ini Flush...\n";
    
    // Pastikan ada 5 kartu yang dimainkan
    if (hand.cards.size() == 5) {
        bool isFlush = true;
        char firstSuit = hand.cards[0].suit; // Ambil warna kartu pertama
        
        // Cek apakah sisa kartunya punya warna yang sama dengan kartu pertama
        for (size_t i = 1; i < hand.cards.size(); ++i) {
            if (hand.cards[i].suit != firstSuit) {
                isFlush = false; // Beda warna? Berarti bukan Flush!
                break;
            }
        }
        
        if (isFlush) {
            std::cout << "   [!] MATCH! Kombinasi Flush (Semua warna " << firstSuit << ") ditemukan!\n";
            return HandRank::Flush;
        }
    }

    // Jika gagal, lempar ke checker di bawahnya (Chain of Responsibility)
    if (nextChecker) return nextChecker->check(hand);
    return HandRank::None;
}