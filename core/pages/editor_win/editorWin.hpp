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
class Cursor {
public:
  int row;
  int col;

  Cursor(int r = 0, int c = 0) : row(r), col(c) {}

  void moveUp() {
    row--;
    move(row, col);
  }
  void moveDown() {
    row++;
    move(row, col);
  }
  void moveLeft() {
    col--;
    move(row, col);
  }
  void moveRight() {
    col++;
    move(row, col);
  }

  void reset() {
    row = 0;
    col = 0;
    move(row, col);
  }
};

class EditorWin : public StatusBar {

private:
  std::string file_buffer;
  std::vector<std::string> editor_buffer;

  int x_offset; // Renderer starts rendering from this column
  int y_offset; // Renderer starts rendering from this row

  int num_cols;
  int num_rows;

  // NOTE: File parser and renderer funcs
  std::string getFileContent(std::string &path);
  std::vector<std::string> createEditorBuffer(std::string file_buffer);
  void render_buffer(std::vector<std::string> &buf);

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
