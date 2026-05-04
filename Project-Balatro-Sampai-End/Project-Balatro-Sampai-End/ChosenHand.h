#pragma once
#include "Hand.h"

struct ChosenHand : public Hand {
    // Hanya menyebutkan nama fungsinya saja (Buku Menu)
    void addChosenCard(const Card& selectedCard);
    void printChosenCards() const;
};