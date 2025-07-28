#include "status_bar.hpp"

StatusBar::StatusBar() {}
StatusBar::~StatusBar() {}

WINDOW *StatusBar::draw_status_bar(WINDOW *parentWIN) {
  int win_height, win_width;
  getmaxyx(parentWIN, win_height, win_width);

  int height = 1;
  int starty = win_height - 1;

  // start_color();
  // init_pair(1, COLOR_BLACK, COLOR_GREEN);

  WINDOW *bar = derwin(parentWIN, height, win_width, starty, 0);
  wbkgd(bar, COLOR_PAIR(1));
  werase(bar);

  mvwprintw(bar, 0, 0, "-- NORMAL --");
  mvwprintw(bar, 0, win_width / 3, current_file.c_str());
  mvwprintw(bar, 0, win_width * 6 / 10, "Press ':' to enter command");

  wrefresh(bar);
  return bar;
}

std::string StatusBar::get_command_input(WINDOW *bar, int *cancelled) {
  // If the command is cancelled the integer that is pointed as parameter will
  // be 1

  int win_height, win_width;
  getmaxyx(bar, win_height, win_width);

  std::string input;
  int start_y = win_height - 1;

  werase(bar);
  wmove(bar, start_y, 0);
  wrefresh(bar);

  // echo(); Ah şu hata
  wbkgd(bar, COLOR_PAIR(1));
  curs_set(1);
  mvwprintw(bar, start_y, 0, ":");
  wrefresh(bar);

  int ch;
  while ((ch = wgetch(bar)) != '\n') {
    if (ch == 27) { // ESC
      *cancelled = 1;
      break;
    } else if (ch == KEY_BACKSPACE || ch == 127 || ch == '\b') {
      if (!input.empty()) {
        input.pop_back();
        int len = input.size();
        mvwprintw(bar, start_y, len + 1, " ");
        wmove(bar, start_y, len + 1);
        wrefresh(bar);
      }
    } else if (input.size() < MAX_CMD_BAR_INPUT_L - 1 && ch >= 32 &&
               ch <= 126) {
      input.push_back(ch);
      mvwprintw(bar, start_y, input.size(), "%c", ch);
      wrefresh(bar);
    }
  }

  noecho();
  curs_set(0);
  werase(bar);
  wrefresh(bar);

  if (*cancelled) {
    return "";
  }

  return input;
}
