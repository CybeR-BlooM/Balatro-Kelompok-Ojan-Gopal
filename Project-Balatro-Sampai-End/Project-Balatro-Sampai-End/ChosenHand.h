#pragma once
#include "Card.h"
#include <vector>

struct ChosenHand {
    // TDD: Menyimpan hanya kartu yang dipilih untuk dinilai [cite: 111-112]
    std::vector<Card> cards;

    // Kembalikan deklarasi fungsi lamamu agar ChosenHand.cpp dan HandPlayer tidak error
    void addChosenCard(const Card& card);
    void printChosenCards() const;
};