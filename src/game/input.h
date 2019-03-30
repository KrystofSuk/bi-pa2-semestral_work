#ifndef INPUT_H
#define INPUT_H

#include <string>
#include "input.h"

using namespace std;

namespace GameLogic
{
    //Specific actions
    enum Key{ Left, Right, Up, Down, Confirm, Cancel, Unknown, End };
    /**
     * @brief It processes information from keyboard and manages it.
     * 
     */
    class InputProcesser{
        public:
            /**
             * @brief Key processing method for getting currently pressed key.
             * 
             * @return const Key which was pressed
             */
            static const Key Process();
    };
}
#endif