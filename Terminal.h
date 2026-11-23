#ifndef TERMINAL_H
#define TERMINAL_H

#include "raylib.h"
#include <string>
#include <vector>
using namespace std;

class Terminal {
    private:

    vector<string> history;
    string input;

    public:
    Terminal();

    void AddLine(const string message);
    bool UpdateInput(string command);

    void Draw(Rectangle area) const;
}; 

#endif