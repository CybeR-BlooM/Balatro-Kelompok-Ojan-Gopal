#include "StraightChecker.h"
#include <iostream>
#include <vector>
#include <algorithm> // Wajib di-include untuk menggunakan std::sort

HandRank StraightChecker::check(const Hand& hand) {
    std::cout << "-> Mengecek apakah kartu ini Straight...\n";

    // Pastikan kartu yang dimainkan tepat 5 kartu
    if (hand.cards.size() == 5) {
        
        // LANGKAH 1: Ekstraksi Angka
        // Kita buat keranjang baru khusus untuk menampung angka (rank) saja
        std::vector<int> ranks;
        for (const Card& c : hand.cards) {
            ranks.push_back(c.rank);
        }

        // LANGKAH 2: Pengurutan (Sorting)
        // Fungsi ini akan mengurutkan isi 'ranks' dari yang paling kecil ke paling besar
        // Contoh awal: [10, 8, 9, 12, 11] -> Setelah disort: [8, 9, 10, 11, 12]
        std::sort(ranks.begin(), ranks.end());

        // LANGKAH 3: Pengecekan Jarak (Distance Check)
        bool isStraight = true;
        // Kita mulai looping dari indeks 1 (kartu kedua) untuk dibandingkan dengan indeks sebelumnya
        for (size_t i = 1; i < ranks.size(); ++i) {
            // Syarat Straight: Angka saat ini HARUS SAMA DENGAN angka sebelumnya + 1
            if (ranks[i] != ranks[i - 1] + 1) {
                isStraight = false; // Jika selisihnya bukan 1 (loncat) atau malah kembar, langsung gagalkan!
                break;
            }
        }

        if (isStraight) {
            std::cout << "   [!] MATCH! Kombinasi Straight ditemukan!\n";
            return HandRank::Straight;
        }
    }

    // Jika gagal (bukan Straight), lempar ke rantai Checker selanjutnya
    if (nextChecker) return nextChecker->check(hand);
    return HandRank::None;
}