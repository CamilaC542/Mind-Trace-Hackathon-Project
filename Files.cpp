#include "Files.h"
#include <sstream>
using namespace std;

void DrawWrappedText(const string text, int x, int y, int maxWidth, int fontSize, Color color) {
    stringstream stream(text); // reminder to cite here later cami
    string word;
    string line;

    int lineHeight = fontSize + 7;

    while (stream >> word) {
        string testLine = line;

        if (!testLine.empty()) {
            testLine += " ";
        }

        testLine += word;

        // Update citation here : https://www.geeksforgeeks.org/cpp/basic_string-c_str-function-in-c-stl/
        if (MeasureText(testLine.c_str(), fontSize) > maxWidth && !line.empty()) {
            DrawText(line.c_str(), x, y, fontSize, color);

            y += lineHeight;
            line = word;

        } else {
            line = testLine;
        }
    }

    if (!line.empty()) {
        DrawText(line.c_str(), x, y ,fontSize, color);
    }
}

void Files::DrawCard(Rectangle area, bool selected) const {

    Color background = selected
    ? Color{45, 65, 55, 255}
    : Color{25, 30, 30, 255};

    Color border = selected ? GREEN : DARKGRAY;

    DrawRectangleRec(area, background);

    DrawRectangleLinesEx(area, 2, border);

    DrawText(id.c_str(), area.x + 12, area.y + 10, 14, GREEN);

    DrawText(title.c_str(), area.x + 12, area.y + 35, 17, RAYWHITE);

    DrawText(date.c_str(), area.x + 12, area.y + 58, 12, GRAY);
}
    
void Files::DrawDetails(Rectangle area) const {
    DrawRectangleRec(area, Color{20, 25, 25, 255});
        
    DrawRectangleLinesEx(area, 2, DARKGREEN);

    int x = area.x + 25;
    int y = area.y + 20;

    DrawText("CLASSIFIED FILE", x, y, 14, GREEN);

    y += 35;

    DrawText(title.c_str(), x, y, 30, RAYWHITE);

    y += 45;

    DrawText(date.c_str(), x, y, 17, GRAY);

    y +=35;

    DrawText("OVERVIEW", x, y, 16, GREEN);

    y += 25;

    DrawWrappedText(summary, x, y, area.width - 55, 17, RAYWHITE);

    y += 105;

    DrawText("HISTORICAL EVIDENCE", x, y, 16, GREEN);

    y += 25;

    DrawWrappedText(evidence, x, y, area.width - 55, 16, LIGHTGRAY);

    y += 75;

    DrawText("ETHICAL QUESTION", x, y, 16, ORANGE);

    y += 25;

    DrawWrappedText(question, x, y, area.width - 55, 16, RAYWHITE);

    y += 60;

    DrawText("SOURCE: ", x, y, 13, GREEN);

    DrawText(source.c_str(), x + 65, y, 12, GRAY);

}