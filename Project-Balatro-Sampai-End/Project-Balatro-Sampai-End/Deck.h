#pragma once
#include "Card.h"
#include <vector>
#include <random>

class Deck {
private:
    std::vector<Card> cards; // Menyimpan tumpukan kartu
    std::mt19937 rng;        // Engine pengacak standar C++ modern

public:
    Deck(); // Constructor

    void initialize();       // Membuat 52 kartu
    void shuffle();          // Mengacak urutan kartu
    Card drawCard();         // Menarik satu kartu teratas
    int size() const;        // Mengecek jumlah sisa kartu
    bool isEmpty() const;    // Mengecek apakah deck sudah habis
};