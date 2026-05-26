#pragma once

#include "JokerObserver.h"
#include <string>

class Joker : public JokerObserver {
public:
    // Virtual destructor untuk keamanan memori
    virtual ~Joker() = default;

    // Mewajibkan semua Joker memiliki Nama
    virtual std::string getName() const = 0;

    // Mewajibkan semua Joker memiliki Deskripsi Efek
    // Menggunakan ScoreContext agar deskripsi bisa dinamis (menyesuaikan keadaan)
    virtual std::string getDescription(const ScoreContext& context) const = 0;
};