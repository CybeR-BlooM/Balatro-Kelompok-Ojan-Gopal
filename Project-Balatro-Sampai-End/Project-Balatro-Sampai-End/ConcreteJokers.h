#pragma once
#include "Joker.h"
#include <string>

// =========================================================
// JOKER DARI TDD DOSEN
// =========================================================

class FlatChipJoker : public Joker {
public:
    std::string getName() const override { return "Flat Chip Joker"; }

    std::string getDescription(const ScoreContext& context) const override {
        return "+20 Chips (Selalu Aktif)";
    }

    void onScoreCalculated(ScoreContext& context) override {
        context.chips += 20;
    }
};

class PairJoker : public Joker {
public:
    std::string getName() const override { return "Pair Joker"; }

    std::string getDescription(const ScoreContext& context) const override {
        return "+4 Mult (Aktif jika kombinasi adalah Pair)";
    }

    void onScoreCalculated(ScoreContext& context) override {
        // [PENYESUAIAN]: Menggunakan enum HandRank dari ScoreContext.h
        if (context.handType == HandRank::Pair) {
            context.mult += 4;
        }
    }
};

// =========================================================
// JOKER DARI TDD KELOMPOK 11
// =========================================================

class BasicJoker : public Joker {
public:
    std::string getName() const override { return "Basic Joker"; }

    std::string getDescription(const ScoreContext& context) const override {
        return "+10 Chips, +2 Mult (Selalu Aktif)";
    }

    void onScoreCalculated(ScoreContext& context) override {
        context.chips += 10;
        context.mult += 2;
    }
};

class GreedyJoker : public Joker {
public:
    std::string getName() const override { return "Greedy Joker"; }

    std::string getDescription(const ScoreContext& context) const override {
        return "x2 Multiplier (Selalu Aktif)";
    }

    void onScoreCalculated(ScoreContext& context) override {
        context.mult *= 2;
    }
};

class SpadeJoker : public Joker {
public:
    std::string getName() const override { return "Spade Joker"; }

    std::string getDescription(const ScoreContext& context) const override {
        return "+5 Chips untuk setiap kartu Spade (Sekop) yang dimainkan";
    }

    void onScoreCalculated(ScoreContext& context) override {
        // [PENYESUAIAN]: Melakukan loop pada array cards di ScoreContext.h
        for (const auto& card : context.cards) {
            if (card.suit == 'S') { // Asumsi suit Spade menggunakan huruf 'S'
                context.chips += 5;
            }
        }
    }
};