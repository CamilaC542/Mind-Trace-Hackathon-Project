// headers here ...
#include "raylib.h"
#include "Files.h"
#include "Terminal.h"

#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <cctype>

string Uppercase(string text) {

    transform(
        text.begin(),
        text.end(),
        text.begin(),
        [](unsigned char c) {
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

using namespace std;
int main() {

    /***

     your project code here!
     
     ***/

     const int screenWidth = 1100;
    const int screenHeight = 760;

    InitWindow(
        screenWidth,
        screenHeight,
        "MINDTRACE - Intelligence Archive"
    );

    SetTargetFPS(60);

    vector<Files> Filess;

    Files mkultra;

    mkultra.id = "FILE 001";
    mkultra.title = "PROJECT MKULTRA";
    mkultra.date = "";
    mkultra.category = "";

    mkultra.summary = "";

    mkultra.evidence = "";

    mkultra.question = "";

    mkultra.source = "";

    Filess.push_back(mkultra);


    Files cointelpro;

    cointelpro.id = "FILE 002";
    cointelpro.title = "COINTELPRO";
    cointelpro.date = "";
    cointelpro.category = "";

    cointelpro.summary = "";

    cointelpro.evidence = "";

    cointelpro.question = "";

    cointelpro.source = "";

    Filess.push_back(cointelpro);


    Files ai;

    ai.id = "FILE 003";
    ai.title = "AI PSYOPS";
    ai.date = "";
    ai.category = "";

    ai.summary = "";

    ai.evidence = "";

    ai.question = "";

    ai.source = "";

    Filess.push_back(ai);


    Terminal terminal;

    int selectedFiles = 0;

    bool running = true;

    cout << "MINDTRACE STARTED" << endl;
    cout << "Archive contains "
         << Filess.size()
         << " files."
         << endl;


    while (!WindowShouldClose() && running) {

        Vector2 mouse = GetMousePosition();

        if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {

            for (int i = 0; i < Filess.size(); i++) {

                Rectangle fileArea = {
                    25,
                    120.0f + i * 95,
                    285,
                    80
                };

                if (CheckCollisionPointRec(mouse, fileArea)) {

                    selectedFiles = i;

                    terminal.AddLine(
                        "OPENED " + Filess[i].id
                    );

                    cout << "Opened: "
                         << Filess[i].title
                         << endl;
                }
            }
        }


        string command;

        if (terminal.UpdateInput(command)) {

            command = Uppercase(command);

            terminal.AddLine("> " + command);

            cout << "COMMAND: "
                 << command
                 << endl;


            if (command == "HELP") {

                terminal.AddLine(
                    "HELP | FILES | OPEN [ID] | CONNECTIONS | EXIT"
                );

            }

            else if (command == "FILES") {

                for (const Files& d : Filess) {

                    terminal.AddLine(
                        d.id + " - " + d.title
                    );
                }

            }

            else if (command == "CONNECTIONS") {

                terminal.AddLine(
                    "FILE 001 <-> FILE 002"
                );

                terminal.AddLine(
                    "FILE 002 <-> FILE 003"
                );

                terminal.AddLine(
                    "ALL FILES <-> POWER AND CONTROL"
                );

            }

            else if (command.rfind("OPEN ", 0) == 0) {

                string search = command.substr(5);

                int result = FindFiles(
                    Filess,
                    search
                );

                if (result != -1) {

                    selectedFiles = result;

                    terminal.AddLine(
                        "FILE OPENED SUCCESSFULLY."
                    );

                } else {

                    terminal.AddLine(
                        "ERROR: FILE NOT FOUND."
                    );
                }

            }

            else if (command == "EXIT") {

                running = false;

            }

            else {

                terminal.AddLine(
                    "UNKNOWN COMMAND. TYPE HELP."
                );
            }
        }


        BeginDrawing();

        ClearBackground(
            Color{12, 15, 15, 255}
        );


        DrawRectangle(
            0, 0,
            screenWidth, 70,
            Color{20, 35, 30, 255}
        );

        DrawText(
            "MINDTRACE",
            25, 15,
            30,
            GREEN
        );

        DrawText(
            "INTELLIGENCE ARCHIVE // ACCESS GRANTED",
            280, 28,
            15,
            LIGHTGRAY
        );


        DrawText(
            "ARCHIVE FILES",
            25, 85,
            18,
            GREEN
        );


        for (int i = 0; i < Filess.size(); i++) {

            Rectangle fileArea = {
                25,
                120.0f + i * 95,
                285,
                80
            };

            Filess[i].DrawCard(
                fileArea,
                i == selectedFiles
            );
        }


        Rectangle detailsArea = {
            335, 85,
            740, 455
        };

        Filess[selectedFiles].DrawDetails(
            detailsArea
        );


        Rectangle terminalArea = {
            25, 560,
            1050, 175
        };

        terminal.Draw(terminalArea);


        EndDrawing();

    }


    CloseWindow();
    cout << "MINDTRACE CLOSED." << endl;

    return 0;
}