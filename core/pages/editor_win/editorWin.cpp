#include "editorWin.hpp"
#include <ncurses.h>

// =======================================
// =     CONSTRUCTOR  / DESTRUCTOR       =
// =======================================

EditorWin::EditorWin() {
  cursor = new Cursor(0, 0);

  editor_mode = EDITOR_MODE::NORMAL;

  x_offset = 0;
  y_offset = 5;

  // INFO: Set window size and loc
  start_x = getbegx(editor_win);
  start_y = getbegy(editor_win);
  num_cols = getmaxx(editor_win);
  num_rows = getmaxy(editor_win);
}
EditorWin::~EditorWin() { delete cursor; }

// =======================================
// =     INITIALIZATION OF WINDOW        =
// =======================================

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

// =======================================
// =     FILE RENDERING FUNCTIONS        =
// =======================================

// NOTE: Main render func
void EditorWin::render() {
  file_buffer = getFileContent(current_file_path); // Read the file
  editor_buffer = createEditorBuffer(file_buffer); // Parse the file  to lines
  render_buffer(editor_buffer);
  StatusBar::draw_status_bar(editor_win);

  wclear(stdscr);   // Clear the screen for page change
  wrefresh(stdscr); //

  wrefresh(editor_win);
}

// NOTE: moves content for -one- block to a direction
void EditorWin::moveRenderedContent(CURSOR_MOVEMENT direction) {
  switch (direction) {
  case CURSOR_MOVEMENT::UP:
    y_offset--;
    break;
  case CURSOR_MOVEMENT::DOWN:
    y_offset++;
    break;
  case CURSOR_MOVEMENT::RIGHT:
    x_offset++;
    break;
  case CURSOR_MOVEMENT::LEFT:
    x_offset--;
    break;
  }
  render_buffer(editor_buffer);
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

void EditorWin::render_buffer(std::vector<std::string> &buf) {
  int col_offset = Style::instance().editor_buffer_vertical_padding();
  int term_col = Style::instance().term_cols();
  int term_row = Style::instance().term_rows();
  wattron(editor_win, COLOR_PAIR(4));
  for (int i = 0; i < term_row; ++i) {
    mvwaddch(editor_win, i, 0, '~'); // Fill the first row with spaces
  }
  wattroff(editor_win, COLOR_PAIR(4));

  int row = 0;

  for (int i = y_offset; i < buf.size(); ++i) {
    const std::string &line = buf[i];

    int col = col_offset;
    for (int j = x_offset; j < line.size(); ++j) {
      if (col >= term_col) {
        row++;
        col = col_offset;
      }
      if (row >= term_row - 1)
        return;

      mvwaddch(editor_win, row, col, line[j]);
      col++;
    }

    row++; // yeni terminal satırına geç (ekranda)
    if (row >= term_row - 1)
      break;
  }
}

// =======================================
// =     STATUS_BAR ABSTRACTIONS         =
// =======================================

std::string EditorWin::handleStatusBarCommand() {
  // Abstraction for get_command_input() func from StatusBar
  // Cancelled var is cancelled :) , if the command is empty, it will return
  // empty :)
  int cancelled = 0;
  std::string command = StatusBar::get_command_input(editor_win, &cancelled);

  // TODO: Always render parentWin first
  EditorWin::render();                    // Reopen the file
  StatusBar::draw_status_bar(editor_win); // Redraw the status bar

  return command;
}

// =======================================
// =          CURSOR HANDLING            =
// =======================================

void EditorWin::handleCursorMove(CURSOR_MOVEMENT direction) {
  switch (direction) {
  case CURSOR_MOVEMENT::UP:
    if (cursor->editor_row > 0) {
      cursor->moveUp();
    } else if (y_offset != 0) {
      y_offset -= 1;
    }
    break;
  case CURSOR_MOVEMENT::DOWN:
    if (cursor->editor_row < Style::instance().term_rows() - 1) {
      cursor->moveDown();
    }
    break;
  case CURSOR_MOVEMENT::LEFT:
    if (cursor->editor_col > 0) {
      cursor->moveLeft();
    }
    break;
  case CURSOR_MOVEMENT::RIGHT:
    if (cursor->editor_col < Style::instance().term_cols() - 1) {
      cursor->moveRight();
    }
    break;
  default:
    break;
  }
  render();
}

// =======================================
// ===     LOGGING FUNCTIONS           ===
// =======================================

void EditorWin::printEditorBuf() {
  for (std::string s : editor_buffer) {
    std::cout << s << std::endl;
  }
}
