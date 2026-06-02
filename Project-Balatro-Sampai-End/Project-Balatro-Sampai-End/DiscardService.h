#pragma once
#include "Deck.h"
#include "HandState.h"
#include <vector>

class DiscardService {
public:
    // Menerima daftar index (posisi) kartu yang ingin dibuang
    void discardCards(HandState& hand, std::vector<int> indicesToDiscard);
};