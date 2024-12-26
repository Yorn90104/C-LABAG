#include "LaBaG.h"
#include <iostream>
#include <string>
#include "raylib.h"
using namespace std;

int main() {
    srand(time(NULL));
    LaBaG Game;
    InitWindow(450, 800, "LaBaG");

    while (!WindowShouldClose())
    {
        while (Game.GameRunning()) {
            cout << "請按下 ENTER" << endl;
            string s = "";
            getline(cin, s); // 讀取一行 偵測到換行符號結束讀取
            if (s.compare("") == 0) {
                Game.GameLogic();
            }
        }
        /*cout << "\n遊戲結束！\n最終總分為：" << Game.score << endl;*/
    }
    CloseWindow();
    return 0;
}
