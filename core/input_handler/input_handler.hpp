#include <ncurses.h>
#include <iostream>

#include "../../common/types.hpp"

/*
This class is responsible for handling user input in a terminal

getUserInput returns a struct (InputEvent) which includes :
- type: the type of input (key press, mouse click, etc.)
- x, y: mouse coordinates (only for mouse events)
- ch: the character pressed (if applicable)

*/

class InputHandler
{
private:
public:
    InputEvent getUserInput(int ch);
    void testUserInput(int ch);
};