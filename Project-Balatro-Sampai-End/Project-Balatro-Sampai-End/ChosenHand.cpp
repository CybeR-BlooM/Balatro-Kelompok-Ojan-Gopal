#include "ChosenHand.h"
#include <iostream>

void ChosenHand::addChosenCard(const Card& selectedCard) {
    if (cards.size() < 5) {
        cards.push_back(selectedCard);
    }
    else {
        std::cout << "[Warning] Chosen Hand penuh (Maksimal 5 kartu)!\n";
    }
}

void ChosenHand::printChosenCards() const {
    std::cout << "Kartu yang dimainkan (Chosen Hand):\n";
    for (const Card& c : cards) {
        std::cout << " - Rank: " << c.rank << " | Suit: " << c.suit << "\n";
    }
}