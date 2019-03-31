#ifndef CONSTS_H
#define CONSTS_H

#include <string>
#include <vector>

using namespace std;

namespace Extra
{
    class Consts{
        public:
            Consts();

            const int & GetCanvasWidth() const;
            const int &  GetCanvasHeight() const;
            const int &  GetUpKey() const;
            const int &  GetDownKey() const;
            const int &  GetLeftKey() const;
            const int &  GetRightKey() const;
            const int &  GetCancelKey() const;
            const int &  GetConfirmKey() const;
        private:
            int _canvasWidth;
            int _canvasHeight;
            int _upKey;
            int _downKey;
            int _leftKey;
            int _rightKey;
            int _cancelKey;
            int _confirmKey;
    };
}
#endif