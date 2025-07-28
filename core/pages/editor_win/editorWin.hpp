#ifndef EDITOR_WIN_HPP
#define EDITOR_WIN_HPP

#include "../../../common/styles/style.hpp"
#include "../../status_bar/status_bar.hpp"
#include <ncurses.h>
#include <string>

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

class EditorWin : public StatusBar {
private:
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
};

#endif // EDITOR_WIN_HPP
