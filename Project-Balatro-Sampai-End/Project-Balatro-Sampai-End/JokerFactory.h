#pragma once
#include "Joker.h"
#include <memory>
#include <string>

// Enum daftar 5 Joker yang tersedia di pabrik (Gabungan TDD Dosen & TDD Kelompok 11)
enum class JokerType {
    FlatChip,
    Pair,
    Basic,
    Greedy,
    Spade
};

class JokerFactory {
public:
    // Factory Method: Menciptakan objek Joker berdasarkan tipenya
    static std::unique_ptr<Joker> createJoker(JokerType type);
    
    // Fungsi utilitas untuk Shop System
    static int getPrice(JokerType type);
    static std::string getName(JokerType type);
};