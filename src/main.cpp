#include <iostream>
#include <string>
#include <iomanip>
#include "ui.h"
#include "ui_elements.h"
#include "ui_elements_extra.h"

using namespace std;
using namespace UI;
using namespace UI_Extra;

int main ( int argc, char* argv[] ) {
    Canvas canvas = Canvas(30, 20);

    Rect r = Rect(10, 10, 5, 8, red, 'x');
    Rect r2 = Rect(0, 10, 3, 3, blue, 'o');
    Circle c = Circle(8, 3, 5, white, ',');
    Circle c2 = Circle(2, 3, 3, green, 'm');

    canvas.Clear();
    canvas.AddElement(r);
    canvas.AddElement(c);
    canvas.AddElement(r2);
    canvas.AddElement(c2);
    canvas.Draw();
    return 0;
}