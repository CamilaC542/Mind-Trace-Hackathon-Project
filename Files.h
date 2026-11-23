#ifndef FILES_H
#define FILES_H

#include "raylib.h"
#include <string>
using namespace std;

class Files {

public:

    string id;
    string title;
    string date;
    string category;
    string summary;
    string evidence;
    string question;
    string source;

    void DrawCard(Rectangle area, bool selected) const;

    void DrawDetails(Rectangle area) const;
};

#endif