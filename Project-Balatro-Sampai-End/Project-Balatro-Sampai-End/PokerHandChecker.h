#pragma once
#include "Hand.h"
#include "GameTypes.h"

class PokerHandChecker {
protected:
    PokerHandChecker* nextChecker = nullptr; // Pointer ke rantai selanjutnya

public:
    virtual ~PokerHandChecker() = default;

    // Fungsi untuk menyambungkan rantai
    void setNext(PokerHandChecker* next);

    // Pure virtual function: Memaksa semua class turunan (12 Checker) untuk membuat fungsi ini
    virtual HandRank check(const Hand& hand) = 0;
};