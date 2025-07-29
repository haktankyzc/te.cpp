#include "editorWin.hpp"
#include <fstream>
#include <ncurses.h>
#include <sstream>
#include <vector>

EditorWin::EditorWin() {}
EditorWin::~EditorWin() {}

void EditorWin::open(EDITOR_OPEN_MODE open_mode, const std::string &path) {

  // Window opening options
  switch (open_mode) {
  case EDITOR_OPEN_MODE::NEW_FILE:
    file_status = EDITOR_FILE_STATUS::NEW_FILE;
    current_file_path = path;
    break;
  case EDITOR_OPEN_MODE::OPEN_FILE:
    file_status = EDITOR_FILE_STATUS::EXISTING_FILE;
    current_file_path = path;
    break;
  case EDITOR_OPEN_MODE::OPEN_FOLDER:
    // TODO: File Tree is not implemented yet :()
    break;
  }

  file_buffer = getFileContent(current_file_path); // Read the file

  // Define the window object
  editor_win = newwin(Style::instance().term_rows(),
                      Style::instance().term_cols(), 0, 0);
  wclear(stdscr);   // Clear the screen for page change
  wrefresh(stdscr); //

  StatusBar::draw_status_bar(editor_win);

  wrefresh(editor_win);
}

std::string EditorWin::getFileContent(std::string &path) {
  std::ifstream file(path);

  std::stringstream buffer;
  buffer << file.rdbuf();
  return buffer.str();
}

std::vector<std::string>
EditorWin::createEditorBuffer(std::string file_buffer) {

  int term_col = Style::instance().term_cols() -
                 Style::instance().editor_buffer_vertical_padding();
  int term_row = Style::instance().term_rows();

  std::vector<std::string> editorBuf;
  std::string line = "";

  int row_index = 0;

  for (int index = 0; index < file_buffer.length(); index++) {

    if (file_buffer.at(index) == '\n') {
      editorBuf.push_back(line);
      line.clear();
      continue;
    }
    if (line.length() >= term_col) {
      editorBuf.push_back(line);
      line.clear();
      continue;
    }
    line.push_back(file_buffer.at(index));
  }

  if (!line.empty()) {
    editorBuf.push_back(line);
  }

  return editorBuf;
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
