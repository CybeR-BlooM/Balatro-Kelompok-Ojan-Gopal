#pragma once
#include "Deck.h"
#include "HandState.h"

class DrawService {
public:
    // Fungsi untuk menarik sejumlah kartu dari deck ke tangan pemain
    void drawCardsToHand(Deck& deck, HandState& hand, int amount);
};