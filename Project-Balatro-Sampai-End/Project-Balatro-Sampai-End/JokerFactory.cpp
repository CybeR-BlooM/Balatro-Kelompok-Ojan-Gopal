#include "JokerFactory.h"
#include "ConcreteJokers.h" // Meng-include semua wujud asli Joker

std::unique_ptr<Joker> JokerFactory::createJoker(JokerType type) {
    switch (type) {
        case JokerType::FlatChip: return std::make_unique<FlatChipJoker>();
        case JokerType::Pair:     return std::make_unique<PairJoker>();
        case JokerType::Basic:    return std::make_unique<BasicJoker>();
        case JokerType::Greedy:   return std::make_unique<GreedyJoker>();
        case JokerType::Spade:    return std::make_unique<SpadeJoker>();
        default:                  return nullptr;
    }
}

int JokerFactory::getPrice(JokerType type) {
    // Menentukan harga balancing untuk toko
    switch (type) {
        case JokerType::Basic:    return 3;
        case JokerType::FlatChip: return 4;
        case JokerType::Pair:     return 5;
        case JokerType::Spade:    return 6;
        case JokerType::Greedy:   return 8;
        default: return 0;
    }
}

std::string JokerFactory::getName(JokerType type) {
    // Nama yang akan ditampilkan di UI terminal Shop
    switch (type) {
        case JokerType::Basic:    return "Basic Joker (+10 Chips, +2 Mult)";
        case JokerType::FlatChip: return "Flat Chip Joker (+20 Chips)";
        case JokerType::Pair:     return "Pair Joker (+4 Mult on Pair)";
        case JokerType::Spade:    return "Spade Joker (+5 Chips per Spade Card)";
        case JokerType::Greedy:   return "Greedy Joker (x2 Mult)";
        default: return "Unknown Joker";
    }
}