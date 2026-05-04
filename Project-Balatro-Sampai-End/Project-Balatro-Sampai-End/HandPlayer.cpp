#include "HandPlayer.h"
#include <iostream>

ChosenHand HandPlayer::playHand(const Hand& dealtHand) {
    std::cout << "=> Player sedang memilih kartu (Dummy Auto-Pick)...\n";

    ChosenHand chosen;

    // Strategi Dummy: Kita ambil otomatis 5 kartu pertama saja dari tangan.
    // Nanti kalau ada waktu, bagian ini bisa diganti dengan input keyboard (std::cin).
    int cardsToPick = 5;

    // Pastikan kita tidak mengambil lebih dari jumlah kartu yang ada
    if (dealtHand.cards.size() < 5) {
        size_t cardsToPick = 5; // Ubah int jadi size_t
        if (dealtHand.cards.size() < 5) {
            cardsToPick = dealtHand.cards.size();
        }
        for (size_t i = 0; i < cardsToPick; ++i) { // Ubah int i jadi size_t i
            chosen.addChosenCard(dealtHand.cards[i]);
        }

    // Tampilkan ke terminal kartu apa saja yang terpilih
    chosen.printChosenCards();

    return chosen;
}