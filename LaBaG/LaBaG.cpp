﻿#include "LaBaG.h"
#include <iostream>
#include <cstdlib>
#include <ctime>
#include <algorithm> // all of(), any_of()
using namespace std;

// 構造函數
LaBaG::LaBaG():
    times(30),
    played(0),
    score(0),
    margin_score(0),
    score_time_map({
        {"Normal", 1},
        {"SuperHHH", 1},
        {"GreenWei", 3},
        {"PiKaChu", 1}
        }),
    score_time(1),
    SuperHHH(false),
    SuperRate(15),
    SuperTimes(0),
    SuperNum(0),
    GreenWei(false),
    GreenRate(35), GreenTimes(0),
    GreenNum(0),
    gss_times(0),
    PiKaChu(false),
    kachu_times(0)
{
    int AScores[3] = { 625, 350, 150 };
    map<string, int> ARate = { {"Normal", 36}, {"SuperHHH", 19}, {"GreenWei", 36}, {"PiKaChu", 36} };
    P_Map["A"] = P("A", AScores, ARate);

    int BScores[3] = { 1250, 650, 220 };
    map<string, int> BRate = { {"Normal", 24}, {"SuperHHH", 5}, {"GreenWei", 24}, {"PiKaChu", 24} };
    P_Map["B"] = P("B", BScores, BRate);

    int CScores[3] = { 2100, 1080, 380 };
    map<string, int> CRate = { {"Normal", 17}, {"SuperHHH", 19}, {"GreenWei", 17}, {"PiKaChu", 17} };
    P_Map["C"] = P("C", CScores, CRate);

    int DScores[3] = { 2500, 1250, 420 };
    map<string, int> DRate = { {"Normal", 12}, {"SuperHHH", 19}, {"GreenWei", 12}, {"PiKaChu", 12} };
    P_Map["D"] = P("D", DScores, DRate);

    int EScores[3] = { 10000, 5000, 1250 };
    map<string, int> ERate = { {"Normal", 8}, {"SuperHHH", 19}, {"GreenWei", 8}, {"PiKaChu", 8} };
    P_Map["E"] = P("E", EScores, ERate);

    int FScores[3] = { 20000, 10000, 2500 };
    map<string, int> FRate = { {"Normal", 3}, {"SuperHHH", 19}, {"GreenWei", 3}, {"PiKaChu", 3} };
    P_Map["F"] = P("F", FScores, FRate);

    string seq[6] = { "A", "B", "C", "D", "E", "F" };
    for (int i = 0; i < 6; i++) {
        sequence[i] = seq[i];
    }
}

// 遊戲是否運行
bool LaBaG::GameRunning() const 
{
    return played < times;
}

//遊戲內部邏輯流程
void LaBaG::GameLogic() 
{
    Random();
    JudgeSuper();
    CalculateScore();
    JudgeGreen();
    Result();
    JudgeKaChu();
}

//重制
void LaBaG::Reset() 
{
    played = 0;
    score = 0;
    margin_score = 0;
    score_time = 1;

    SuperHHH = false;
    SuperTimes = 0;

    GreenWei = false;
    GreenTimes = 0;
    gss_times = 0;

    PiKaChu = false;
    kachu_times = 0;
}

//現在模式
string LaBaG::NowMod(){
    if (SuperHHH) 
    {
        return "SuperHHH";
    }
    else if (GreenWei)
    {
        return "GreenWei";
    }
    else if (PiKaChu)
    {
        return "PiKaChu";
    }
    else
    {
        return "Normal";
    }
}

// 累積機率
vector<int> LaBaG::acc_rate() 
{
    int acc = 0;
    vector<int> res;
    for (int i = 0; i < 6; i++) {
        acc += P_Map[sequence[i]].Rate[NowMod()];
        res.push_back(acc);
    }
    return res;
}

// 隨機生成
void LaBaG::Random()
{   
    int rand_nums[3] = { rand() % 100 + 1, rand() % 100 + 1, rand() % 100 + 1 };
    vector<int> rate_range = acc_rate();
    cout << "機率區間：";
    for (int r : rate_range) {
        cout << r << " ";
    }
    cout << endl;

    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 6; j++) {
            if (rand_nums[i] <= rate_range[j]) {
                Ps[i] = P_Map[sequence[j]];
                break;
            }
        }
    }
}

// 根據情況獲取分數
void LaBaG::GetScore(P p, int typ) 
{
    margin_score += P_Map[p.code].Score[typ];
}
// 計算分數
void LaBaG::CalculateScore()
{
    score_time = score_time_map[NowMod()];
    cout << "加分倍數:" << score_time << endl;

    if (Ps[0] == Ps[1] && Ps[1] == Ps[2]) {
        GetScore(Ps[0], 0);
        margin_score *= score_time;
    }
    else if (Ps[0] == Ps[1] || Ps[1] == Ps[2] || Ps[2] == Ps[0]) {
        if (Ps[0] == Ps[1]) {
            GetScore(Ps[0], 1);
            GetScore(Ps[2], 2);
        }
        else if (Ps[1] == Ps[2]) {
            GetScore(Ps[1], 1);
            GetScore(Ps[0], 2);
        }
        else if (Ps[2] == Ps[0]) {
            GetScore(Ps[2], 1);
            GetScore(Ps[1], 2);
        }
        margin_score = margin_score * score_time * 10 / 13;
    }
    else {
        GetScore(Ps[0], 2);
        GetScore(Ps[1], 2);
        GetScore(Ps[2], 2);
        margin_score = margin_score * score_time / 3;
    }

    
}

