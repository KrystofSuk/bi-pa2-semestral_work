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
            Rect(const int & x, const int & y, const int & w, const int & h, const Color & fg, const string & c);
            void Draw(Pixel ** canvas, const int & w, const int & h) const;
            virtual ~Rect();
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
            Circle(const int & x, const int & y, const double & r, const Color & fg, const string & c);
            void Draw(Pixel ** canvas, const int & w, const int & h) const;
            virtual ~Circle();
    };

    /**
     * @brief 
     * 
     */
    class Arc : public Circle{
        private:
        public:
            /**
             * @brief Construct a new Arc object
             * 
             * @param x 
             * @param y 
             * @param r 
             * @param fg 
             * @param c 
             */
            Arc(const int & x, const int & y, const double & r, const Color & fg, const string & c);
            void Draw(Pixel ** canvas, const int & w, const int & h) const;
            virtual ~Arc();
    };
    
    /**
     * @brief 
     * 
     */
    class Text : public Element{
        protected:
            string _text;
            vector<Pixel> _pixels;
        public:
            /**
             * @brief Construct a new Text object
             * 
             * @param x 
             * @param y 
             * @param fg 
             * @param text 
             */
            Text(const int & x, const int & y, const Color & fg, const string & text);
            void Draw(Pixel ** canvas, const int & w, const int & h) const;
            virtual ~Text();
    };

    class UIInteraction{
        protected:
            Color _active;
            Color _deActive;
        public:
            UIInteraction(const Color & fg);
            ~UIInteraction();        
    };

    class Button : public Text, public UIInteraction{
        private:
            Button * _l;
            Button * _r;
            Button * _t;
            Button * _b;
            int _stateIndex;
        public:
            Button(const int & x, const int & y, const Color & fg, const string & text, const Color & activeFg, const int & state);
            Button * GetNext(Direction dir);
            void SetNextElements(Button * l, Button * r, Button * t, Button * b);
            const int & GetIndex() const;
            void Active();
            void Deactivate();
            virtual ~Button();
    };
}
#endif