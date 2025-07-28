#ifndef STATUS_BAR_HPP
#define STATUS_BAR_HPP

#include <ncurses.h>
#include <string>
#include <utility>

#include "../../utils/timer/timer.hpp"

/*
This is a vim like status bar for the terminal apllications.

First, you draw_status_bar() and it pop ups the bar at the bottom of the screen.
Then, you can update the bar with updateBar() method.

It has its own timer to update the bar every second, so you can use it to show
the current time or any other information that needs to be updated frequently.
*/

#define MAX_CMD_BAR_INPUT_L 100

class StatusBar {
private:
  std::string mode = "NORMAL";
  std::string current_file = "";
  std::string info_msg;
  std::pair<std::string, std::string> LOC_INFO;
  std::string time;

  MyTimer bar_timer;

public:
  typedef enum STATUS_BAR_ELEMENT {
    BAR_MODE,
    BAR_CURRENT_FILE,
    BAR_COL_INFO,
    BAR_ROW_INFO
  } STATUS_BAR_ELEMENT;

  StatusBar();
  ~StatusBar();

  WINDOW *bar;

  WINDOW *draw_status_bar(WINDOW *parentWIN);
  std::string get_command_input(WINDOW *bar, int *cancelled);
  void updateBar(STATUS_BAR_ELEMENT element, const std::string &value);
};

#endif // STATUS_BAR_HPP
