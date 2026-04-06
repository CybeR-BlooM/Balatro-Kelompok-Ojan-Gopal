#include "ScoringRule.h"
#include <iostream>

// --- PROGRAMMER SISTEM HARUS MENG-INCLUDE SEMUA 13 FILE DI SINI ---
#include "FlushFiveChecker.h"
#include "FlushHouseChecker.h"
#include "FiveOfAKindChecker.h"
#include "RoyalFlushChecker.h"
#include "StraightFlushChecker.h"
#include "FourOfAKindChecker.h"
#include "FullHouseChecker.h"
#include "FlushChecker.h"
#include "StraightChecker.h"
#include "ThreeOfAKindChecker.h"
#include "TwoPairChecker.h"
#include "PairChecker.h"
#include "HighCardChecker.h"

ScoringRule::ScoringRule() {
    // 1. Instansiasi (Membuat objek) dari ke-13 Checker
    PokerHandChecker* flushFive = new FlushFiveChecker();
    PokerHandChecker* flushHouse = new FlushHouseChecker();
    PokerHandChecker* fiveKind = new FiveOfAKindChecker();
    PokerHandChecker* royalFlush = new RoyalFlushChecker();
    PokerHandChecker* straightFlush = new StraightFlushChecker();
    PokerHandChecker* fourKind = new FourOfAKindChecker();
    PokerHandChecker* fullHouse = new FullHouseChecker();
    PokerHandChecker* flush = new FlushChecker();
    PokerHandChecker* straight = new StraightChecker();
    PokerHandChecker* threeKind = new ThreeOfAKindChecker();
    PokerHandChecker* twoPair = new TwoPairChecker();
    PokerHandChecker* pair = new PairChecker();
    PokerHandChecker* highCard = new HighCardChecker();

    // 2. Merangkai Chain of Responsibility (Menyambungkan Rantai)
    flushFive->setNext(flushHouse);
    flushHouse->setNext(fiveKind);
    fiveKind->setNext(royalFlush);
    royalFlush->setNext(straightFlush);
    straightFlush->setNext(fourKind);
    fourKind->setNext(fullHouse);
    fullHouse->setNext(flush);
    flush->setNext(straight);
    straight->setNext(threeKind);
    threeKind->setNext(twoPair);
    twoPair->setNext(pair);
    pair->setNext(highCard); // HighCard adalah rantai terakhir

    // 3. Menetapkan kepala rantai (titik awal pengecekan)
    chainRoot = flushFive;
}

ScoringRule::~ScoringRule() {
    // Catatan: Di C++ yang baik, memori yang dibuat dengan 'new' harus di-delete.
    // Tapi karena kita merangkai chain, delete bisa dibuat otomatis nanti.
    // Untuk tahap awal ini biarkan kosong tidak apa-apa agar fokus ke jalan programnya dulu.
}

int ScoringRule::scoreHand(const Hand& hand) {
    std::cout << "[Fase 3] ScoringRule mengirim kartu ke Chain of Responsibility...\n";

    // Ini akan memicu rantai berjalan dari FlushFive sampai ketemu hasilnya
    HandRank rank = chainRoot->check(hand);

    // Ubah hasil (misal: "Pair") jadi angka skor (misal: 100)
    return convertRankToScore(rank);
}

int ScoringRule::convertRankToScore(HandRank rank) {
    int score = 0;

    // (DUMMY SEMENTARA) Nanti Programmer Mekanik yang mengisi nilai asli setiap ranking
    if (rank == HandRank::HighCard) score = 100;
    else if (rank == HandRank::FlushFive) score = 5000;
    // dan seterusnya...

    std::cout << "=> Evaluasi Selesai! Skor Dasar Kartu: " << score << "\n";
    return score;
}