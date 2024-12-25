#include <iostream>
#include <string>
#include <map>
#include <vector>
#include <cstdlib>  // rand(), srand()
#include <ctime>    // time()
using namespace std;

class P {
public:
    string code;
    int Score[3];
    int Rate;

    bool operator==(const P& other) const {
        return code == other.code; // 比较 code 是否相同
    } // 用於 LaBaG calculate_score 中的比較P

    bool operator!=(const P& other) const {
        return code != other.code; // 比较 code 是否相同
    } // 用於 LaBaG calculate_score 中的比較P

    P() : code(""), Rate(0) {
        for (int i = 0; i < 3; i++) {
            Score[i] = 0;
        }
    } // LaBAG 中 P Ps[3] 初始化空的需要的

    P(string c, int s[3], int r) : code(c), Rate(r) {
        for (int i = 0; i < 3; i++) {
            Score[i] = s[i];
        }
    }
};

class LaBaG {
public:
    int times = 30; // 遊戲次數
    int played = 0; // 已遊玩次數

    int score = 0; // 總分
    int margin_score = 0; // 邊際分數

    map<string, P> P_Map; //此遊戲中使用的P的映射 
    string sequence[6] = { "A", "B", "C", "D", "E", "F" }; // P 順序

    P Ps[3]; //每次遊玩出現的P

    LaBaG() {
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
    }//

    bool GameRunning() {
        return played < times;
    }

    vector<int> acc_rate() {
        int acc = 0;
        vector<int> res;
        for (int i = 0; i < 6; i++) {
            acc += P_Map[sequence[i]].Rate;
            res.push_back(acc);
        }
        return res;  // 返回 vector
    }

    void random() {
        int rand_nums[3] = { rand() % 100 + 1, rand() % 100 + 1, rand() % 100 +1};

        vector<int> rate_range = acc_rate(); //機率區間
        // 遍歷輸出機率區間
        cout << "機率區間: ";
        for (int r : rate_range) {
            cout << r << " ";
        }
        cout << endl;

        for (int i = 0; i < 3; i++) {
            for (int j = 0; j < 6; j++) {
                if (rand_nums[i] < rate_range[j]) {
                    Ps[i] = P_Map[sequence[j]]; // 設定選中的 P
                    break; // 選中就 break 回 i 圈
                }
            }

        }
    }

    void get_score(P p, int typ) {
        //typ 得分情況
        margin_score += P_Map[p.code].Score[typ];
    }

    void calculate_score() {
        //計算分數
        if (Ps[0] == Ps[1] && Ps[1] == Ps[2]) {
            //三個相同
            get_score(Ps[0], 0);
        }
        else if (Ps[0] == Ps[1] || Ps[1] == Ps[2] || Ps[2] == Ps[0]) {
            //兩個相同
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
        else if (Ps[0] != Ps[1] && Ps[1] != Ps[2] && Ps[2] != Ps[0]) {
            //三個皆不同
            get_score(Ps[0], 2);
            get_score(Ps[1], 2);
            get_score(Ps[2], 2);
            margin_score /= 3;
        }
    }

    void result() {
        played++;
        score += margin_score;
        cout << "第 " << played << " 次" << endl;
        cout << Ps[0].code << " | " << Ps[1].code << " | " << Ps[2].code << endl;
        cout << "+" << margin_score << endl;
        cout << "目前分數：" << score << endl;
        margin_score = 0;
    }
};

int main() {
    srand(time(NULL)); // 隨機數種子
    LaBaG Game;
    while (Game.GameRunning()) {
        cout << "請按下 ENTER" << endl;
        string s; // 使用字元陣列 string == char[]
        getline(cin, s); // 讀取整行句子，直到遇到換行符

        if (s.compare("") == 0)
        {
            Game.random();
            Game.calculate_score();
            Game.result();
        }
    }
    cout << "\n遊戲結束！\n最終總分為：" << Game.score << endl;
    return 0;
}

