#include <string>
#include <ncurses.h>

#include "../../utils/timer/timer.hpp"

/*
This is a vim like status bar for the terminal apllications. 

First, you draw_status_bar() and it pop ups the bar at the bottom of the screen.
Then, you can update the bar with updateBar() method.

It has its own timer to update the bar every second, so you can use it to show the current time or any other information that needs to be updated frequently.
*/

#define MAX_CMD_BAR_INPUT_L 100

class StatusBar
{
private:
    std::string MODE;
    std::string STATUS;
    std::string INFO_MSG;

    MyTimer bar_timer;
    
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