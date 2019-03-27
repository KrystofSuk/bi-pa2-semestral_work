#ifndef UI_H
#define UI_H

#include <string>
#include <vector>

using namespace std;

namespace UI
{
    enum UI_Type {none, rect, circle, arc};
    enum Color {white, black, blue, red, green, yellow};
    class Element{
        protected:
            UI_Type _type;
            int _x;
            int _y;
            Color _fg;
            Color _bg;
            int _w;
            int _h;
        public:
            virtual void Draw() const;
            Element();
            Element(int x, int y, Color fg, Color bg);
            int GetX() const;
            int GetY() const;
            int GetW() const;
            int GetH() const;
            Color GetFG() const;
            Color GetBG() const;
            virtual void SetPos(int x, int y);
            UI_Type GetType() const;
    };

    class Canvas{
        private:
            int _w;
            int _h;
            unsigned char ** _canvas;
            Color ** _col;
            int _count;
        public:
            Canvas(int w, int h);
            void Draw() const;
            void Clear();
            void SetElements(vector<Element> _element);
            void AddElement(const Element a);
            ~Canvas();
    };

    class Button{
        private:
        public:
    };

    class Rect : public Element{
        private:
        public:
            void Draw() const;
            Rect(int x, int y, int w, int h, Color fg, Color bg);
    };

    class Circle : public Element{
        private:
        public:
            Circle(int x, int y, int r, Color fg, Color bg);
    };

    class Arc{
        private:
        public:
    };

    class Text{
        private:
        public:
    };
}
#endif