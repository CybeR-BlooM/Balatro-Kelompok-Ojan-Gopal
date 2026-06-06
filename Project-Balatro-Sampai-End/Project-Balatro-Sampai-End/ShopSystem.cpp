#include "ShopSystem.h"
#include <iostream>
#include <string>

void ShopSystem::restock() {
    currentStock.clear();
    // Simulasi stok toko: Menyediakan 3 Joker
    currentStock.push_back(JokerType::Basic);
    currentStock.push_back(JokerType::Spade);
    currentStock.push_back(JokerType::Greedy);
}

void ShopSystem::enterShop(RunSessionState& state, JokerManager& jokerManager) {
    restock();
    bool inShop = true;

    while (inShop) {
        std::cout << "\n=========================================================\n";
        std::cout << " 🛒 SELAMAT DATANG DI TOKO (SHOP PHASE) 🛒 \n";
        std::cout << " DOMPET KAMU: $" << state.money << " | REROLL GRATIS: " << state.freeRerolls << "\n";
        std::cout << " SLOT JOKER KAMU: " << jokerManager.size() << " / 5\n"; // Asumsi maksimal 5
        std::cout << "=========================================================\n";

        for (size_t i = 0; i < currentStock.size(); ++i) {
            std::cout << " [" << (i + 1) << "] " << JokerFactory::getName(currentStock[i])
                << " - Harga: $" << JokerFactory::getPrice(currentStock[i]) << "\n";
        }
        std::cout << " [R] Reroll Stok (Harga: $5) | [L] Leave Shop (Lanjut Game)\n";
        std::cout << "---------------------------------------------------------\n";
        std::cout << "Pilih aksi > ";

        std::string input;
        std::getline(std::cin, input);

        if (input.empty()) continue;

        char command = std::toupper(input[0]);

        if (command == 'L') {
            std::cout << "\n[!] Keluar dari Toko. Melanjutkan perjalanan...\n";
            inShop = false;
        }
        else if (command == 'R') {
            if (state.freeRerolls > 0) {
                state.freeRerolls--;
                std::cout << "\n[!] Menggunakan Free Reroll! Stok diperbarui.\n";
                restock(); // Idealnya di-random, untuk sekarang restock statis
            }
            else if (state.money >= 5) {
                state.money -= 5;
                std::cout << "\n[!] Membayar $5 untuk Reroll! Stok diperbarui.\n";
                restock();
            }
            else {
                std::cout << "\n[!] Uang tidak cukup untuk Reroll!\n";
            }
        }
        else if (command >= '1' && command <= '3') {
            int index = command - '1';
            if (index < currentStock.size()) {
                JokerType selected = currentStock[index];
                int price = JokerFactory::getPrice(selected);

                if (state.money >= price) {
                    if (jokerManager.size() >= 5) {
                        std::cout << "\n[!] Slot Joker penuh! Jual Joker lamamu dulu.\n";
                    }
                    else {
                        // Proses Pembelian
                        state.money -= price;
                        std::cout << "\n[!] Berhasil membeli " << JokerFactory::getName(selected) << "!\n";

                        // Buat Joker via Factory dan masukkan ke Manager
                        // jokerManager.addJoker(JokerFactory::createJoker(selected));

                        // Hapus dari etalase toko
                        currentStock.erase(currentStock.begin() + index);
                    }
                }
                else {
                    std::cout << "\n[!] Uang tidak cukup!\n";
                }
            }
        }
        else {
            std::cout << "\n[!] Perintah tidak valid.\n";
        }
    }
}