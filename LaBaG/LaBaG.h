#ifndef LABAG_H
#define LABAG_H

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

    bool GameRunning();
    vector<int> acc_rate();
    void random();
    void get_score(P p, int typ);
    void calculate_score();
    void result();
};

#endif // LABAG_H
