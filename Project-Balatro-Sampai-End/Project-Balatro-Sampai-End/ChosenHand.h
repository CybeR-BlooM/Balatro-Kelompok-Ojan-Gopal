#pragma once
#include "Hand.h"
#include <iostream>

// Karena ChosenHand pada dasarnya adalah "Kumpulan Kartu" juga,
// kita bisa menggunakan konsep Inheritance (Pewarisan) dari struct Hand.
struct ChosenHand : public Hand {

    // Fungsi untuk memindahkan kartu pilihan player ke ChosenHand
    void addChosenCard(const Card& selectedCard) {
        // Balatro maksimal hanya membolehkan 5 kartu untuk di-play
        if (cards.size() < 5) {
            cards.push_back(selectedCard);
        }
        else {
            std::cout << "[Warning] Chosen Hand sudah penuh (Maksimal 5 kartu)!\n";
        }
    }

    // Fungsi tambahan untuk mempermudah pengecekan di terminal
    void printChosenCards() {
        std::cout << "Kartu yang akan dimainkan (Chosen Hand):\n";
        for (const Card& c : cards) {
            std::cout << " - Rank: " << c.rank << " | Suit: " << c.suit << "\n";
        }
    }
};