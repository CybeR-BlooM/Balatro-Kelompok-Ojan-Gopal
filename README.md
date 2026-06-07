♠️ Balatro Clone - Final Technical Documentation

📖 Overview

Balatro Clone merupakan proyek berbasis C++ yang mengimplementasikan sistem permainan kartu poker roguelike yang terinspirasi dari game Balatro. Sistem ini dirancang menggunakan konsep Object-Oriented Programming (OOP) secara ketat dan memadukan 5 Design Pattern tingkat lanjut untuk menghasilkan arsitektur yang sangat modular, scalable, dan mudah dikembangkan di masa depan tanpa merusak kode inti (Open-Closed Principle).

Project ini berfokus pada:

- Evaluasi kombinasi poker yang berjenjang

- Perhitungan skor dinamis (Chips x Multiplier)

- Modifikasi skor menggunakan sistem Joker

- Sistem Ekonomi dan Toko (Shop System)

- Manajemen progresi tantangan (Blind System)

- Eksekusi hadiah tertunda (Deferred Reward System)


🎯 Objectives

Tujuan dari penyusunan sistem arsitektur ini adalah:

- Mengimplementasikan evaluasi poker hand tanpa nested if-else yang rumit.

- Memisahkan logika skor dasar dan modifikasi skor.

- Membangun sistem Joker yang stabil dengan akses langsung ke konteks data (Observer Pattern).

- Menciptakan siklus ekonomi untuk pemain melalui Shop (Factory Pattern).

- Mengeliminasi struktur kontrol panjang pada fase permainan menggunakan State Pattern (Blind Progression).

- Menangani efek skip blind dan reward yang fleksibel menggunakan Command Pattern.


🏗️ System Architecture

Proyek ini dibagi menjadi beberapa sistem utama yang saling bekerja sama, di mana setiap sistem memiliki tanggung jawab tunggal (Single Responsibility):

- GameManager :	Mengontrol jalannya siklus permainan utama (Game Loop).

- Deck : Membuat, mengacak, dan menyediakan 52 kartu standar.

- Draw/Discard Service : Mengelola transisi logistik kartu antara Deck dan tangan pemain.

- HandState : Menyimpan kartu yang sedang dipegang pemain saat ini (Maksimal 8).

- ChosenHand : Menyimpan kartu yang dipilih pemain untuk dievaluasi (Maksimal 5).

- HandPlayer : Mengelola parser input terminal pemain (Play, Discard, Skip).

- Poker Hand Evaluator : Menentukan tipe kombinasi tangan tertinggi.

- ScoringRule : Menghitung base chips dan base multiplier.

- JokerManager : Menyiarkan data skor kepada seluruh Joker untuk dimodifikasi.

- ShopSystem : Menyediakan antarmuka pembelian Joker dengan mata uang permainan.

- BlindSystem : Mengatur status target skor dan progresi tingkat kesulitan.

📂 Project Structure

```text
Balatro-Clone
│
├── System
│   ├── GameManager
│   ├── RunSessionState
│   │
│   ├── Card Mechanics
│   │   ├── Card
│   │   ├── Deck
│   │   ├── HandState
│   │   ├── ChosenHand
│   │   ├── HandPlayer
│   │   ├── DrawService
│   │   └── DiscardService
│   │
│   ├── Hand Evaluation (Chain of Responsibility)
│   │   ├── PokerHandChecker (Interface)
│   │   ├── ScoringRule
│   │   ├── ScoreContext
│   │   ├── GameTypes (HandRank Enum)
│   │   └── Checkers (FlushFiveChecker ... HighCardChecker)
│   │
│   ├── Jokers (Observer & Factory Pattern)
│   │   ├── Joker (Interface)
│   │   ├── JokerManager
│   │   ├── ConcreteJokers (FlatChip, Pair, Basic, Greedy, Spade)
│   │   ├── JokerFactory
│   │   └── ShopSystem
│   │
│   └── Blinds & Rewards (State & Command Pattern)
│       ├── BlindState (Interface)
│       ├── ConcreteBlinds (Small, Big, Boss)
│       ├── RewardCommand (Interface)
│       └── ConcreteCommands (BonusHand, FreeReroll)
│
└── Main.cpp 
```

