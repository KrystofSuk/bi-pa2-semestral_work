#include <iostream>
#include <string>
#include <iomanip>
#include "ui.h"

using namespace std;
using namespace UI;

int main ( int argc, char* argv[] ) {
    Canvas canvas = Canvas(30,20);
    Rect r = Rect(10, 10, 5, 8, red, red);
    Rect r2 = Rect(0, 10, 3, 3, blue, black);
    Circle c = Circle(8, 3, 5, white, white);
    Circle c2 = Circle(2, 3, 3, green, blue);
    canvas.Clear();
    canvas.SetElements({c, c2});
    canvas.SetElements({r, r2});
    canvas.Draw();
    return 0;
}