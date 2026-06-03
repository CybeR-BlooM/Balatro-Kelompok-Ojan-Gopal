#pragma once
#include <string>

class BlindContext; // Forward declaration agar State bisa mengubah State selanjutnya nanti

class BlindState {
public:
    virtual ~BlindState() = default;

    // Setiap Blind harus punya nama (misal: "Small Blind", "The Hook")
    virtual std::string getName() const = 0;

    // Menghitung target skor berdasarkan Ante (level permainan saat ini)
    virtual int getTargetScore(int baseAnte) const = 0;

    // Uang/Chip yang didapat jika menang
    virtual int getRewardReward() const = 0;

    // Fungsi transisi: Apa yang terjadi kalau Blind ini selesai?
    // Nanti SmallBlind akan mengubah context menjadi BigBlind, dst.
    virtual void handleNextBlind(BlindContext* context) = 0;
};