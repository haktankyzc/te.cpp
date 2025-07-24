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

void InputHandler::testUserInput(int ch)
{
    switch (ch)
    {
    case KEY_UP:
        std::cout << "Input: KEY_PRESS_UP" << std::endl;
        break;
    case KEY_DOWN:
        std::cout << "Input: KEY_PRESS_DOWN" << std::endl;
        break;
    case KEY_LEFT:
        std::cout << "Input: KEY_PRESS_LEFT" << std::endl;
        break;
    case KEY_RIGHT:
        std::cout << "Input: KEY_PRESS_RIGHT" << std::endl;
        break;
    case KEY_ENTER:
    case '\n':
        std::cout << "Input: KEY_PRESS_ENTER" << std::endl;
        break;
    case 27:
        std::cout << "Input: KEY_PRESS_ESCAPE" << std::endl;
        break;
    case ' ':
        std::cout << "Input: KEY_PRESS_SPACE" << std::endl;
        break;
    case KEY_BACKSPACE:
    case 127:
        std::cout << "Input: KEY_PRESS_BACKSPACE" << std::endl;
        break;
    case '\t':
        std::cout << "Input: KEY_PRESS_TAB" << std::endl;
        break;
    case ':':
        std::cout << "Input: KEY_PRESS_COLON" << std::endl;
        break;
    case 3:
        std::cout << "Input: KEY_PRESS_CTRL_C" << std::endl;
        break;
    case 4:
        std::cout << "Input: KEY_PRESS_CTRL_D" << std::endl;
        break;
    case 26:
        std::cout << "Input: KEY_PRESS_CTRL_Z" << std::endl;
        break;
    case 19:
        std::cout << "Input: KEY_PRESS_CTRL_S" << std::endl;
        break;

    case KEY_MOUSE:
    {
        MEVENT me;
        if (getmouse(&me) == OK)
        {
            std::cout << "Input: MOUSE_EVENT at (" << me.x << ", " << me.y << ")" << std::endl;

            if (me.bstate & BUTTON1_CLICKED)
                std::cout << "Mouse Button: LEFT" << std::endl;
            else if (me.bstate & BUTTON3_CLICKED)
                std::cout << "Mouse Button: RIGHT" << std::endl;
            else if (me.bstate & BUTTON2_CLICKED)
                std::cout << "Mouse Button: MIDDLE" << std::endl;
            else if (me.bstate & BUTTON4_PRESSED)
                std::cout << "Mouse Wheel: UP" << std::endl;
            else if (me.bstate & BUTTON5_PRESSED)
                std::cout << "Mouse Wheel: DOWN" << std::endl;
        }
        break;
    }

    default:
        if (ch >= 32 && ch <= 126)
        {
            std::cout << "Input: KEY_PRESS_CHAR (" << static_cast<char>(ch) << ")" << std::endl;
        }
        else
        {
            std::cout << "Input: UNKNOWN" << std::endl;
        }
        break;
    }
}