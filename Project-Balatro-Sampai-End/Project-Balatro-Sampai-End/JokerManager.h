#pragma once

#include "Joker.h"
#include <memory>
#include <vector>

class JokerManager {
public:
    // Menambahkan Joker baru ke dalam koleksi pemain
    void addJoker(std::unique_ptr<Joker> joker);

    // Menyiarkan event perubahan skor secara diam-diam (untuk kalkulasi internal)
    void notifyScoreCalculated(ScoreContext& context) const;

    // Menyiarkan event perubahan skor beserta log teks ke terminal (untuk UI pemain)
    void notifyScoreCalculatedWithLog(ScoreContext& context) const;

    // Mengecek berapa banyak Joker yang sedang aktif
    int size() const;

private:
    // Rak penyimpanan untuk semua Joker menggunakan smart pointer (mencegah memory leak)
    std::vector<std::unique_ptr<Joker>> jokers;
};