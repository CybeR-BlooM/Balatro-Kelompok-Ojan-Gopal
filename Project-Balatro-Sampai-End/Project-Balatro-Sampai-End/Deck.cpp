#include "Deck.h"
#include <algorithm>
#include <stdexcept>
#include <chrono>

Deck::Deck() {
    // Memberikan 'seed' (kunci acak) berdasarkan waktu saat ini agar acakannya selalu berbeda
    unsigned seed = static_cast<unsigned>(std::chrono::system_clock::now().time_since_epoch().count());
    rng = std::mt19937(seed);

    initialize();
    shuffle();
}

void Deck::initialize() {
    cards.clear(); // Bersihkan meja

    // Membuat 52 kartu standar (4 Warna, 13 Angka)
    char suits[] = { 'H', 'D', 'C', 'S' }; // Hearts, Diamonds, Clubs, Spades
    for (char s : suits) {
        for (int r = 2; r <= 14; ++r) { // Angka 2 sampai 14 (As)
            Card c;
            c.suit = s;
            c.rank = r;
            cards.push_back(c);
        }
    }
}

void Deck::shuffle() {
    // Menggunakan std::shuffle dan mt19937 sesuai instruksi TDD
    std::shuffle(cards.begin(), cards.end(), rng);
}

Card Deck::drawCard() {
    if (isEmpty()) {
        throw std::out_of_range("Deck sudah habis! Tidak bisa menarik kartu lagi.");
    }
    // Ambil kartu paling belakang (atas tumpukan)
    Card drawn = cards.back();
    // Hapus kartu tersebut dari tumpukan
    cards.pop_back();

    return drawn;
}

int Deck::size() const {
    return static_cast<int>(cards.size());
}

bool Deck::isEmpty() const {
    return cards.empty();
}