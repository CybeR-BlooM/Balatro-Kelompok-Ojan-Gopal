#pragma once
// Hapus #include "HandGenerator.h" jika masih ada
#include "Deck.h"
#include "HandState.h"
#include "HandPlayer.h"
#include "DrawService.h"
#include "DiscardService.h"
#include "ScoringRule.h"
#include "JokerManager.h"
#include "ScoreContext.h"

class GameManager {
private:
    // --- KOMPONEN SISTEM BARU ---
    Deck deck;
    HandState currentHand;
    HandPlayer handPlayer;
    DrawService drawService;
    DiscardService discardService;
    ScoringRule scoringRule;
    JokerManager jokerManager;

    // --- VARIABEL STATUS GAME ---
    int playsLeft;
    int discardsLeft;
    int currentScore;
    int blindTarget;

    // Fungsi untuk menampilkan UI ke layar
    void displayUI();

public:
    GameManager();
    void runSession();
};