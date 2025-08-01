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

// NOTE: Add these enumerationss to types.hpp
typedef enum class EDITOR_MODE { NORMAL, INSERT, VISUAL, COMMAND } EDITOR_MODE;

typedef enum class EDITOR_FILE_STATUS {
  NEW_FILE,
  EXISTING_FILE,
} EDITOR_FILE_STATUS;

typedef enum class EDITOR_OPEN_MODE {
  NEW_FILE,
  OPEN_FILE,
  OPEN_FOLDER
} EDITOR_OPEN_MODE;

typedef enum class CURSOR_MOVEMENT {
  UP,
  DOWN,
  LEFT,
  RIGHT,
} CURSOR_MOVEMENT;

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
  Cursor *cursor;

  int x_offset = 0;
  int y_offset = 0;

  std::string getFileContent(std::string &path);
  std::vector<std::string> createEditorBuffer(std::string file_buffer);
  void renderFile(std::vector<std::string> buf);

protected:
  EDITOR_MODE mode = EDITOR_MODE::NORMAL;

  EDITOR_OPEN_MODE current_open_mode;
  std::string current_file_path;
  EDITOR_FILE_STATUS file_status;

public:
  EditorWin();
  ~EditorWin();

  WINDOW *editor_win;

  void init(EDITOR_OPEN_MODE mode, const std::string &path = "");
  void render();
  std::string getStatusBarCommand();
  void handleCursorMove(CURSOR_MOVEMENT direction);

  void printEditorBuf(); // TEST:
};

#endif // EDITOR_WIN_HPP
