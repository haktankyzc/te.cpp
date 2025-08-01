#include "editorWin.hpp"
#include <fstream>
#include <ncurses.h>
#include <sstream>
#include <vector>

EditorWin::EditorWin() {}
EditorWin::~EditorWin() {}

void EditorWin::render() {
  file_buffer = getFileContent(current_file_path); // Read the file
  editor_buffer = createEditorBuffer(file_buffer); // Parse the file  to lines
  renderFile(editor_buffer);
  StatusBar::draw_status_bar(editor_win);

  wclear(stdscr);   // Clear the screen for page change
  wrefresh(stdscr); //

  wrefresh(editor_win);
}

void EditorWin::init(EDITOR_OPEN_MODE open_mode, const std::string &path) {

  // Window opening options
  current_open_mode = open_mode;
  current_file_path = path;
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
  // Define the window object
  editor_win = newwin(Style::instance().term_rows(),
                      Style::instance().term_cols(), 0, 0);
  render();
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

  std::vector<std::string> editorBuf;
  std::string line = "";

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

void EditorWin::renderFile(std::vector<std::string> buf) {
  int col_offset = Style::instance().editor_buffer_vertical_padding();
  int term_col = Style::instance().term_cols();
  int term_row = Style::instance().term_rows();

  int row = 0;

  for (const std::string &line : buf) {
    int col = col_offset;
    for (char ch : line) {
      if (col > term_col) {
        row++;
        col = col_offset;
      }
      if (row >= term_row - 1)
        return;
      mvwaddch(editor_win, row, col, ch);
      col++;
    }
    row++; // yeni satıra geç
  }
}

std::string EditorWin::getStatusBarCommand() {
  // Abstraction for get_command_input() func from StatusBar
  int cancelled = 0;
  std::string command = StatusBar::get_command_input(editor_win, &cancelled);
  StatusBar::draw_status_bar(editor_win); // Redraw the status bar
  EditorWin::draw(current_open_mode, current_file_path); // Reopen the file
  return command;
}

void EditorWin::printEditorBuf() {
  for (std::string s : editor_buffer) {
    std::cout << s << std::endl;
  }
}

void handleCursorMove(CURSOR_MOVEMENT direction) {
  switch (direction) {
  case CURSOR_MOVEMENT::UP:
    if (cursor.row > 0) {
      move(--cursor.row, cursor.col);
    }
    break;

  default:
    break;
  }
}
