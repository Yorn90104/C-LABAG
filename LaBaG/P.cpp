#include "P.h"

// 預設構造函數
P::P() : code(""), Rate(0) {
    for (int i = 0; i < 3; i++) {
        Score[i] = 0;
    }
}

// 帶參數的構造函數
P::P(string c, int s[3], int r) : code(c), Rate(r) {
    for (int i = 0; i < 3; i++) {
        Score[i] = s[i];
    }
}

// 比較運算符重載
bool P::operator==(const P& other) const {
    return code == other.code;
}

bool P::operator!=(const P& other) const {
    return code != other.code;
}
