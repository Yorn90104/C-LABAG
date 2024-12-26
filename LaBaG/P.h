#pragma once

#include <string>
using namespace std;

class P {
public:
    string code;
    int Score[3];
    int Rate;

    P();
    P(string c, int s[3], int r);

    bool operator==(const P& other) const;
    bool operator!=(const P& other) const;
};

