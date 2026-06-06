#pragma once
#include "Deck.h"
#include "HandState.h"
#include "HandPlayer.h"
#include "DrawService.h"
#include "DiscardService.h"
#include "ScoringRule.h"
#include "JokerManager.h"
#include "ScoreContext.h"
#include "RunSessionState.h" // Sesuai TDD
#include "ConcreteBlinds.h"  // Untuk inisialisasi awal SmallBlind
#include "RewardCommand.h"

class GameManager {
private:
    // --- STATE UTAMA UTK SESI INI ---
    RunSessionState sessionState;

    // --- SERVICE / INFRASTRUKTUR ---
    Deck deck;
    HandState currentHand;
    HandPlayer handPlayer;
    DrawService drawService;
    DiscardService discardService;
    ScoringRule scoringRule;
    JokerManager jokerManager;

    // --- FUNGSI INTERNAL UTK MANAGING COMMANDS & UI ---
    void displayUI();
    void executePendingCommands(CommandTiming timing);
    void startNewBlind();

public:
    GameManager();
    void runSession();
};