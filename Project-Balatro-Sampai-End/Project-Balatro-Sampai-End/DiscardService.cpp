#include "DiscardService.h"
#include <iostream>
#include <algorithm> // Untuk std::sort

void DiscardService::discardCards(HandState& hand, std::vector<int> indicesToDiscard) {
    if (indicesToDiscard.empty()) return;

    std::cout << "\n[DiscardService] Membuang " << indicesToDiscard.size() << " kartu...\n";

    // 1. Urutkan index dari yang terbesar ke terkecil (Descending)
    // Mencegah pergeseran index saat elemen dihapus dari std::vector
    std::sort(indicesToDiscard.begin(), indicesToDiscard.end(), std::greater<int>());

    // 2. Hapus kartu satu per satu berdasarkan index
    for (int index : indicesToDiscard) {
        // Validasi keamanan: pastikan index tidak melampaui batas
        if (index >= 0 && index < hand.cards.size()) {
            hand.cards.erase(hand.cards.begin() + index);
        }
    }

    std::cout << "=> Kartu berhasil dibuang.\n";
}