🔄 Runtime Flow

```text
main()
    ↓
GameManager::runSession()
    ↓
Initialize Deck & Shuffle
    ↓
[ START NEW BLIND ]
Execute NextBlind Deferred Commands
Draw Cards (Up to 8)
    ↓
[ PLAYER ACTION PROMPT ] -> Play (P) / Discard (D) / Skip (S)
    ↓
    ├── IF SKIP (S):
    │   Create RewardCommand (Command Pattern)
    │   Store in PendingCommands
    │   Execute Immediate Commands
    │   Transition to Next Blind State
    │
    └── IF PLAY (P):
        Validate Selection (Max 5 cards)
        Evaluate HandRank (Chain of Responsibility)
        Calculate Base Score (ScoringRule)
        Inject Data to ScoreContext (Cards, HandRank, Base Chips, Base Mult)
        Trigger Jokers to Modify Context (Observer Pattern)
        Add to Total Score
        Discard Played Cards & Draw Replacements
    ↓
[ CHECK WIN/LOSE CONDITIONS ]
    ├── IF Score >= Target: 
    │   Win Blind -> Earn Money -> Execute NextShop Commands -> Enter ShopSystem -> Next Blind
    └── IF Plays <= 0 OR (Hand Empty & Deck Empty): 
        Game Over
```
🃏 Card System

Card

Merepresentasikan satu kartu permainan fisik.

Attributes
```text
struct Card {
    int rank;
    char suit;
};
```
Rank & Suit

- Rank: 2 - 10 (Angka), 11 (Jack), 12 (Queen), 13 (King), 14 (Ace).

- Suit: 'H' (Hearts), 'D' (Diamonds), 'C' (Clubs), 'S' (Spades).

🎴 Deck System

Bertanggung jawab mengelola suplai kartu. Berbeda dengan mekanisme tanpa batas, deck ini bersifat finite (52 kartu) untuk menjaga tingkat kesulitan permainan.

- initialize(): Menyusun 52 kartu standar.

- shuffle(): Mengacak menggunakan algoritma RNG C++.

- drawCard(): Mengeluarkan kartu teratas.

- isEmpty(): Mengecek apakah pemain kehabisan kartu (trigger kondisi kritis).

✋ Hand System & Player Interaction

HandState & ChosenHand

Mekanisme memisahkan Inventory (kartu di tangan) dan Execution Tray (kartu yang dimainkan). Pemain memegang maksimal 8 kartu di HandState, dan hanya bisa memilih maksimal 5 kartu untuk dimasukkan ke ChosenHand.

HandPlayer

Parser input cerdas yang membaca perintah pemain via terminal:

- P 1 2 3 : Memainkan (PLAY) kartu pada indeks 1, 2, 3.

- D 4 5 : Membuang (DISCARD) kartu pada indeks 4, 5.

- S : Melewati (SKIP) Blind saat ini untuk mengambil hadiah khusus.

♣ Poker Hand Evaluation System

Evaluasi kombinasi poker dibangun secara eksklusif menggunakan Chain of Responsibility Pattern.

Alih-alih menggunakan logika if-else masif yang sulit di-debug, sistem melempar ChosenHand ke rantai Checker yang tersusun dari hierarki tertinggi hingga terendah:

- FlushFive

- FlushHouse

- FiveOfAKind

- RoyalFlush

- StraightFlush

- FourOfAKind

- FullHouse

- Flush

- Straight

- ThreeOfAKind

- TwoPair

- Pair

- HighCard (Fallback Checker - memastikan tidak ada error jika kombinasi gagal)

💰 Scoring System

ScoringRule

Mengonversi hasil rantai evaluasi (HandRank) menjadi nilai dasar permainan dan menyimpannya di memori internal (lastHandRank) untuk dibaca oleh sistem luar.

- Rumus Dasar: Final Score = Chips × Multiplier

ScoreContext (Data Transfer Object)

Wadah dinamis yang melintas dari ScoringRule menuju ke JokerManager.

