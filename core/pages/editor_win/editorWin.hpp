#ifndef EDITOR_WIN_HPP
#define EDITOR_WIN_HPP

#include <fstream>
#include <iostream>
#include <ncurses.h>
#include <sstream>
#include <string>

#include "../../../common/styles/style.hpp"
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

typedef struct Cursor {
  int row = 1;
  int col = 1;
} Cursor;

class EditorWin : public StatusBar {

private:
  std::string file_buffer;
  std::vector<std::string> editor_buffer;
  Cursor cursor;

  std::string getFileContent(std::string &path);
  std::vector<std::string> createEditorBuffer(std::string file_buffer);
  void renderFile(std::vector<std::string> buf);

protected:
  EDITOR_FILE_STATUS file_status;
  EDITOR_MODE mode = EDITOR_MODE::NORMAL;

public:
  EditorWin();
  ~EditorWin();

  WINDOW *editor_win;

  std::string current_file_path;

  void open(EDITOR_OPEN_MODE mode, const std::string &path = "");
  std::string getStatusBarCommand();

  void printEditorBuf(); // TEST:
};

#endif // EDITOR_WIN_HPP
