#pragma once
#include "RunSessionState.h"
#include "JokerManager.h"
#include "JokerFactory.h"
#include <vector>

class ShopSystem {
private:
    std::vector<JokerType> currentStock;

public:
    // Mengisi toko dengan Joker acak (Untuk sekarang kita hardcode dulu)
    void restock();

    // Membuka UI Toko dan menangani interaksi pemain
    void enterShop(RunSessionState& state, JokerManager& jokerManager);
};