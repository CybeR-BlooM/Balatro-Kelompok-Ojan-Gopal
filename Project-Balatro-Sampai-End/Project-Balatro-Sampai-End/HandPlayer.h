#pragma once
#include "HandState.h"
#include "ChosenHand.h"
#include <string>
#include <vector>

// Enum untuk mendaftar pilihan aksi pemain
enum class ActionType {
    PLAY,
    DISCARD,
    JOKER_INFO,
    INVALID // Jika pemain mengetik perintah yang salah (typo)
};

// Struct paket data untuk dikirim ke GameManager
struct PlayerAction {
    ActionType type;
    std::vector<int> selectedIndices; // Menyimpan index kartu yang dipilih
};

class HandPlayer {
public:
    // Fungsi membaca teks input terminal (contoh: "P 1 3 4")
    PlayerAction promptPlayer(const HandState& hand);

    // Fungsi utilitas untuk memindahkan kartu dari HandState ke ChosenHand saat PLAY
    ChosenHand createChosenHand(const HandState& hand, const std::vector<int>& indices);
};