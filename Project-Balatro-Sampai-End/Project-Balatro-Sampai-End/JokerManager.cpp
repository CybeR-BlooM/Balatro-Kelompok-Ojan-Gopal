#include "JokerManager.h"
#include <iostream>

void JokerManager::addJoker(std::unique_ptr<Joker> joker) {
    // Memindahkan hak milik Joker dari luar sistem ke dalam rak penyimpanan
    jokers.push_back(std::move(joker));
}

void JokerManager::notifyScoreCalculated(ScoreContext& context) const {
    // Memanggil efek setiap Joker secara berurutan
    for (const auto& joker : jokers) {
        joker->onScoreCalculated(context);
    }
}

void JokerManager::notifyScoreCalculatedWithLog(ScoreContext& context) const {
    std::cout << "\n=== EFEK JOKER BEKERJA ===\n";

    for (const auto& joker : jokers) {
        std::cout << "> " << joker->getName() << "\n";
        std::cout << "  Efek: " << joker->getDescription(context) << "\n";

        // Eksekusi efek Joker (Decorator bekerja di baris ini)
        joker->onScoreCalculated(context);

        std::cout << "  Skor Sementara: " << context.chips << " Chips, "
            << context.mult << " Mult\n\n";
    }

    std::cout << "=== SKOR AKHIR RONDE ===\n";
    std::cout << context.chips << " x " << context.mult
        << " = " << context.getFinalScore() << "\n\n";
}

int JokerManager::size() const {
    return static_cast<int>(jokers.size());
}