#include <ncurses.h>
/*
This class is responsible for handling user input in a terminal

getUserInput returns a struct (InputEvent) which includes :
- type: the type of input (key press, mouse click, etc.)
- x, y: mouse coordinates (only for mouse events)
- ch: the character pressed (if applicable)

*/

typedef enum class InputType
{
    KEY_PRESS_UP,
    KEY_PRESS_DOWN,
    KEY_PRESS_LEFT,
    KEY_PRESS_RIGHT,
    KEY_PRESS_ENTER,
    KEY_PRESS_ESCAPE,
    KEY_PRESS_SPACE,
    KEY_PRESS_BACKSPACE,
    KEY_PRESS_TAB,
    KEY_PRESS_COLON,

    MOUSE_BUTTON_LEFT,
    MOUSE_BUTTON_RIGHT,
    MOUSE_BUTTON_MIDDLE,

    MOUSE_WHEEL_UP,
    MOUSE_WHEEL_DOWN,

    KEY_PRESS_CHAR,
    KEY_PRESS_CTRL_C,
    KEY_PRESS_CTRL_D,
    KEY_PRESS_CTRL_Z,
    KEY_PRESS_CTRL_S,

} InputType;

struct InputEvent
{
    InputType type;
    int x = -1; // They will be -1 if there is no mouse event
    int y = -1;
    char ch = '\0'; 
};

class InputHandler
{
private:
public:
    InputEvent getUserInput(int ch);
};