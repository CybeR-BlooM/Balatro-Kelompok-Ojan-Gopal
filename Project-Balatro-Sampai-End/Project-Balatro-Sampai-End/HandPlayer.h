#pragma once
#include "Hand.h"
#include "ChosenHand.h"

class HandPlayer {
public:
    // Fungsi ini menerima 8 kartu dari HandGenerator, 
    // lalu mengembalikan ChosenHand (maksimal 5 kartu).
    ChosenHand playHand(const Hand& dealtHand);
};