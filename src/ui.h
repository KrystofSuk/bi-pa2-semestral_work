#ifndef UI_H
#define UI_H

#include <string>
#include <vector>

using namespace std;

namespace UI
{
    enum Color {white, black, blue, red, green, yellow};

    class Pixel{
        private:
            char _c;
            Color _col; 
        public:
            Pixel();
            Pixel(const char & c, const Color & col);

            char GetChar() const;
            Color GetCol() const;
            
            Pixel& operator=(const Pixel& other) 
            {
                if (this != &other) { 
                    this -> _c = other._c;
                    this -> _col = other._col;
                }
                return *this;
            }
    };

    class Element{
        protected:
            int _x;
            int _y;
            Pixel _px;
        public:
            Element();
            Element(const int & x, const int & y, const char & c, const Color & fg);

            int GetX() const;
            int GetY() const;
            char GetChar() const;
            Pixel GetPixel() const;

            virtual void SetPos(const int & x, const int & y);
            virtual void Draw(Pixel ** canvas, int w, int h) const;
    };

    class Canvas{
        private:
            int _w;
            int _h;
            int _count;
            
            Pixel ** _canvas;

            vector<Element> * _layers;
        public:
            Canvas(const int & w, const int & h);
            void AddElement(const Element & a);
            void Clear();
            void Draw() const;
            ~Canvas();
    };
}
#endif