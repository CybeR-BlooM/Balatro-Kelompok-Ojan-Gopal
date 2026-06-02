#include "HandPlayer.h"
#include <iostream>
#include <sstream> // Untuk memecah teks berdasarkan spasi
#include <cctype>  // Untuk std::toupper

PlayerAction HandPlayer::promptPlayer(const HandState& hand) {
    PlayerAction action;
    action.type = ActionType::INVALID;

    std::string input;
    std::cout << "\nMasukkan Aksi (P/D/J) diikuti nomor kartu > ";

    // getline digunakan agar bisa membaca teks berspasi
    std::getline(std::cin, input);

    // Jika pemain tidak mengetik apa-apa dan langsung enter
    if (input.empty()) return action;

    // Masukkan input ke mesin pemecah kata (String Stream)
    std::stringstream ss(input);
    char commandChar;

    // Ambil karakter pertama (P/D/J)
    ss >> commandChar;
    commandChar = std::toupper(commandChar); // Paksa jadi huruf kapital

    // Tentukan jenis aksi
    if (commandChar == 'P') action.type = ActionType::PLAY;
    else if (commandChar == 'D') action.type = ActionType::DISCARD;
    else if (commandChar == 'J') action.type = ActionType::JOKER_INFO;
    else return action; // Jika bukan P/D/J, status tetap INVALID

    // Ambil sisa angkanya satu per satu (contoh: 1, 3, 5)
    int num;
    while (ss >> num) {
        // Validasi keamanan: Pastikan pemain tidak mengetik angka ngawur (misal kartu ada 8, dia ketik 99)
        if (num >= 1 && num <= hand.cards.size()) {
            // Masukkan ke vector, dikurangi 1 karena index array/vector C++ selalu mulai dari 0
            action.selectedIndices.push_back(num - 1);
        }
    }

    return action;
}

ChosenHand HandPlayer::createChosenHand(const HandState& hand, const std::vector<int>& indices) {
    ChosenHand chosen;
    for (int index : indices) {
        // Validasi ekstra
        if (index >= 0 && index < hand.cards.size()) {
            chosen.cards.push_back(hand.cards[index]);
        }
    }
    return chosen;
}