#include "ConcreteBlinds.h"
#include "ConcreteCommands.h" // Import command yang baru kita buat

// Sesuai TDD, Small Blind memberikan Free Reroll untuk Shop berikutnya [cite: 486-492]
PendingCommand SmallBlindState::createSkipRewardCommand() const {
    return PendingCommand{
        CommandTiming::NextShop,       // Waktu eksekusi: Saat masuk Shop [cite: 489]
        false,                         // Status eksekusi awal: belum dijalankan [cite: 490]
        std::make_unique<FreeRerollCommand>() // Command yang dibungkus [cite: 491]
    };
}

// Mari kita asumsikan Big Blind memberikan Bonus Hand untuk Blind berikutnya
PendingCommand BigBlindState::createSkipRewardCommand() const {
    return PendingCommand{
        CommandTiming::NextBlind,      
        false,
        std::make_unique<BonusHandCommand>() 
    };
}

// Boss Blind biasanya tidak bisa di-skip di Balatro, tapi karena ini diwajibkan oleh interface, 
// kita bisa kembalikan command kosong atau reward khusus jika nanti ada fiturnya.
// Untuk sekarang, kita buat kembalian default yang aman.
PendingCommand BossBlindState::createSkipRewardCommand() const {
    return PendingCommand{
        CommandTiming::Immediate, 
        true, // Langsung ditandai true agar tidak dieksekusi
        nullptr
    };
}