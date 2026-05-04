#include "HandGenerator.h"
#include <iostream>
#include <vector>
#include <algorithm> // Untuk fungsi std::shuffle (mengocok array)
#include <random>    // Untuk mesin pembuat angka acak (RNG)

Hand HandGenerator::generateHand() {
    std::cout << "=> Generating random hand...\n";

    // 1. Persiapan: Buat Deck kosong dan daftar tipe Suit
    std::vector<Card> deck;
    char suits[] = { 'H', 'D', 'C', 'S' }; // Hati, Wajik, Keriting, Sekop

    // 2. Isi Deck dengan 52 kartu standar (Rank 2 sampai 14 untuk setiap Suit)
    for (char suit : suits) {
        for (int rank = 2; rank <= 14; ++rank) {
            deck.push_back({ rank, suit });
        }
    }

    // 3. Mesin Pengocok (RNG - Random Number Generator)
    // std::random_device bertugas mengambil "seed" acak dari hardware komputermu
    std::random_device rd;
    std::mt19937 g(rd());  // mt19937 adalah algoritma RNG standar industri di C++

    // Kocok urutan kartu di dalam deck
    std::shuffle(deck.begin(), deck.end(), g);

    // 4. Bagikan kartu ke Hand pemain
    Hand hand;
    // Misalnya di Balatro pemain dibagikan 8 kartu di awal
    int cardsToDeal = 8;
    for (int i = 0; i < cardsToDeal; ++i) {
        hand.cards.push_back(deck[i]);

        // (Opsional) Print kartu yang dibagikan agar kamu bisa melihat hasilnya di terminal
        std::cout << "   Dapat Kartu: Rank " << deck[i].rank << ", Suit " << deck[i].suit << "\n";
    }

    return hand;
}