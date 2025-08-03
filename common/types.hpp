#ifndef TYPES_HPP
#define TYPES_HPP


// =======================================
// =        INPUT_HANDLING               =
// =======================================

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

// =======================================
// =            EDITOR WINDOW            =
// =======================================

typedef enum class EDITOR_MODE { NORMAL, INSERT, VISUAL, COMMAND } EDITOR_MODE;

typedef enum class EDITOR_FILE_STATUS {
  NEW_FILE,
  EXISTING_FILE,
} EDITOR_FILE_STATUS;

typedef enum class EDITOR_OPEN_MODE {
  NEW_FILE,
  OPEN_FILE,
  OPEN_FOLDER
} EDITOR_OPEN_MODE;

typedef enum class CURSOR_MOVEMENT {
  UP,
  DOWN,
  LEFT,
  RIGHT,
} CURSOR_MOVEMENT;

// =======================================
// =     EMPTY
// =======================================

#endif // TYPES_HPP