/* INFO:
 * If you suffer understanding the x, y, col, row things just look at here
 * ROW = Y
 * COL(UMN) = X
 */

#ifndef EDITOR_WIN_HPP
#define EDITOR_WIN_HPP

#include <fstream>
#include <iostream>
#include <ncurses.h>
#include <sstream>
#include <string>

#include "../../../common/styles/style.hpp"
#include "../../../common/types.hpp"
#include "../../status_bar/status_bar.hpp"

// NOTE: Just moves the cursor and keeps the location
// TODO: Will be developed for the multiple and block cursor skills (later
// for sure :)
class Cursor {
public:
  int editor_row;
  int editor_col;

  Cursor(int r = 0, int c = 0) : editor_row(r), editor_col(c) {}

  void moveUp() {
    editor_row--;
    move(editor_row, editor_col);
  }
  void moveDown() {
    editor_row++;
    move(editor_row, editor_col);
  }
  void moveLeft() {
    editor_col--;
    move(editor_row, editor_col);
  }
  void moveRight() {
    editor_col++;
    move(editor_row, editor_col);
  }

  void reset() {
    editor_row = 0;
    editor_col = 0;
    move(editor_row, editor_col);
  }
};

class EditorWin : public StatusBar {

private:
  std::string file_buffer;
  std::vector<std::string> editor_buffer;

  // NOTE: File renderer offsets (start coordinates)
  int x_offset;
  int y_offset;

  // NOTE: Editor Win Size and Location
  int start_x;  // left up x
  int start_y;  // left up y
  int num_cols; // Cols of win
  int num_rows; // Rows of win

  // NOTE: File parser and renderer funcs
  std::string getFileContent(std::string &path);
  std::vector<std::string> createEditorBuffer(std::string file_buffer);
  void render_buffer(std::vector<std::string> &buf);
  void moveRenderedContent(CURSOR_MOVEMENT direction);

protected:
  // NOTE: ENUMS for modes
  EDITOR_MODE editor_mode;
  EDITOR_OPEN_MODE current_open_mode;
  EDITOR_FILE_STATUS file_status;

  std::string current_file_path;

public:
  EditorWin();
  ~EditorWin();

  // NOTE: Instances
  WINDOW *editor_win;
  Cursor *cursor;

  void init(EDITOR_OPEN_MODE mode, const std::string &path = "");
  void render();

  // NOTE: Handlers
  std::string handleStatusBarCommand();
  void handleCursorMove(CURSOR_MOVEMENT direction);

  // NOTE: Test functions
  void printEditorBuf(); // TEST:
};

#endif // EDITOR_WIN_HPP
