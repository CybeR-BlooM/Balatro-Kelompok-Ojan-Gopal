♠️ Balatro Clone - Final Technical Documentation

📖 Overview

Balatro Clone merupakan proyek berbasis C++ yang mengimplementasikan sistem permainan kartu poker roguelike yang terinspirasi dari game Balatro. Sistem ini dirancang menggunakan konsep Object-Oriented Programming (OOP) secara ketat dan memadukan 5 Design Pattern tingkat lanjut untuk menghasilkan arsitektur yang sangat modular, scalable, dan mudah dikembangkan di masa depan tanpa merusak kode inti (Open-Closed Principle).

Project ini berfokus pada:

Evaluasi kombinasi poker yang berjenjang

Perhitungan skor dinamis (Chips x Multiplier)

Modifikasi skor menggunakan sistem Joker

Sistem Ekonomi dan Toko (Shop System)

Manajemen progresi tantangan (Blind System)

Eksekusi hadiah tertunda (Deferred Reward System)


🎯 Objectives

Tujuan dari penyusunan sistem arsitektur ini adalah:

Mengimplementasikan evaluasi poker hand tanpa nested if-else yang rumit.

Memisahkan logika skor dasar dan modifikasi skor.

Membangun sistem Joker yang stabil dengan akses langsung ke konteks data (Observer Pattern).

Menciptakan siklus ekonomi untuk pemain melalui Shop (Factory Pattern).

Mengeliminasi struktur kontrol panjang pada fase permainan menggunakan State Pattern (Blind Progression).

Menangani efek skip blind dan reward yang fleksibel menggunakan Command Pattern.


🏗️ System Architecture

Proyek ini dibagi menjadi beberapa sistem utama yang saling bekerja sama, di mana setiap sistem memiliki tanggung jawab tunggal (Single Responsibility):

GameManager :	Mengontrol jalannya siklus permainan utama (Game Loop).

Deck :	Membuat, mengacak, dan menyediakan 52 kartu standar.

Draw/Discard Service :	Mengelola transisi logistik kartu antara Deck dan tangan pemain.

HandState :	Menyimpan kartu yang sedang dipegang pemain saat ini (Maksimal 8).

ChosenHand :	Menyimpan kartu yang dipilih pemain untuk dievaluasi (Maksimal 5).

HandPlayer :	Mengelola parser input terminal pemain (Play, Discard, Skip).

Poker Hand Evaluator :	Menentukan tipe kombinasi tangan tertinggi.

ScoringRule :	Menghitung base chips dan base multiplier.

JokerManager :	Menyiarkan data skor kepada seluruh Joker untuk dimodifikasi.

ShopSystem : Menyediakan antarmuka pembelian Joker dengan mata uang permainan.

BlindSystem : Mengatur status target skor dan progresi tingkat kesulitan.
