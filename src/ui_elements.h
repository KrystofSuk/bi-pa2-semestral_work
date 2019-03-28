#ifndef UI_ELEMENTS_H
#define UI_ELEMENTS_H

#include <string>
#include <vector>
#include "ui.h"

using namespace std;

namespace UI
{
    class Rect : public Element{
        private:
            int _w;
            int _h;
        public:
            Rect(const int & x, const int & y, const int & w, const int & h, const Color & fg, const char & c);
            void Draw(Pixel ** canvas, int w, int h) const;
    };

    class Circle : public Element{
        private:
            int _r;
        public:
            Circle(const int & x, const int & y, const int & r, const Color & fg, const char & c);
            void Draw(Pixel ** canvas, int w, int h) const;
    };

    class Arc : public Element{
        private:
            int _r;
        public:
            Arc(const int & x, const int & y, const int & r, const Color & fg, const char & c);
            void Draw(Pixel ** canvas, int w, int h) const;
    };
}
#endif