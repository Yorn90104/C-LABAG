#include "LaBaG.h"
#include <iostream>
#include <cstdlib>
#include <ctime>
using namespace std;

// 構造函數
LaBaG::LaBaG() : times(30), played(0), score(0), margin_score(0) {
    int AScores[3] = { 625, 350, 150 };
    P_Map["A"] = P("A", AScores, 36);

    int BScores[3] = { 1250, 650, 220 };
    P_Map["B"] = P("B", BScores, 24);

    int CScores[3] = { 2100, 1080, 380 };
    P_Map["C"] = P("C", CScores, 17);

    int DScores[3] = { 2500, 1250, 420 };
    P_Map["D"] = P("D", DScores, 12);

    int EScores[3] = { 10000, 5000, 1250 };
    P_Map["E"] = P("E", EScores, 8);

    int FScores[3] = { 20000, 10000, 2500 };
    P_Map["F"] = P("F", FScores, 3);

    string seq[6] = { "A", "B", "C", "D", "E", "F" };
    for (int i = 0; i < 6; i++) {
        sequence[i] = seq[i];
    }
}

// 遊戲是否運行
bool LaBaG::GameRunning() {
    return played < times;
}

// 累積機率
vector<int> LaBaG::acc_rate() {
    int acc = 0;
    vector<int> res;
    for (int i = 0; i < 6; i++) {
        acc += P_Map[sequence[i]].Rate;
        res.push_back(acc);
    }
    return res;
}

// 隨機生成
void LaBaG::random() {
    int rand_nums[3] = { rand() % 100 + 1, rand() % 100 + 1, rand() % 100 + 1 };
    vector<int> rate_range = acc_rate();
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 6; j++) {
            if (rand_nums[i] < rate_range[j]) {
                Ps[i] = P_Map[sequence[j]];
                break;
            }
        }
    }
}

// 根據情況獲取分數
void LaBaG::get_score(P p, int typ) {
    margin_score += P_Map[p.code].Score[typ];
}
// 計算分數
void LaBaG::calculate_score() {
    if (Ps[0] == Ps[1] && Ps[1] == Ps[2]) {
        get_score(Ps[0], 0);
    }
    else if (Ps[0] == Ps[1] || Ps[1] == Ps[2] || Ps[2] == Ps[0]) {
        if (Ps[0] == Ps[1]) {
            get_score(Ps[0], 1);
            get_score(Ps[2], 2);
        }
        else if (Ps[1] == Ps[2]) {
            get_score(Ps[1], 1);
            get_score(Ps[0], 2);
        }
        else if (Ps[2] == Ps[0]) {
            get_score(Ps[2], 1);
            get_score(Ps[1], 2);
        }
        margin_score = margin_score * 10 / 13;
    }
    else {
        get_score(Ps[0], 2);
        get_score(Ps[1], 2);
        get_score(Ps[2], 2);
        margin_score /= 3;
    }
}

// 輸出結果
void LaBaG::result() {
    played++;
    score += margin_score;
    cout << "第 " << played << " 次" << endl;
    cout << Ps[0].code << " | " << Ps[1].code << " | " << Ps[2].code << endl;
    cout << "+" << margin_score << endl;
    cout << "目前分數：" << score << endl;
    margin_score = 0;
}
