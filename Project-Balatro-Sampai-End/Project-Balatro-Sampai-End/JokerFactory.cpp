#include "JokerFactory.h"
// #include "ConcreteJokers.h" (Nanti kalau Jokernya sudah kita buat)

std::unique_ptr<Joker> JokerFactory::createJoker(JokerType type) {
    // KARENA JOKERNYA BELUM DIBUAT CONCRETE-NYA, 
    // Untuk sementara kita return nullptr (atau bisa return BasicJoker kalau sudah ada)
    // Nanti kita lengkapi bagian ini!
    return nullptr;
}

int JokerFactory::getPrice(JokerType type) {
    switch (type) {
    case JokerType::Basic: return 4;
    case JokerType::Spade: return 6;
    case JokerType::Greedy: return 8;
    default: return 0;
    }
}

std::string JokerFactory::getName(JokerType type) {
    switch (type) {
    case JokerType::Basic: return "Basic Joker (+20 Score)";
    case JokerType::Spade: return "Spade Joker (+5 per Spade)";
    case JokerType::Greedy: return "Greedy Joker (x2 Score)";
    default: return "Unknown Joker";
    }
}