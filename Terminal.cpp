#include "Terminal.h"
using namespace std;

Terminal::Terminal() {

    input = "";

    AddLine("MINDTRACE INTELLIGENCE SYSTEM");
    AddLine("ARCHIVE CONNECTION ESTABLISHED.");
    AddLine("TYPE HELP FOR AVAILABLE COMMANDS.");

}

void Terminal::AddLine(const string message) {

    history.push_back(message);

    if (history.size() > 5) {
        history.erase(history.begin());
    }

}

bool Terminal::UpdateInput(string command) {

    int key = GetCharPressed();

    while (key > 0) {

        if (key >= 32 && key <= 125 && input.size() < 45) {
            input += static_cast<char>(key);
        }

        key = GetCharPressed();
    }

    if (IsKeyPressed(KEY_BACKSPACE) && !input.empty()) {
        input.pop_back();
    }

    if (IsKeyPressed(KEY_ENTER)) {

        command = input;
        input.clear();
        return true;
    }

    return false;

}

void Terminal::Draw(Rectangle area) const {

    DrawRectangleRec(area, BLACK);

    DrawRectangleLinesEx(area, 2, DARKGREEN);

    DrawText("SYSTEM TERMINAL", area.x + 15, area.y + 10, 15, GREEN);

    int y = area.y + 38;

    for (const std::string& line : history) {

        DrawText(line.c_str(), area.x + 15, y, 14, LIGHTGRAY);

        y += 21;
    }

    DrawText(("> " + input + "_").c_str(), area.x + 15, area.y + area.height - 28, 16, GREEN);

}
