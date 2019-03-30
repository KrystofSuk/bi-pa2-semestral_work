#ifndef UI_ELEMENTS_H
#define UI_ELEMENTS_H

#include <string>
#include <vector>
#include "ui.h"

using namespace std;

namespace UI
{
    /**
     * @brief 
     * 
     */
    class Rect : public Element{
        private:
            int _w;
            int _h;
        public:
            /**
             * @brief Construct a new Rect object
             * 
             * @param x 
             * @param y 
             * @param w 
             * @param h 
             * @param fg 
             * @param c 
             */
            Rect(const int & x, const int & y, const int & w, const int & h, const Color & fg, const char & c);
            void Draw(Pixel ** canvas, int w, int h) const;
    };

    /**
     * @brief 
     * 
     */
    class Circle : public Element{
        protected:
            double _r;
        public:
            /**
             * @brief Construct a new Circle object
             * 
             * @param x 
             * @param y 
             * @param r 
             * @param fg 
             * @param c 
             */
            Circle(const int & x, const int & y, const double & r, const Color & fg, const char & c);
            void Draw(Pixel ** canvas, int w, int h) const;
    };

    /**
     * @brief 
     * 
     */
    class Arc : Circle{
        private:
        public:
            void Draw(Pixel ** canvas, int w, int h) const;
    };
    
    /**
     * @brief 
     * 
     */
    class Text : public Element{
        private:
            string _text;
            vector<Pixel> _pixels;
        public:
            Text(const int & x, const int & y, const Color & fg, const string & text);
            void Draw(Pixel ** canvas, int w, int h) const;
    };
}
#endif