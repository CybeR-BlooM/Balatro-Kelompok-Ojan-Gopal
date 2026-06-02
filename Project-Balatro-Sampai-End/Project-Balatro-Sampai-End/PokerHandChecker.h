#pragma once
#include "ChosenHand.h"
#include "GameTypes.h"

class PokerHandChecker {
protected:
    PokerHandChecker* nextChecker = nullptr; // Pointer ke rantai selanjutnya

public:
    virtual ~PokerHandChecker() = default;

    // HANYA DEKLARASI (Tubuhnya kita biarkan di .cpp)
    void setNext(PokerHandChecker* next);

    // Pure virtual function
    virtual HandRank check(const ChosenHand& hand) = 0;
};