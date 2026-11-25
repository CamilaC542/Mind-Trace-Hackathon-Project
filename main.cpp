// headers here ...
#include "raylib.h"
#include "Files.h"
#include "Terminal.h"
#include "Questions.h"

#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <cctype>

using namespace std;

string Uppercase(string text) {

    transform(text.begin(), text.end(), text.begin(), [](unsigned char c) {
            return toupper(c);
        }
    );

    return text;
}

int FindFiles(const vector<Files>& Filess, const string& search) {

    for (int i = 0; i < Filess.size(); i++) {

        if (Uppercase(Filess[i].id) == search ||
            Uppercase(Filess[i].title).find(search) != string::npos) {

            return i;
        }
    }

    return -1;
}

int main() {

    const int screenWidth = 1100;
    const int screenHeight = 760;

    InitWindow(screenWidth, screenHeight, "MINDTRACE - Intelligence Archive");

    SetTargetFPS(60);

    vector<Files> Filess;

    Files mkultra;

    mkultra.id = "FILE 001";
    mkultra.title = "PROJECT MKULTRA";
    mkultra.date = "1953 - 1973";
    mkultra.category = "BEHAVIORAL RESEARCH";
    mkultra.summary = "A secret CIA program investigating drugs, interrogation, and methods of influencing human behavior.";
    mkultra.evidence = "Declassified CIA documents revealed experiments involving LSD and other substances, sometimes conducted without participants' informed consent.";
    mkultra.question = "Can national security justify experimenting on people without their knowledge or consent? MKULTRA raises serious questions about human rights, scientific ethics, and government accountability.";
    mkultra.source = "https://www.cia.gov/library/abbottabad-compound/9D/9D9A27BD7241E2074EAF81C7FC2C86CF_MK.Ultra_Senate.Hearings.pdf";

    Filess.push_back(mkultra);

    Files stargate;

    stargate.id = "FILE 002";
    stargate.title = "PROJECT STARGATE";
    stargate.date = "1970s - 1995";
    stargate.category = "PSYCHIC INTELLIGENCE RESEARCH";
    stargate.summary = "A U.S. intelligence research program investigating whether remote viewing could be used to gather information about distant locations and targets.";
    stargate.evidence = "Declassified records document remote viewing experiments. A 1995 evaluation questioned whether the results provided reliable and useful intelligence.";
    stargate.question = "Should intelligence agencies invest in research when its scientific reliability remains uncertain?";
    stargate.source = "American Institutes for Research - 1995 Evaluation of the Stargate Program";
    Filess.push_back(stargate);

    Files ai;

    ai.id = "FILE 003";
    ai.title = "AI PSYOPS";
    ai.date = "2020s - PRESENT";
    ai.category = "DIGITAL INFORMATION MANIPULATION";
    ai.summary = "The use of artificial intelligence in influence operations, including synthetic media, automated messaging, and the spread of misleading information.";
    ai.evidence = "AI-generated images, videos, and text can make deceptive narratives easier to produce and distribute at scale.";
    ai.question = "How can individuals distinguish authentic information from AI-generated manipulation?";
    ai.source = "CISA - Foreign Influence Operations and Disinformation Resources";

    Filess.push_back(ai);

    Terminal terminal;
    Questions questionnaire;

    int selectedFiles = 0;
    int selectedTab = 0;

    bool questionnaireStarted = false;
    bool running = true;

    cout << "MINDTRACE STARTED" << endl;
    cout << "Archive contains " << Filess.size() << " files." << endl;

    while (!WindowShouldClose() && running) {

        Vector2 mouse = GetMousePosition();

        if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {

            for (int i = 0; i < Filess.size(); i++) {

                Rectangle fileArea = {25, 120.0f + i * 95, 285, 80 };

                if (CheckCollisionPointRec(mouse, fileArea)) {
                    selectedFiles = i;
                    selectedTab = i;

                    terminal.AddLine("OPENED " + Filess[i].id);

                    cout << "Opened: " << Filess[i].title << endl;
                }
            }

            Rectangle assessmentArea = {25, 405, 285, 80};

            if (CheckCollisionPointRec(mouse, assessmentArea)) {

                selectedTab = 3;

                if (!questionnaireStarted) {
                    questionnaire.Start();
                    questionnaireStarted = true;
                }

                terminal.AddLine("OPENED SUBJECT ASSESSMENT");

                cout << "Opened: SUBJECT ASSESSMENT" << endl;
            }
        }

        if (selectedTab == 3) {

            questionnaire.Update();

        } else {

            string command;

            if (terminal.UpdateInput(command)) {

                command = Uppercase(command);

                terminal.AddLine("> " + command);

                cout << "COMMAND: " << command << endl;

                if (command == "HELP") {

                    terminal.AddLine("HELP | FILES | OPEN [ID] | ASSESSMENT | CONNECTIONS | EXIT");

                } else if (command == "FILES") {

                    for (const Files& d : Filess) {
                        terminal.AddLine(d.id + " - " + d.title);
                    }

                } else if (command == "CONNECTIONS") {

                    terminal.AddLine("FILE 001 <-> FILE 002");
                    terminal.AddLine("FILE 002 <-> FILE 003");
                    terminal.AddLine("ALL FILES <-> POWER AND CONTROL");

                } else if (command == "ASSESSMENT") {

                    selectedTab = 3;

                    if (!questionnaireStarted) {
                        questionnaire.Start();
                        questionnaireStarted = true;
                    }

                } else if (command.rfind("OPEN ", 0) == 0) {

                    string search = command.substr(5);

                    int result = FindFiles(Filess, search);

                    if (result != -1) {

                        selectedFiles = result;
                        selectedTab = result;

                        terminal.AddLine("FILE OPENED SUCCESSFULLY.");

                    } else {

                        terminal.AddLine("ERROR: FILE NOT FOUND.");
                    }

                } else if (command == "EXIT") {

                    running = false;

                } else {

                    terminal.AddLine("UNKNOWN COMMAND. TYPE HELP.");
                }
            }
        }

        BeginDrawing();

        ClearBackground(Color{12, 15, 15, 255});

        DrawRectangle(0, 0, screenWidth, 70, Color{20, 35, 30, 255});

        DrawText("MINDTRACE", 25, 15, 30, GREEN);

        DrawText("INTELLIGENCE ARCHIVE // ACCESS GRANTED", 280, 28, 15, LIGHTGRAY);

        DrawText("ARCHIVE FILES", 25, 85, 18, GREEN);

        for (int i = 0; i < Filess.size(); i++) {

            Rectangle fileArea = {25, 120.0f + i * 95, 285, 80};

            Filess[i].DrawCard(fileArea, selectedTab == i);
        }

        Rectangle assessmentArea = {25, 405, 285, 80};

        DrawRectangleRec(assessmentArea, selectedTab == 3 ? Color{35, 75, 55, 255} : Color{25, 35, 32, 255});

        DrawRectangleLinesEx(assessmentArea, 2, selectedTab == 3 ? GREEN : DARKGREEN);

        DrawText("FILE 004", 40, 420, 15, GREEN);

        DrawText("SUBJECT ASSESSMENT", 40, 445, 17, LIGHTGRAY);

        if (selectedTab == 3) {

            questionnaire.Draw({335, 85, 740, 455});

        } else {

            Rectangle detailsArea = {335, 85, 740, 455};
            Filess[selectedFiles].DrawDetails(detailsArea);
        }

        Rectangle terminalArea = {25, 560, 1050, 175};

        terminal.Draw(terminalArea);

        EndDrawing();
    }

    CloseWindow();

    cout << "MINDTRACE CLOSED." << endl;

    return 0;
}