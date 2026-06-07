#pragma once
#include "ScoreContext.h"
#include <string>

class Joker {
public:
    // Virtual destructor wajib ada untuk mencegah memory leak saat polymorphism
    virtual ~Joker() = default;

    // =========================================================
    // FUNGSI KONTRAK WAJIB DARI TDD 
    // =========================================================

    // 1. Mendapatkan nama Joker
    virtual std::string getName() const = 0;

    // 2. Mendapatkan deskripsi Joker (Menerima parameter ScoreContext sesuai TDD)
    virtual std::string getDescription(const ScoreContext& context) const = 0;

    // 3. Fungsi utama untuk memodifikasi chips dan multiplier di dalam context
    virtual void onScoreCalculated(ScoreContext& context) = 0;
};