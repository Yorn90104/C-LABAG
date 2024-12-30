#include "LaBaG.h"
#include <iostream>
#include <string>
using namespace std;

int main()
{   
    LaBaG Game;
    srand(time(NULL));
    while (Game.GameRunning()) {
        cout << "請按下 ENTER" << endl;
        string s = "";
        getline(cin, s); // 讀取一行 偵測到換行符號結束讀取
        if (s.compare("") == 0) {
            Game.GameLogic();
        }
    }
    cout << Game.score << endl;
        
    return 0;
}
