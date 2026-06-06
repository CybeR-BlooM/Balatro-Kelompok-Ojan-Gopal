#include "DrawService.h"
#include <iostream>

void DrawService::drawCardsToHand(Deck& deck, HandState& hand, int amount) {
    int cardsDrawn = 0;

    for (int i = 0; i < amount; ++i) {
        if (!deck.isEmpty()) {
            // Menarik kartu selama deck masih ada isinya
            hand.cards.push_back(deck.drawCard());
            cardsDrawn++;
        }
        else {
            // Hentikan penarikan jika deck kosong
            std::cout << "\n[!] Peringatan: Deck habis! Kamu harus berjuang dengan sisa kartu di tangan.\n";
            break;
        }
    }

    if (cardsDrawn > 0) {
        std::cout << "=> " << cardsDrawn << " kartu baru ditarik ke tangan.\n";
    }
}