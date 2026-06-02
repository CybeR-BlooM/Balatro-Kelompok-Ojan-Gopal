#include "DrawService.h"
#include <iostream>

void DrawService::drawCardsToHand(Deck& deck, HandState& hand, int amount) {
    std::cout << "\n[DrawService] Menarik " << amount << " kartu dari Deck...\n";

    int cardsDrawn = 0;
    for (int i = 0; i < amount; ++i) {
        if (!deck.isEmpty()) {
            hand.addCard(deck.drawCard());
            cardsDrawn++;
        }
        else {
            std::cout << "[!] Peringatan: Deck habis!\n";
            break; // Hentikan penarikan jika deck kosong
        }
    }

    std::cout << "=> " << cardsDrawn << " kartu berhasil ditambahkan ke tangan pemain.\n";
}