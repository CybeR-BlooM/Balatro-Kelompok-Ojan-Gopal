#pragma once
#include "Card.h"
#include <vector>

struct HandState {
    // Menyimpan semua kartu yang ditarik dari Deck (misal: 8 kartu)
    std::vector<Card> cards;

    // Fungsi utilitas untuk mempermudah menambah/menghapus kartu nanti
    void addCard(const Card& card) {
        cards.push_back(card);
    }

    void clearHand() {
        cards.clear();
    }
};