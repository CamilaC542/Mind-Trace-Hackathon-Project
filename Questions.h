#ifndef QUESTIONS_H
#define QUESTIONS_H

#include "raylib.h"
#include <string>

using namespace std;

class Questions {

private:
    int currentQuestion;
    int scores[3];

    bool active;
    bool complete;

    string result;

    void CalculateResult();

public:
    Questions();

    void Start();
    void Update();
    void Draw(Rectangle area);

    bool IsComplete() const;
    const string& GetResult() const;
};

#endif