// 輸出結果
void LaBaG::Result() 
{
    played++;
    score += margin_score;
    cout << Ps[0].code << " | " << Ps[1].code << " | " << Ps[2].code << endl;
    cout << "+" << margin_score << endl;
    cout << "目前分數：" << score << endl;
    cout << "剩餘次數 " << (times - played)  << endl;
    margin_score = 0;
    cout << endl;
}

void LaBaG::SuperFalse()
{
    SuperHHH = false;
}

void LaBaG::SuperRandom()
{
    SuperNum = rand() % 100 + 1;
    cout << "超級阿禾隨機數:" << SuperNum << endl;
}

void LaBaG::JudgeSuper()
{
    if (!GameRunning())
    {
        SuperFalse();
        return;
    }

    SuperRandom();
    string mod = NowMod();
    if (mod.compare("SuperHHH") == 0)
    {
        SuperTimes -= 1;
        
        if (all_of(begin(Ps), end(Ps), [](const P& p) {return p.code == "B";})) // & 表示以引用的方式傳遞參數
        {
            SuperTimes += 2;
            cout << "全阿禾，該次次數不消耗且加 1" << endl;
        }
        if (SuperTimes <= 0)
        {
            SuperFalse();
        }
    }
    else if (mod.compare("Normal") == 0 || mod.compare("PiKaChu") == 0)
    {
        bool hhh_appear = false;
        if (any_of(begin(Ps), end(Ps), [](const P& p) {return p.code == "B";}))
        {
            hhh_appear = true;
        }
        if (SuperNum <= SuperRate && hhh_appear)
        {
            cout << "超級阿禾出現了！" << endl;
            SuperHHH = true;
            SuperTimes += 6;
            if (PiKaChu)
            {
                KachuFalse();
            }
            // 超級阿禾加倍
            if (all_of(begin(Ps), end(Ps), [](const P& p) {return p.code == "B";})) 
            {
                cout << "全超級阿禾，觸發阿禾加倍！" << endl;
                int double_score = score * score_time / 2;
                margin_score += double_score;
            }
        }
    }
}

void LaBaG::GreenFalse()
{
    GreenWei = false;
}

void LaBaG::GreenRandom()
{
    GreenNum = rand() % 100 + 1;
    cout << "綠光阿瑋隨機數:" << GreenNum << endl;
}

void LaBaG::JudgeGreen()
{
    if (!GameRunning())
    {
        GreenFalse();
        return;
    }
    // 累積咖波累積數
    for (P p : Ps) {
        if (p.code.compare("A") == 0)
        {
            gss_times += 1;
        }
    }
    cout << "咖波累積數:" << gss_times << endl;

    GreenRandom();
    string mod = NowMod();
    if (mod.compare("GreenWei") == 0)
    {
        GreenTimes -= 1;

        if (all_of(begin(Ps), end(Ps), [](const P& p) {return p.code == "A";})) // & 表示以引用的方式傳遞參數
        {
            GreenTimes ++;
            cout << "全咖波，該次次數不消耗" << endl;
        }
        if (GreenTimes <= 0)
        {
            GreenFalse();
            JudgeSuper();
        }
    }
    else if (mod.compare("Normal") == 0 || mod.compare("PiKaChu") == 0)
    {
        bool all_gss = false;
        if (all_of(begin(Ps), end(Ps), [](const P& p) {return p.code == "A";}))
        {
            all_gss = true;
        }
        if (GreenNum <= GreenRate && all_gss)
        {
            cout << "綠光阿瑋出現了！" << endl;
            GreenWei = true;
            GreenTimes += 2;
            if (PiKaChu)
            {
                KachuFalse();
            }
            
        }
        else if (gss_times >= 20)
        {
            cout << "綠光阿瑋出現了！" << endl;
            GreenWei = true;
            GreenTimes += 2;
            gss_times = 0;
            if (PiKaChu)
            {
                KachuFalse();
            }
        }
    }
}

void LaBaG::KachuFalse()
{
    PiKaChu = false;
}

void LaBaG::JudgeKaChu()
{
    if (!GameRunning() && any_of(begin(Ps), end(Ps), [](const P& p) {return p.code == "E";}))
    {
        cout << "皮卡丘為你充電！" << endl;
        PiKaChu = true;
        played -= 5;
        kachu_times++;
        // 關掉其他模式
        SuperFalse();
        GreenFalse();
    }
    else
    {
        KachuFalse();
    }
}
