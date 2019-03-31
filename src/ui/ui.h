#ifndef UI_H
#define UI_H

#include <string>
#include <vector>

using namespace std;

/**
 * @brief UI namespace for all UI elements, helpers and canvas.
 * 
 */
namespace UI
{
    enum Color {White, Black, Blue, Red, Green, Yellow};

    /**
     * @brief Basic pixel object for storing information for later drawing.
     * It stores information about color and what character this pixel is.
     */
    class Pixel{
        private:
            char _c;
            Color _col; 
        public:
            /**
             * @brief Construct a new Pixel object.
             * constructor, which sets character to space and color to black.
             */
            Pixel();
            /**
             * @brief Construct a new Pixel object.
             * 
             * @param c is character that will be displayed
             * @param col is color of character specified in color enum
             */
            Pixel(const char & c, const Color & col);
            /**
             * @brief Get the character of pixel.
             * 
             * @return The character which pixel stores.
             */
            char GetChar() const;
            /**
             * @brief Get the color of the pixel.
             * 
             * @return Color of pixel
             */
            Color GetCol() const;

            /**
             * @brief Operator for copying pixel information from other pixel.
             * 
             * @param other is pixel from which will be copying values
             * @return Pixel& is modified pixel
             */
            Pixel& operator=(const Pixel& other) 
            {
                if (this != &other) { 
                    this -> _c = other._c;
                    this -> _col = other._col;
                }
                return *this;
            }
    };

    /**
     * @brief Basic ui element which stores information about his position and his specific pixel type, other elements derives this class with basic information.
     * 
     */
    class Element{
        protected:
            unsigned short _layer; 
            int _x;
            int _y;
            Pixel _px;
        public:
            /**
             * @brief Construct a new Element object.
             * 
             */
            Element();
            /**
             * @brief Construct a new Element object.
             * 
             * @param x position
             * @param y position
             * @param c character which will be drawn
             * @param fg color of an element
             */
            Element(const int & x, const int & y, const char & c, const Color & fg);

            /**
             * @brief Getter for x position.
             * 
             * @return int x position
             */
            int GetX() const;
            /**
             * @brief Getter for y position.
             * 
             * @return int y position
             */
            int GetY() const;
            /**
             * @brief Get the Pixel specification of an element.
             * 
             * @return Pixel
             */
            Pixel GetPixel() const;

            /**
             * @brief Set the position of element.
             * 
             * @param x position
             * @param y position
             */
            virtual void SetPos(const int & x, const int & y);
            /**
             * @brief Draw the element to the canvas
             * 
             * @param canvas canvas which will be modified
             * @param w width of canvas
             * @param h height of canvas
             */
            virtual void Draw(Pixel ** canvas, const int & w, const int & h) const;
    };

    /**
     * @brief Canvas class for drawing all specified elements, clearing, modifiing colors.
     * 
     */
    class Canvas{
        private:
            int _w;
            int _h;
            int _count;
            
            Pixel ** _canvas;

            vector<Element *> _layer;
        public:
            /**
             * @brief Construct a new Canvas 
             * 
             */
            Canvas();
            /**
             * @brief Construct a new Canvas 
             * 
             * @param w width
             * @param h height
             */
            Canvas(const int & w, const int & h);

            /**
             * @brief Adds new element to canvas
             * 
             * @param e pointer to element to add
             */
            void AddElement(Element * e);
            /**
             * @brief Clears the canvas and sets it back to black board
             * 
             */
            void Clear();
            /**
             * @brief Draws all added elements in specific layers
             * 
             */
            void Draw();

            /**
             * @brief Destroy the Canvas
             * 
             */
            ~Canvas();
    };
}
#endif