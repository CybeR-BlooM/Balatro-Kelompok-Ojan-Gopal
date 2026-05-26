#pragma once
#include "ScoreContext.h"

class JokerObserver {
public:
    // Virtual destructor agar saat Joker dihapus, memori bersih dan tidak bocor (memory leak)
    virtual ~JokerObserver() = default;

    // Pure virtual function (= 0) yang memaksa semua jenis Joker 
    // untuk memiliki kemampuan bereaksi terhadap kalkulasi skor
    virtual void onScoreCalculated(ScoreContext& context) = 0;
};