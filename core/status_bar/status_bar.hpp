#include <string>
#include <ncurses.h>

#include "../../utils/timer/timer.hpp"

#define MAX_CMD_BAR_INPUT_L 100


class StatusBar
{
private:
    std::string MODE;
    std::string STATUS;
    std::string INFO_MSG;
    
public:
    typedef enum BAR_ELEMENT
    {
        BAR_MODE,
        BAR_CURRENT_FILE,
        BAR_COL_INFO,
    } BAR_ELEMENT;

    StatusBar();
    ~StatusBar();

    static WINDOW *draw_status_bar(WINDOW *parentWIN);
    static std::string get_command_input(WINDOW *bar, int *cancelled);
    static void updateBar(BAR_ELEMENT element, const std::string &value);
};