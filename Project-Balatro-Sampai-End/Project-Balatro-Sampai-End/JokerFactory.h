#pragma once
#include "Joker.h" // Asumsi file Joker dasar milikmu
#include <memory>
#include <string>

// Daftar tipe Joker yang tersedia di Shop
enum class JokerType {
    Basic,
    Spade,
    Greedy
};

class JokerFactory {
public:
    // Factory Method: Membuat Joker berdasarkan tipenya secara dinamis
    static std::unique_ptr<Joker> createJoker(JokerType type);

    // Fungsi utilitas untuk mendapatkan harga Joker
    static int getPrice(JokerType type);

    // Fungsi utilitas untuk nama Joker di UI Shop
    static std::string getName(JokerType type);
};