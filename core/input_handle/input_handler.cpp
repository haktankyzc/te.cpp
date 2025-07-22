#include "input_handler.hpp"

InputEvent InputHandler::getUserInput(int ch)
    {
        InputEvent event;

        switch (ch)
        {
        case KEY_UP:
            event.type = InputType::KEY_PRESS_UP;
            break;
        case KEY_DOWN:
            event.type = InputType::KEY_PRESS_DOWN;
            break;
        case KEY_LEFT:
            event.type = InputType::KEY_PRESS_LEFT;
            break;
        case KEY_RIGHT:
            event.type = InputType::KEY_PRESS_RIGHT;
            break;
        case KEY_ENTER:
        case '\n':
            event.type = InputType::KEY_PRESS_ENTER;
            break;
        case 27:
            event.type = InputType::KEY_PRESS_ESCAPE;
            break;
        case ' ':
            event.type = InputType::KEY_PRESS_SPACE;
            break;
        case KEY_BACKSPACE:
        case 127:
            event.type = InputType::KEY_PRESS_BACKSPACE;
            break;
        case '\t':
            event.type = InputType::KEY_PRESS_TAB;
            break;
        case ':':
            event.type = InputType::KEY_PRESS_COLON;
            break;
        case 3:
            event.type = InputType::KEY_PRESS_CTRL_C;
            break;
        case 4:
            event.type = InputType::KEY_PRESS_CTRL_D;
            break;
        case 26:
            event.type = InputType::KEY_PRESS_CTRL_Z;
            break;
        case 19:
            event.type = InputType::KEY_PRESS_CTRL_S;
            break;

        case KEY_MOUSE:
        {
            MEVENT me;
            if (getmouse(&me) == OK)
            {
                event.x = me.x;
                event.y = me.y;

                if (me.bstate & BUTTON1_CLICKED)
                    event.type = InputType::MOUSE_BUTTON_LEFT;
                else if (me.bstate & BUTTON3_CLICKED)
                    event.type = InputType::MOUSE_BUTTON_RIGHT;
                else if (me.bstate & BUTTON2_CLICKED)
                    event.type = InputType::MOUSE_BUTTON_MIDDLE;
                else if (me.bstate & BUTTON4_PRESSED)
                    event.type = InputType::MOUSE_WHEEL_UP;
                else if (me.bstate & BUTTON5_PRESSED)
                    event.type = InputType::MOUSE_WHEEL_DOWN;
            }
            break;
        }

        default:
            if (ch >= 32 && ch <= 126)
            {
                event.type = InputType::KEY_PRESS_CHAR;
                event.ch = static_cast<char>(ch);
            }
            break;
        }

        return event;
    }