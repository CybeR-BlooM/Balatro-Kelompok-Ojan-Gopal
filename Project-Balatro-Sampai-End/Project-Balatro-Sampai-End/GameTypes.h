#pragma once

// Enum untuk 12 jenis checker (Ditambah None sebagai default)
enum class HandRank {
    None, HighCard, Pair, TwoPair, ThreeOfAKind, Straight, Flush,
    FullHouse, FourOfAKind, StraightFlush, RoyalFlush,
    FiveOfAKind, FlushHouse, FlushFive
};