- Data Input: cards (kartu fisik yang dimainkan), handType (tipe kombinasi).

- Data Termutasi: chips, mult.

🎭 Joker System

Berbeda dengan beberapa implementasi yang menggunakan Decorator, proyek ini menggunakan pendekatan Observer Pattern / Direct Context Modification untuk stabilitas yang lebih tinggi. JokerManager menyiarkan ScoreContext kepada semua Joker aktif, dan setiap Joker mengubah nilai di dalamnya secara mandiri.

Available Jokers :

- Basic Joker: +10 Chips, +2 Mult (Selalu aktif).

- Flat Chip Joker: +20 Chips (Selalu aktif).

- Greedy Joker: x2 Mult (Menggandakan multiplier).

- Pair Joker: +4 Mult (Aktif secara kondisional jika handType bernilai Pair).

- Spade Joker: +5 Chips (Membaca isi array cards dan menghitung jumlah suit 'S').

🏪 Shop System & Economy

Fase belanja antar-Blind yang digerakkan oleh Factory Pattern.

JokerFactory

Menghapus kebutuhan inisialisasi manual. ShopSystem meminta factory untuk menciptakan instance memori baru (std::unique_ptr<Joker>) hanya ketika pemain melakukan pembelian yang sah.

- Metode: createJoker(JokerType), getPrice(JokerType), getName(JokerType).

Shop System Mechanics

Pemain menggunakan $ money (didapat dari kemenangan Blind) untuk:

- Membeli Joker baru (Maksimal 5 slot).

- Reroll stok barang dengan biaya $5 atau menggunakan token Free Reroll.

🎯 Blind System

Progresi tingkat kesulitan dimodelkan dengan State Pattern. GameManager tidak perlu mengetahui syarat kemenangan fase saat ini; ia cukup bertanya pada State yang sedang aktif.

- SmallBlindState: Target skor rendah.

- BigBlindState: Target skor menengah.

- BossBlindState: Target ekstrem, tidak bisa di-skip, dan bertanggung jawab menaikkan level level Ante sebelum mereset kembali ke Small Blind.

🎁 Reward System (Skip Blind)

Mengeliminasi eksekusi efek secara langsung menggunakan Command Pattern dan Deferred Execution Queue (PendingCommand).

Ketika pemain melakukan Skip Blind:

- BlindState saat ini meracik RewardCommand spesifik (misal: FreeRerollCommand).

- Command dimasukkan ke antrean sesi dengan CommandTiming tertentu (contoh: NextShop).

- GameManager memonitor timing ini. Saat pemain memasuki fase Toko, GameManager memanggil .execute() pada command yang tertunda.

🧩 Design Patterns Summary

- Chain of Responsibility: Digunakan pada Poker Hand Evaluation (PokerHandChecker berantai). Menjamin penambahan kombinasi baru tidak mengganggu logika lama.

- Observer Pattern / Context Modifier: Digunakan pada Joker System. JokerManager menyiarkan ScoreContext ke objek turunan Joker.

- State Pattern: Digunakan pada Blind Progression (BlindState dan turunannya). Menghilangkan percabangan rumit dari Game Loop.

- Command Pattern: Digunakan pada Reward System (RewardCommand). Membungkus aksi sebagai objek tertunda yang bisa dieksekusi berdasarkan fase permainan.

- Factory Pattern: Digunakan pada Pembuatan Joker (JokerFactory). Memusatkan logika perakitan memori objek Joker agar toko (ShopSystem) tetap bersih.

🚀 Future Improvements

Beberapa fitur yang dipersiapkan untuk ekspansi di masa depan:

- Implementasi sistem UI interaktif.

- Mekanisme penjualan Joker (Sell System) di Toko.

- Penambahan efek modifikasi kartu (Tarot/Planet cards).

- Save/Load System untuk melanjutkan progres.

👨‍💻 Authors

Kelompok Proyek C++ Balatro

- Fauzan Dharul Ramadhani

- M Naufal Aqil

📜 License

This project was created for educational purposes, software architecture studies, and advanced C++ Design Pattern implementation practice.
