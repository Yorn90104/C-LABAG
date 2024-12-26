#pragma once

#include "P.h"
#include <map>
#include <vector>
#include <string>
using namespace std;

class LaBaG {
public:
    int times;
    int played;
    int score;
    int margin_score;

    map<string, P> P_Map;
    string sequence[6];
    P Ps[3];

    LaBaG();

    bool GameRunning() const;
    void GameLogic();
private:
    vector<int> acc_rate();
    void random();
    void get_score(P p, int typ);
    void calculate_score();
    void result();
};
