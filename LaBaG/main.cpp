#include "LaBaG.h"
#include <iostream>
#include <string>
using namespace std;

int main() {
    srand(time(NULL));
    LaBaG Game;
    while (Game.GameRunning()) {
        cout << "請按下 ENTER" << endl;
        string s;
        getline(cin, s);
        if (s.compare("") == 0) {
            Game.random();
            Game.calculate_score();
            Game.result();
        }
    }
    cout << "\n遊戲結束！\n最終總分為：" << Game.score << endl;
    return 0;
}
