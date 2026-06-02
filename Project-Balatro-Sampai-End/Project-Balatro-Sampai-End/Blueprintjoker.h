#pragma once
#include "Joker.h"
#include <string>

// 1. TIPE JOKER CHIP: Menambahkan Chips (Contoh: Sly Joker)
class SlyJoker : public Joker {
public:
    std::string getName() const override { return "Sly Joker"; }
    std::string getDescription(const ScoreContext& context) const override {
        return "+50 Chips";
    }
    void onScoreCalculated(ScoreContext& context) override {
        context.chips += 50; // Menambahkan 50 Chips ke base score
    }
};

// 2. TIPE JOKER +MULT: Menambahkan Mult dasar (Contoh: Jolly Joker)
class JollyJoker : public Joker {
public:
    std::string getName() const override { return "Jolly Joker"; }
    std::string getDescription(const ScoreContext& context) const override {
        return "+8 Mult";
    }
    void onScoreCalculated(ScoreContext& context) override {
        context.mult += 8; // Menambahkan 8 Mult
    }
};

// 3. TIPE JOKER X MULT: Mengalikan total Mult (Contoh: Cavendish)
class CavendishJoker : public Joker {
public:
    std::string getName() const override { return "Cavendish"; }
    std::string getDescription(const ScoreContext& context) const override {
        return "X3 Mult";
    }
    void onScoreCalculated(ScoreContext& context) override {
        context.mult *= 3; // MENGALIKAN Mult yang sudah ada dengan 3
    }
};

// 4. TIPE JOKER SPESIFIK TANGAN: Aktif HANYA jika kombinasinya cocok (Contoh: Zany Joker)
class ZanyJoker : public Joker {
public:
    std::string getName() const override { return "Zany Joker"; }
    std::string getDescription(const ScoreContext& context) const override {
        return "+12 Mult jika kombinasi yang dimainkan adalah Three of a Kind";
    }
    void onScoreCalculated(ScoreContext& context) override {
        // Ingat HandRank dari 13 Checker kemarin? Kita gunakan di sini!
        if (context.handType == HandRank::ThreeOfAKind) {
            context.mult += 12; 
        }
    }
};

// 5. TIPE JOKER BERSYARAT (Contoh: Joker yang butuh jumlah kartu tertentu)
class MysticJoker : public Joker {
public:
    std::string getName() const override { return "Mystic Joker"; }
    std::string getDescription(const ScoreContext& context) const override {
        return "+20 Mult jika kamu memainkan tepat 3 kartu";
    }
    void onScoreCalculated(ScoreContext& context) override {
        if (context.cards.size() == 3) {
            context.mult += 20;
        }
    }
};