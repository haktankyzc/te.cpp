#include "editorWin.hpp"
#include <ncurses.h>

EditorWin::EditorWin() {}
EditorWin::~EditorWin() {}

void EditorWin::open(EDITOR_OPEN_MODE open_mode, const std::string &path) {

  // Window opening options
  switch (open_mode) {
  case EDITOR_OPEN_MODE::NEW_FILE:
    file_status = EDITOR_FILE_STATUS::NEW_FILE;
    break;
  case EDITOR_OPEN_MODE::OPEN_FILE:
    file_status = EDITOR_FILE_STATUS::EXISTING_FILE;
    break;
  case EDITOR_OPEN_MODE::OPEN_FOLDER:
    // TODO: File Tree is not implemented yet :()
    break;
  }
  // Define the window object
  editor_win = newwin(Style::instance().term_rows(),
                      Style::instance().term_cols(), 0, 0);
  wclear(stdscr);   // Clear the screen for page change
  wrefresh(stdscr); //

  StatusBar::draw_status_bar(editor_win);

  wrefresh(editor_win);
}

std::string EditorWin::getStatusBarCommand() {
  // Easinesss for get_command_input() func from StatusBar
  int cancelled = 0;
  std::string command = StatusBar::get_command_input(editor_win, &cancelled);
  if (cancelled) {
    return "";
  } else {
    return command;
  }
}
