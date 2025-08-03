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

class Cursor
{
public:
  int row;
  int col;

  Cursor(int r = 0, int c = 0) : row(r), col(c) {}

  void moveUp()
  {
    row--;
    move(row, col);
  }
  void moveDown()
  {
    row++;
    move(row, col);
  }
  void moveLeft()
  {
    col--;
    move(row, col);
  }
  void moveRight()
  {
    col++;
    move(row, col);
  }

  void reset()
  {
    row = 0;
    col = 0;
    move(row, col);
  }
};

class EditorWin : public StatusBar
{

private:
  std::string file_buffer;
  std::vector<std::string> editor_buffer;

  int x_offset = 0;
  int y_offset = 0;

  std::string getFileContent(std::string &path);
  std::vector<std::string> createEditorBuffer(std::string file_buffer);
  void renderFile(std::vector<std::string> buf);

protected:
  EDITOR_MODE editor_mode;

  EDITOR_OPEN_MODE current_open_mode;
  std::string current_file_path;
  EDITOR_FILE_STATUS file_status;

public:
  EditorWin();
  ~EditorWin();

  WINDOW *editor_win;
  Cursor *cursor;

  void init(EDITOR_OPEN_MODE mode, const std::string &path = "");
  void render();
  std::string getStatusBarCommand();
  void handleCursorMove(CURSOR_MOVEMENT direction);

  void printEditorBuf(); // TEST:
};

#endif // EDITOR_WIN_HPP
