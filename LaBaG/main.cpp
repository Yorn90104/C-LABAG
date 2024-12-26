#include "LaBaG.h"
#include <iostream>
#include <string>
using namespace std;

int main() {
    srand(time(NULL));
    LaBaG Game;
    while (Game.GameRunning()) {
        cout << "請按下 ENTER" << endl;
        string s = "";
        //cin >> s; //<-- 一定要輸入字串 不能直接按ENTER
        getline(cin, s); // 讀取一行 偵測到換行符號結束讀取
        if (s.compare("") == 0) {
            Game.random();
            Game.calculate_score();
            Game.result();
        }
    }
    cout << "\n遊戲結束！\n最終總分為：" << Game.score << endl;
    return 0;
}
