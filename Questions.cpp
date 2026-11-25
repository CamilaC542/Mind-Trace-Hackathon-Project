#include "Questions.h"

using namespace std;

Questions::Questions() {
    currentQuestion = 0;

    for (int i = 0; i < 3; i++) {
        scores[i] = 0;
    }

    active = false;
    complete = false;
    result = "";
}

void Questions::Start() {
    currentQuestion = 0;

    for (int i = 0; i < 3; i++) {
        scores[i] = 0;
    }

    active = true;
    complete = false;
    result = "";
}

void Questions::CalculateResult() {

    if (scores[0] > scores[1] && scores[0] > scores[2]) {
        result = "MKULTRA";
    } else if (scores[1] > scores[0] && scores[1] > scores[2]) {
        result = "PROJECT STARGATE";
    } else if (scores[2] > scores[0] && scores[2] > scores[1]) {
        result = "AI PSYOPS";
    }else {
        result = "MIXED RESULT";
    }
}

void Questions::Update() {

    if (!active) {
        return;
    }

    if (complete) {
        if (IsKeyPressed(KEY_R)) {
            Start();
        }

        return;
    }

    int answer = -1;

    if (IsKeyPressed(KEY_ONE)) {
        answer = 0;
    }else if (IsKeyPressed(KEY_TWO)) {
        answer = 1;
    } else if (IsKeyPressed(KEY_THREE)) {
        answer = 2;
    }

    if (answer == -1) {
        return;
    }

    scores[answer]++;

    currentQuestion++;

    if (currentQuestion >= 3) {
        CalculateResult();
        complete = true;
        active = false;
    }
}

void Questions::Draw(Rectangle area) {

    DrawRectangleRec(area, DARKGRAY);
    DrawRectangleLinesEx(area, 2, GREEN);

    DrawText("MINDTRACE // SUBJECT ASSESSMENT", area.x + 20, area.y + 20, 23, GREEN);

    if (complete) {

        DrawText("ASSESSMENT COMPLETE", area.x + 25, area.y + 110, 25, GREEN);

        DrawText("YOUR THEMATIC MATCH:",area.x + 25,area.y + 180, 20,LIGHTGRAY );

        DrawText(result.c_str(),area.x + 25,area.y + 230, 30, YELLOW );

        DrawText( "PRESS R TO RETAKE THE ASSESSMENT", area.x + 25, area.y + 330, 17, GREEN);

        DrawText("This result reflects your answers, not actual susceptibility.", area.x + 25, area.y + 390, 14, LIGHTGRAY);

        return;
    }

    const char* questions[3] = {
        "What concerns you most about government influence?",
        "Which issue would you most want to investigate?",
        "What do you think deserves the most public oversight?"
    };

    const char* options[3][3] = {

        {
            "1. Individual autonomy and informed consent",
            "2. Intelligence claims and unreliable evidence",
            "3. Digital manipulation and misinformation"
        },

        {
            "1. Psychological experimentation on individuals",
            "2. Remote viewing and intelligence research",
            "3. AI-generated content and online influence"
        },

        {
            "1. Human experimentation and personal rights",
            "2. Intelligence gathering and verification",
            "3. Synthetic media and public opinion"
        }
    };

    DrawText(TextFormat("QUESTION %i / 3", currentQuestion + 1), area.x + 25, area.y + 100, 20, YELLOW);

    DrawText(questions[currentQuestion], area.x + 25, area.y + 160, 20, WHITE);

    for (int i = 0; i < 3; i++) {

        DrawText(options[currentQuestion][i],area.x + 25, area.y + 235 + i * 55, 17, LIGHTGRAY);
    }

    DrawText("PRESS 1, 2, OR 3 TO ANSWER", area.x + 25, area.y + 410, 18, GREEN);
}

bool Questions::IsComplete() const {
    return complete;
}

const string& Questions::GetResult() const {
    return result;
}